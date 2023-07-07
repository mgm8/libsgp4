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
 * This file contains miscellaneous functions required for calculating visible satellits.
 * Functions were originally written for Matlab as companion code for "Fundamentals of Astrodynamics 
 * and Applications" by David Vallado (2007). (w) 719-573-2600, email dvallado@agi.com
 *
 * Ported to C++ by Bram Gurdebeke with some modifications, November 2015.
 *
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0.3
 * 
 * \date 2023/07/03
 * 
 * \defgroup visible Visible
 * \{
 */

#ifndef VISIBLE_H_
#define VISIBLE_H_

#include <math.h>

#include "sgp4unit.h"
#include "sgp4ext.h"
#include "sgp4pred.h"

/**
 * \brief Calculates the sun coordinates.
 *
 * \param[in] jd .
 *
 * \param[in] rsun .
 *
 * \return None.
 */
void sun(double jd, double rsun[3]);

#endif /* VISIBLE_H_ */

/** \} End of visible group */
