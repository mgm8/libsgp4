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

/**
 * \brief .
 */
typedef struct
{
    char opsmode;
    gravconsttype whichconst;
    double ro[3];
    double vo[3];
    double razel[3];
    double offset;      /* Min elevation for overpass prediction in radials */
    double sunoffset;   /* Min elevation sun for daylight in radials */
    double jdC;         /* Current used julian date */
    double jdCp;        /* Current used julian date for prediction */

    double sgp4wrap( double jdCe);      /* returns the elevation for a given julian date */
    double visiblewrap(double jdCe);    /* returns angle between sun surface and earth surface */

    char satName[25];   /* satellite name */
    char line1[80];     /* tle line 1 */
    char line2[80];     /* tle line 2 */

    double revpday;     /* revolutions per day */
    elsetrec satrec;
    double siteLat, siteLon, siteAlt, siteLatRad, siteLonRad;
    double satLat, satLon, satAlt, satAz, satEl, satDist,satJd;
    double sunAz, sunEl;
    int16_t satVis;
} sgp4_t;

/**
 * \brief Initialize parameters from 2 line elements.
 *
 * \param[in] naam .
 *
 * \param[in] longstr1 .
 *
 * \param[in] longstr2 .
 *
 * \
 */
bool sgp4_init(sgp4_t *conf, const char naam[], char longstr1[130], char longstr2[130]);

/**
 * \brief Initialize site latitude[degrees],longitude[degrees],altitude[meters].
 *
 * \param[in] lat .
 *
 * \param[in] lon .
 *
 * \param[in] alt .
 *
 * \return None.
 */
void sgp4_site(sgp4_t *conf, double lat, double lon, double alt);

/**
 * \brief Change the elevation that the sun needs to make it daylight.
 *
 * \param[in] degrees .
 *
 * \return None.
 */
void sgp4_setsunrise(sgp4_t *conf, double degrees);

/**
 * \brief Find satellite position from julian date.
 *
 * \param[in] jdI .
 *
 * \return None.
 */
void sgp4_findsat(sgp4_t *conf, double jdI);

/**
 * \brief Find satellite position from unix time.
 *
 * \param[in] .
 *
 * \return None.
 */
void sgp4_findsat(sgp4_t *conf, unsigned long);

/**
 * \brief Calculate next overpass data, returns true if succesfull.
 *
 * \param[in,out] passdata .
 *
 * \param[in] itterations .
 *
 * \reutrn .
 */
bool sgp4_nextpass(sgp4_t *conf, passinfo *passdata, int itterations);

/**
 * \brief Direc = false for forward search, true for backwards search.
 *
 * \param[in,out] passdata .
 *
 * \param[in] itterations .
 *
 * \param[in] direc .
 *
 * \return .
 */
bool sgp4_nextpass(sgp4_t *conf, passinfo *passdata, int itterations, bool direc);

/**
 * \brief MinimumElevation = minimum elevation above the horizon (in degrees).
 *
 * \param[in,out] passdata .
 *
 * \param[in] itterations .
 *
 * \param[in] direc .
 *
 * \param[in] minimumElevation .
 *
 * \return .
 */
bool sgp4_nextpass(sgp4_t *conf, passinfo *passdata, int itterations, bool direc, double minimumElevation);

/**
 * \brief Initialize prediction algorithm, starting from a juliandate and predict passes aboven startelevation.
 *
 * \param[in] juliandata .
 *
 * \param[in] startelevation .
 *
 * \return .
 */
bool sgp4_initpredpoint(sgp4_t *conf, double juliandate, double startelevation);

/**
 * \brief From unix time.
 *
 * \param[in] unix .
 *
 * \param[in] startelevation .
 *
 * \return .
 */
bool sgp4_initpredpoint(sgp4_t *conf, unsigned long unix, double startelevation);

/**
 * \brief Check if satellite is visible.
 *
 * \return .
 */
int16_t sgp4_visible(sgp4_t *conf);

/**
 * \brief .
 *
 * \param[in,out] notdark .
 *
 * \param[in,out] deltaphi .
 *
 * \return .
 */
int16_t sgp4_visible(sgp4_t *conf, bool *notdark, double *deltaphi);

/**
 * \brief .
 *
 * \return .
 */
double sgp4_getpredpoint(sgp4_t *conf);

/**
 * \brief .
 *
 * \param[in] jdCe .
 *
 * \return None.
 */
void sgp4_setpredpoint(sgp4_t *conf, double jdCe);

#endif /* SGP4PRED_H_ */

/** \} End of sgp4pred group */
