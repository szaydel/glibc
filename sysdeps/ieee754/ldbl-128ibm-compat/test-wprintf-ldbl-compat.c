/* Test for the long double variants of *w*printf functions.
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

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <wchar.h>

#include <support/check.h>

static void
do_test_call_varg (FILE *stream, const wchar_t *format, ...)
{
  wchar_t string[128];
  va_list args;

  wprintf (L"%20Ls", L"vfwprintf: ");
  va_start (args, format);
  vfwprintf (stream, format, args);
  va_end (args);
  wprintf (L"\n");

  wprintf (L"%20Ls", L"vswprintf: ");
  va_start (args, format);
  vswprintf (string, 127, format, args);
  va_end (args);
  wprintf (L"%Ls", string);
  wprintf (L"\n");

  wprintf (L"%20Ls", L"vwprintf: ");
  va_start (args, format);
  vwprintf (format, args);
  va_end (args);
  wprintf (L"\n");
}

static void
do_test_call_rarg (FILE *stream, const wchar_t *format, long double ld,
		   double d)
{
  wchar_t string[128];

  wprintf (L"%20Ls", L"fwprintf: ");
  fwprintf (stream, format, ld, d);
  wprintf (L"\n");

  wprintf (L"%20Ls", L"swprintf: ");
  swprintf (string, 127, format, ld, d);
  wprintf (L"%Ls", string);
  wprintf (L"\n");

  wprintf (L"%20Ls", L"wprintf: ");
  wprintf (format, ld, d);
  wprintf (L"\n");
}

static int
do_test (void)
{
  long double ld = -1;
  double d = -1;

  /* Print in decimal notation.  */
  do_test_call_rarg (stdout, L"%.60Lf, %f", ld, d);
  do_test_call_varg (stdout, L"%.60Lf, %f", ld, d);

  /* Print in hexadecimal notation.  */
  do_test_call_rarg (stdout, L"%.60La, %a", ld, d);
  do_test_call_varg (stdout, L"%.60La, %a", ld, d);

  return 0;
}

#include <support/test-driver.c>
