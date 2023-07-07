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
 * This file contains a function to read two line element sets. while
 * not formerly part of the sgp4 mathematical theory, it is
 * required for practical implemenation.
 *
 * \note Based on Companion Code for Fundamentals of Astrodynamics and Applications, 2007 by David Vallado.
 *
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0.3
 * 
 * \date 2023/07/03
 * 
 * \defgroup sgp4io SGP4 IO
 * \{
 */

#ifndef SGP4IO_H_
#define SGP4IO_H_

#include <stdio.h>
#include <math.h>

#include "sgp4ext.h"    /* For several misc routines */
#include "sgp4unit.h"   /* For sgp4init and getgravconst */

/**
 * \brief .
 *
 * \param[in] longstr1 .
 *
 * \param[in] longstr2 .
 *
 * \param[in] opsmode .
 *
 * \param[in] gravconsttype .
 *
 * \param[in] whichconst .
 *
 * \param[in,out] satrec .
 *
 * \return None.
 */
void twoline2rv(char longstr1[130], char longstr2[130], char opsmode, gravconsttype  whichconst, elsetrec& satrec);

/**
 * \brief .
 *
 * \param[in] longstr .
 *
 * \return .
 */
bool twolineChecksum(const char longstr[]);

#endif /* SGP4IO_H_ */

/** \} End of sgp4io group */
