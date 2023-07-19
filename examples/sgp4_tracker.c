/*
 * Released under MIT License
 *
 * Copyright (c) 2021 Hopperpop.
 *
 * Copyright The libsgp4 Contributors.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

/**
 * \brief Main header file.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0.3
 * 
 * \date 2023/07/07
 * 
 * \defgroup sgp4_tracker SGP4 Tracker
 * \ingroup examples
 * \{
 */

#include <sgp4.h>
#include <Ticker.h>

Sgp4 sat;
Ticker tkSecond;
unsigned long unixtime = 1458950400;
int timezone = 12;  /* utc + 12 */
int framerate;

int year;
int mon;
int day;
int hr;
int minute;
double sec;

void second_tick(void)
{
    unixtime += 1;

    invjday(sat.satJd , timezone, true, year, mon, day, hr, minute, sec);
    printf("%d/%d/%d %d:%d:%d\n\r", day, mon, year, hr, minute, sec);
    printf("azimuth = %f elevation = %f distance = %f\n\r", sat.satAz, sat.satEl, sat.satDist);
    printf("latitude = %f longitude = %f altitude = %f\n\r", sat.satLat, sat.satLon, sat.satAlt);

    switch(sat.satVis)
    {
        case -2:
            printf("Visible : Under horizon\n\r");
            break;
        case -1:
            printf("Visible : Daylight\n\r");
            break;
        default:
            printf("Visible : %d\n\r", sat.satVis); /* 0:eclipsed - 1000:visible */
            break;
    }

    printf("Framerate: %d calc/sec\n\r", framerate);

    framerate = 0;
}

int main()
{
    sat.site(-0.5276847, 166.9359231, 34);  /* set site latitude[°], longitude[°] and altitude[m] */

    char satname[] = "ISS (ZARYA)";
    char tle_line1[] = "1 25544U 98067A   16065.25775256 -.00164574  00000-0 -25195-2 0  9990"; /* Line one from the TLE data */
    char tle_line2[] = "2 25544  51.6436 216.3171 0002750 185.0333 238.0864 15.54246933988812"; /* Line two from the TLE data */
  
    sat.init(satname, tle_line1, tle_line2);    /* initialize satellite parameters */

    /* Display TLE epoch time */
    double jdC = sat.satrec.jdsatepoch;
    invjday(jdC , timezone, true, year, mon, day, hr, minute, sec);
    printf("Epoch: %d/%d/%d %d:%d:%d\n\r", day, mon, year, hr, minute, sec);

    tkSecond.attach(1, second_tick);

    while(1)
    {
        sat.findsat(unixtime);
        framerate += 1;
    }

    return 0;
}

/** \} End of sgp4_tracker group */
