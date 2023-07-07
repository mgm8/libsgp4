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
 * \date 2023/07/03
 * 
 * \defgroup sgp4 SGP4
 * \{
 */

#ifndef SGP4COORD_H_
#define SGP4COORD_H_

/*     
sgp4coord.h

This file contains miscellaneous functions required for coordinate transformation.
Functions were originally written for Matlab as companion code for "Fundamentals of Astrodynamics 
and Applications" by David Vallado (2007). (w) 719-573-2600, email dvallado@agi.com

Ported to C++ by Grady Hillhouse with some modifications, July 2015.
*/

#include <math.h>
#include <string.h>

//void teme2ecef(double rteme[3], double vteme[3], double jdut1, double recef[3], double vecef[3]);

/**
 * \brief .
 *
 * \param[in] rteme .
 *
 * \param[in] jdut1 .
 *
 * \param[in] recef .
 *
 * \return None.
 */
void teme2ecef(double rteme[3], double jdut1, double recef[3]);

/**
 * \brief .
 *
 * \param[in] jdut1 .
 *
 * \param[in] pm .
 *
 * \return None.
 */
void polarm(double jdut1, double pm[3][3]);

/**
 * \brief .
 *
 * \param[in] r .
 *
 * \param[in] latlongh .
 *
 * \return None.
 */
void ijk2ll(double r[3], double latlongh[3]);

//void site(double latgd, double lon, double alt, double rs[3], double vs[3]);

/**
 * \brief .
 *
 * \param[in] latgd .
 *
 * \param[in] lon .
 *
 * \param[in] alt .
 *
 * \param[in] rs .
 *
 * \return None.
 */
void site(double latgd, double lon, double alt, double rs[3]);

//void rv2azel(double ro[3], double vo[3], double latgd, double lon, double alt, double jdut1, double razel[3], double razelrates[3]);

/**
 * \brief .
 *
 * \param[in] ro .
 *
 * \param[in] latgd .
 *
 * \param[in] lon .
 *
 * \param[in] alt .
 *
 * \param[in] jdut1 .
 *
 * \param[in] razel .
 *
 * \return None.
 */
void rv2azel(double ro[3], double latgd, double lon, double alt, double jdut1, double razel[3]);

/**
 * \brief .
 *
 * \param[in] invec .
 *
 * \param[in] xval .
 *
 * \param[in] outvec .
 *
 * \return None.
 */
void rot3(double invec[3], double xval, double outvec[3]);

/**
 * \brief .
 *
 * \param[in] invec .
 *
 * \param[in] xval .
 *
 * \param[in] outvec .
 *
 * \return None.
 */
void rot2(double invec[3], double xval, double outvec[3]);

/**
 * \brief .
 *
 * \param[in] unix_secs .
 *
 * \return .
 */
double getJulianFromUnix(double unixSecs);

/**
 * \brief .
 *
 * \param[in] julian .
 *
 * \return .
 */
unsigned long getUnixFromJulian(double julian);

#endif /* SGP4COORD_H_ */

/** \} End of sgp4coord group */
