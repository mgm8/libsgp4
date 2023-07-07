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
 * \brief .
 * 
 * This file contains miscellaneous functions required for predicting satellite overpasses and the main class
 * for easy acces to all the functions.
 *
 * Most functions are based on the columns written by Dr. T.S. Kelso on the celestrak website
 * (https://celestrak.com/columns/).
 *
 * \author Hopperpop
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0.3
 * 
 * \date 2023/07/03
 * 
 * \defgroup sgp4pred SGP4 Pred
 * \{
 */

#ifndef SGP4PRED_H_
#define SGP4PRED_H_

#include <stdint.h>

#include "sgp4ext.h"
#include "sgp4unit.h"
#include "sgp4io.h"
#include "sgp4coord.h"

/**
 * \brief .
 */
typedef enum
{
    daylight,
    eclipsed,
    lighted
} visibletype;

/**
 * \brief .
 */
typedef enum
{
    none,
    enter,
    leave
} shadowtransit;

/**
 * \brief .
 */
typedef struct
{
    double jdstart;
    double jdstop;
    double jdmax;
    double jdtransit;

    double maxelevation;
    double minelevation;    /* Elevation at start and end */
    double transitelevation;

    double azstart;
    double azmax;
    double azstop;
    double aztransit;

    visibletype visstart;
    visibletype visstop;
    visibletype vismax;
    visibletype vistransit;

    visibletype sight;
    shadowtransit transit;
} passinfo;

class Sgp4
{
    char opsmode;
    gravconsttype  whichconst;
    double ro[3];
    double vo[3];
    double razel[3];
    double offset; //Min elevation for overpass prediction in radials
    double sunoffset;  //Min elevation sun for daylight in radials
    double jdC;    //Current used julian date
    double jdCp;    //Current used julian date for prediction

    double sgp4wrap( double jdCe);  //returns the elevation for a given julian date
	double visiblewrap(double jdCe);  //returns angle between sun surface and earth surface

  public:
    char satName[25];   ///satellite name
	char line1[80];     //tle line 1
	char line2[80];     //tle line 2

    double revpday;  ///revolutions per day
    elsetrec satrec;
    double siteLat, siteLon, siteAlt, siteLatRad, siteLonRad;
    double satLat, satLon, satAlt, satAz, satEl, satDist,satJd;
    double sunAz, sunEl;
	int16_t satVis;

    Sgp4();
    bool init(const char naam[], char longstr1[130], char longstr2[130]);  //initialize parameters from 2 line elements
    void site(double lat, double lon, double alt);  //initialize site latitude[degrees],longitude[degrees],altitude[meters]
    void setsunrise(double degrees);   //change the elevation that the sun needs to make it daylight

    void findsat(double jdI);     //find satellite position from julian date
    void findsat(unsigned long);  //find satellite position from unix time

    bool nextpass( passinfo* passdata, int itterations); // calculate next overpass data, returns true if succesfull
	bool nextpass(passinfo* passdata, int itterations, bool direc); //direc = false for forward search, true for backwards search
    bool nextpass(passinfo* passdata, int itterations, bool direc, double minimumElevation); //minimumElevation = minimum elevation above the horizon (in degrees)
    bool initpredpoint( double juliandate , double startelevation); //initialize prediction algorithm, starting from a juliandate and predict passes aboven startelevation
    bool initpredpoint( unsigned long unix, double startelevation); // from unix time

    int16_t visible();  //check if satellite is visible
	int16_t visible(bool& notdark, double& deltaphi);

	double getpredpoint();
	void setpredpoint(double jdCe);
};

#endif /* SGP4PRED_H_ */

/** \} End of sgp4pred group */
