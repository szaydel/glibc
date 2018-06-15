/* Test for the long double variants of *err* functions.
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

#include <err.h>
#include <error.h>
#include <stdarg.h>

#include <support/check.h>

static void
do_test_call (long double ld, const char *format, ...)
{
  va_list args;

  va_start (args, format);
  ERROR_FUNCTION ERROR_FUNCTION_PARAMS;
  va_end (args);
}

static int
do_test (void)
{
  long double ld = -1;

  do_test_call (ld, "%.60Lf", ld);

  return 0;
}

#include <support/test-driver.c>
