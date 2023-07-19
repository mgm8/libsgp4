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
 * \defgroup sgp4_predictor SGP4 Predictor
 * \ingroup examples
 * \{
 */

#include <sgp4.h>
#include <Ticker.h>

Sgp4 sat;
unsigned long unixtime = 1458950400;
int timezone = 12;  /* utc + 12 */

int year;
int mon;
int day;
int hr;
int minute;
double sec;

void Predict(int many)
{
    passinfo overpass;                  /* structure to store overpass info */
    sat.initpredpoint(unixtime, 0.0);   /* finds the startpoint */

    bool error;
    unsigned long start = millis();
    for(int i = 0; i < many; i++)
    {
        error = sat.nextpass(&overpass, 20);    /* search for the next overpass, if there are more than 20 maximums below the horizon it returns false */
        delay(0);

        if (error == 1) /* no error, prints overpass information */
        {
            invjday(overpass.jdstart ,timezone ,true , year, mon, day, hr, minute, sec);
            printf("Overpass %d %d %d\n\r", day, mon, year);
            printf("  Start: az=%fo %d:%d:%d\n\r", overpass.azstart, hr, minute, sec);

            invjday(overpass.jdmax ,timezone ,true , year, mon, day, hr, minute, sec);
            printf("  Max: elev=%fo %d:%d:%d\n\r", overpass.maxelevation, hr, minute, sec);

            invjday(overpass.jdstop ,timezone ,true , year, mon, day, hr, minute, sec);
            printf("  Stop: az=%fo %d:%d:%d\n\r", overpass.azstop, hr, minute, sec);

            switch(overpass.transit)
            {
                case none:
                    break;
                case enter:
                    invjday(overpass.jdtransit ,timezone ,true , year, mon, day, hr, minute, sec);
                    printf("  Enter earth shadow: %d:%d:%d\n\r", hr, minute, sec); 
                    break;
                case leave:
                    invjday(overpass.jdtransit ,timezone ,true , year, mon, day, hr, minute, sec);
                    printf("  Leave earth shadow: %d:%d:%d\n\r", hr, minute, sec); 
                    break;
            }
            switch(overpass.sight)
            {
                case lighted:
                    printf("  Visible\n\r");
                    break;
                case eclipsed:
                    printf("  Not visible\n\r");
                    break;
                case daylight:
                    printf("  Daylight\n\r");
                    break;
            }
        }
        else
        {
            printf("Prediction error\n\r");
        }
        delay(0);
    }
    unsigned long einde = millis();
    printf("Time: %d milliseconds\n\r", einde - start);
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
    invjday(jdC, timezone, true, year, mon, day, hr, minute, sec);
    printf("Epoch: %d/%d/%d %d:%d:%d\n\r", day, mon, year, hr, minute, sec);

    Predict(50);    /* Calculates the next 50 overpasses */

    return 0;
}

/** \} End of sgp4_predictor group */
