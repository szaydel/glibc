/* Test for the long double variants of *warn* functions.
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
#include <stdarg.h>

#include <support/check.h>

static void
do_test_call_varg (const char *format, ...)
{
  va_list args;

  va_start (args, format);
  vwarn (format, args);
  va_end (args);

  va_start (args, format);
  vwarnx (format, args);
  va_end (args);
}

static void
do_test_call_rarg (const char *format, long double ld)
{
  warn (format, ld);
  warnx (format, ld);
}

static int
do_test (void)
{
  long double ld = -1;

  /* Print in decimal notation.  */
  do_test_call_rarg ("%.60Lf", ld);
  do_test_call_varg ("%.60Lf", ld);

  /* Print in hexadecimal notation.  */
  do_test_call_rarg ("%.60La", ld);
  do_test_call_varg ("%.60La", ld);

  return 0;
}

#include <support/test-driver.c>
