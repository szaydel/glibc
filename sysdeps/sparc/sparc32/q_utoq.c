/* Software floating-point emulation.
   c = (long double)(a)
   Copyright (C) 1997-2025 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#define FP_NO_EXCEPTIONS
#include "soft-fp.h"
#include "quad.h"

long double _Q_utoq(const unsigned int a)
{
  FP_DECL_Q(C);
  long double c;
  unsigned int b = a;

  FP_FROM_INT_Q(C, b, 32, unsigned int);
  FP_PACK_RAW_Q(c, C);
  return c;
}
