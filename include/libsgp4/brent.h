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
 * \brief Brent's method functions definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0.3
 * 
 * \date 2023/07/03
 * 
 * \defgroup brent Brent
 * \{
 */

#ifndef BRENT_H_
#define BRENT_H_

#include "sgp4pred.h"

/**
 * \brief .
 *
 * Given a function f, and given a bracketing triplet of abscissas ax, bx, cx (such that bx is
 * between ax and cx, and f(bx) is less than both f(ax) and f(cx)), this routine isolates
 * the minimum to a fractional precision of about tol using Brent’s method. The abscissa of
 * the minimum is returned as xmin, and the minimum function value is returned as brent, the
 * returned function value.
 *
 * \param[in] ax .
 *
 * \param[in] bx .
 *
 * \param[in] cx .
 *
 * \param[in] .
 *
 * \param[in] tol .
 *
 * \param[in] xmin .
 *
 * \param[in] obj .
 *
 * \return .
 */
double brentmin(double ax, double bx, double cx, double (Sgp4::*f)(double), double tol, double *xmin,  Sgp4* obj);

/**
 * \brief .
 *
 * Using Brent’s method, find the root of a function func known to lie between x1 and x2. The
 * root, returned as zbrent, will be refined until its accuracy is tol.
 *
 * \param[in] .
 *
 * \param[in] x1 .
 *
 * \param[in] x2 .
 *
 * \param[in] tol .
 *
 * \param[in] .
 *
 * \return .
 */
double zbrent(double (Sgp4::*func)(double), double x1, double x2, double tol, Sgp4* obj);

#endif /* BRENT_H_ */

/** \} End of brent group */
