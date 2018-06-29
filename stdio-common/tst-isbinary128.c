/* Test for the behaviour of 'is_binary128' in printf_size.
   Copyright (C) 2018 Free Software Foundation, Inc.
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
   <http://www.gnu.org/licenses/>.  */

#include <printf.h>
#include <stdio.h>
#include <string.h>

#include <support/check.h>

static int
do_test (void)
{
  double d = 2000;
  double *dptr = &d;
  long double ld = 4000;
  long double *ldptr = & ld;
  struct printf_info info;

  memset (&info, 0, sizeof (info));
  info.spec = L'f';

  /* First, call printf_size with 'is_long_double' and 'is_binary128'
     both zeroed.  */
  printf_size (stdout, &info, (void *) &dptr);

  /* Then test that setting 'is_binary128' to one still prints double
     correctly.  */
  info.is_binary128 = 1;
  printf_size (stdout, &info, (void *) &dptr);

  /* Finally, check that long double values are also printed correctly,
     provided that 'is_binary128' is zeroed.  */
  info.is_long_double = 1;
  info.is_binary128 = 0;
  printf_size (stdout, &info, (void *) &ldptr);

  /* Setting both 'is_long_double' and 'is_binary128' to one is out of
     the scope of this test, because such configuration is only valid
     when _Float128 and long double are ABI-distinct (which is not
     always true and this is an arch-independent test).  */
  return 0;
}

#include <support/test-driver.c>
