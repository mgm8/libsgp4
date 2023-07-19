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
 * This file contains the sgp4 procedures for analytical propagation
 * of a satellite. the code was originally released in the 1980 and 1986
 * spacetrack papers. a detailed discussion of the theory and history
 * may be found in the 2006 aiaa paper by vallado, crawford, hujsak,
 * and kelso.
 *
 * \note Based on Companion Code for Fundamentals of Astrodynamics and Applications, 2007 by David Vallado.
 *
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0.3
 * 
 * \date 2023/07/03
 * 
 * \defgroup sgp4unit SGP4 Unit
 * \{
 */

#ifndef SGP4UNIT_H_
#define SGP4UNIT_H_

#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#define SGP4Version  "SGP4 Version 2011-12-30"

#define pi 3.14159265358979323846

/**
 * \brief .
 */
typedef enum
{
    wgs72old,
    wgs72,
    wgs84
} gravconsttype;

/**
 * \brief .
 */
typedef struct elsetrec
{
    long int satnum;
    int epochyr, epochtynumrev;
    int error;
    char operationmode;
    char init, method;

    /* Near Earth */
    int isimp;
    double aycof,   con41,  cc1,        cc4,    cc5,    d2,         d3,     d4,
           delmo,   eta,    argpdot,    omgcof, sinmao, t,          t2cof,  t3cof,
           t4cof,   t5cof,  x1mth2,     x7thm1, mdot,   nodedot,    xlcof,  xmcof,
           nodecf;

    /* Deep Space */
    int irez;
    double d2201,   d2211,  d3210,  d3222,  d4410,  d4422,  d5220,  d5232,
           d5421,   d5433,  dedt,   del1,   del2,   del3,   didt,   dmdt,
           dnodt,   domdt,  e3,     ee2,    peo,    pgho,   pho,    pinco,
           plo,     se2,    se3,    sgh2,   sgh3,   sgh4,   sh2,    sh3,
           si2,     si3,    sl2,    sl3,    sl4,    gsto,   xfact,  xgh2,
           xgh3,    xgh4,   xh2,    xh3,    xi2,    xi3,    xl2,    xl3,
           xl4,     xlamo,  zmol,   zmos,   atime,  xli,    xni;

    double a,       altp,   alta,   epochdays,  jdsatepoch, nddot,  ndot,
           bstar,   rcse,   inclo,  nodeo,      ecco,       argpo,  mo,
           no;
} elsetrec;

/**
 * \brief .
 *
 * \param[in] whichconst .
 *
 * \param[in] opsmode .
 *
 * \param[in] satn .
 *
 * \param[in] epoch .
 *
 * \param[in] xbstar .
 *
 * \param[in] xecco .
 *
 * \param[in] xargpo .
 *
 * \param[in] xinclo .
 *
 * \param[in] xmo .
 *
 * \param[in] xno .
 *
 * \param[in] xnodeo .
 *
 * \param[in,out] satrec .
 *
 * \return .
 */
bool sgp4init(gravconsttype whichconst, char opsmode, const int satn, const double epoch, const double xbstar, const double xecco, const double xargpo, const double xinclo, const double xmo, const double xno, const double xnodeo, elsetrec *satrec);

/**
 * \brief .
 *
 * \param[in] whichconst .
 *
 * \param[in] satrec .
 *
 * \param[in] tsince .
 *
 * \param[in] r .
 *
 * \param[in] v .
 *
 * \return .
 */
bool sgp4(gravconsttype whichconst, elsetrec *satrec, double tsince, double r[3], double v[3]);

/**
 * \brief .
 *
 * \param[in] jdut1 .
 *
 * \return .
 */
double gstime(double jdut1);

/**
 * \brief .
 *
 * \parma[in] whichconst .
 *
 * \param[in,out] tumin .
 *
 * \param[in,out] mu .
 *
 * \param[in,out] radiusearthkm .
 *
 * \parma[in,out] xke .
 *
 * \param[in,out] j2 .
 *
 * \param[in,out] j3 .
 *
 * \param[in,out] j4 .
 *
 * \param[in,out] j3oj2 .
 *
 * \return None.
 */
void getgravconst(gravconsttype whichconst, double *tumin, double *mu, double *radiusearthkm, double *xke, double *j2, double *j3, double *j4, double *j3oj2);

#endif /* SGP4UNIT_H_ */

/** \} End of sgp4unit group */
