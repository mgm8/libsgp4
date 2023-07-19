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
 * \brief SGP4 extra functions definition.
 * 
 * This file contains extra routines needed for the main test program for SGP4.
 * These routines are derived from the astro libraries.
 *
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0.3
 * 
 * \date 2023/07/03
 * 
 * \defgroup sgp4ext SGP4 Extras
 * \{
 */

#ifndef SGP4EXT_H_
#define SGP4EXT_H_
/*     ----------------------------------------------------------------
*
*                                 sgp4ext.h
*
*
*                            companion code for
*               fundamentals of astrodynamics and applications
*                                    2007
*                              by david vallado
*
*       (w) 719-573-2600, email dvallado@agi.com
*
*    current :
*              20 apr 07  david vallado
*                           misc documentation updates
*    changes :
*              14 aug 06  david vallado
*                           original baseline
*       ----------------------------------------------------------------      */

#include <string.h>
#include <math.h>

#include "sgp4unit.h"

/**
 * \brief .
 *
 * \param[in] x .
 *
 * \return .
 */
double sgn(double x);

/**
 * \brief .
 *
 * \param[in] x .
 *
 * \return .
 */
double mag(double x[3]);

/**
 * \brief .
 *
 * \param[in] vec1 .
 *
 * \param[in] vec2 .
 *
 * \param[in] outvec .
 *
 * \return None.
 */
void cross(double vec1[3], double vec2[3], double outvec[3]);

/**
 * \brief .
 *
 * \param[in] x .
 *
 * \param[in] y .
 *
 * \return .
 */
double dot(double x[3], double y[3]);

/**
 * \brief .
 *
 * \param[in] vec1 .
 *
 * \param[in] vec2 .
 *
 * \return .
 */
double angle(double vec1[3], double vec2[3]);

/**
 * \brief .
 *
 * \param[in] ecc .
 *
 * \param[in] nu .
 *
 * \param[in,out] e0 .
 *
 * \param[in,out] m .
 *
 * \return None.
 */
void newtonnu(double ecc, double nu, double *e0, double *m);

/**
 * \brief .
 *
 * \param[in] xval .
 *
 * \return .
 */
double asinh(double xval);

/**
 * \brief .
 *
 * \param[in] r .
 *
 * \param[in] v .
 *
 * \param[in] mu .
 *
 * \param[in,out] p .
 *
 * \param[in,out] a .
 *
 * \param[in,out] ecc .
 *
 * \param[in,out] incl .
 *
 * \param[in,out] omega .
 *
 * \param[in,out] argp .
 *
 * \param[in,out] nu .
 *
 * \param[in,out] m .
 *
 * \param[in,out] arglat .
 *
 * \param[in,out] truelon .
 *
 * \param[in,out] lonper .
 *
 * \return None.
 */
void rv2coe(double r[3], double v[3], double mu, double *p, double *a, double *ecc, double *incl, double *omega, double *argp, double *nu, double *m, double *arglat, double *truelon, double *lonper);

/**
 * \brief .
 *
 * \param[in] year .
 *
 * \param[in] mon .
 *
 * \param[in] day .
 *
 * \param[in] hr .
 *
 * \param[in] minute .
 *
 * \param[in] sec .
 *
 * \param[in] timezone .
 *
 * \param[in] daylightsaving .
 *
 * \param[in,out] jd .
 *
 * \return None.
 */
void jday(int year, int mon, int day, int hr, int minute, double sec, int timezone, bool daylightsaving, double *jd);

/**
 * \brief .
 *
 * \param[in] year .
 *
 * \param[in] days .
 *
 * \param[in,out] mon .
 *
 * \param[in,out] day .
 *
 * \param[in,out] hr .
 *
 * \param[in,out] minute .
 *
 * \param[in,out] sec .
 *
 * \return None.
 */
void days2mdhms(int year, double days, int *mon, int *day, int *hr, int *minute, double *sec);

/**
 * \brief .
 *
 * \parma[in] jd .
 *
 * \param[in] timezone .
 *
 * \param[in] daylightsaving .
 *
 * \param[in,out] year .
 *
 * \param[in,out] mon .
 *
 * \param[in,out] day .
 *
 * \param[in,out] hr .
 *
 * \param[in,out] minute .
 *
 * \param[in,out] sec .
 *
 * \return None.
 */
void invjday(double jd, int timezone, bool daylightsaving, int *year, int *mon, int *day, int *hr, int *minute, double *sec);

/**
 * \brief .
 *
 * \param[in] a .
 *
 * \param[in] b .
 *
 * \return .
 */
double floatmod(double a, double b);

/**
 * \brief .
 *
 * \param[in] year .
 *
 * \param[in] month .
 *
 * \param[in] day .
 *
 * \param[in] hour .
 *
 * \param[in] tz_hours .
 *
 * \return .
 */
bool summertime(int year, int month, int day, int hour, int tz_hours);

#endif /* SGP4EXT_H_ */

/** \} End of sgp4ext group */
