/* Test for the long double variants of *printf_chk functions.
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

#define _FORTIFY_SOURCE 2

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

#include <support/check.h>

static void
do_test_call_varg (FILE *stream, const char *format, ...)
{
  char *buffer = NULL;
  char string[128];
  int res;
  va_list args;

  printf ("%20s", "__vasprintf_chk: ");
  va_start (args, format);
  res = __vasprintf_chk (&buffer, 1, format, args);
  va_end (args);
  if (res == -1)
    printf ("Error using vasprintf\n");
  if (buffer == NULL)
    printf ("Error using vasprintf\n");
  else
    {
      printf ("%s", buffer);
      free (buffer);
    }
  printf ("\n");

  printf ("%20s", "__vdprintf_chk: ");
  va_start (args, format);
  __vdprintf_chk (1, 1, format, args);
  va_end (args);
  printf ("\n");

  printf ("%20s", "__vfprintf_chk: ");
  va_start (args, format);
  __vfprintf_chk (stream, 1, format, args);
  va_end (args);
  printf ("\n");

  printf ("%20s", "__vprintf_chk: ");
  va_start (args, format);
  __vprintf_chk (1, format, args);
  va_end (args);
  printf ("\n");

  printf ("%20s", "__vsnprintf_chk: ");
  va_start (args, format);
  __vsnprintf_chk (string, 79, 1, 127, format, args);
  va_end (args);
  printf ("%s", string);
  printf ("\n");

  printf ("%20s", "__vsprintf_chk: ");
  va_start (args, format);
  __vsprintf_chk (string, 1, 127, format, args);
  va_end (args);
  printf ("%s", string);
  printf ("\n");
}

static void
do_test_call_rarg (FILE *stream, const char *format, long double ld)
{
  char *buffer = NULL;
  char string[128];
  int res;

  printf ("%20s", "__asprintf_chk: ");
  res = __asprintf_chk (&buffer, 1, format, ld);
  if (res == -1)
    printf ("Error using vasprintf\n");
  if (buffer == NULL)
    printf ("Error using asprintf\n");
  else
    {
      printf ("%s", buffer);
      free (buffer);
    }
  printf ("\n");

  printf ("%20s", "__dprintf_chk: ");
  __dprintf_chk (1, 1, format, ld);
  printf ("\n");

  printf ("%20s", "__fprintf_chk: ");
  __fprintf_chk (stdout, 1, format, ld);
  printf ("\n");

  printf ("%20s", "__printf_chk: ");
  __printf_chk (1, format, ld);
  printf ("\n");

  printf ("%20s", "__snprintf_chk: ");
  __snprintf_chk (string, 79, 1, 127, format, ld);
  printf ("%s", string);
  printf ("\n");

  printf ("%20s", "__sprintf_chk: ");
  __sprintf_chk (string, 1, 127, format, ld);
  printf ("%s", string);
  printf ("\n");
}

static int
do_test (void)
{
  long double ld = -1;

  /* Print in decimal notation.  */
  do_test_call_rarg (stdout, "%.60Lf", ld);
  do_test_call_varg (stdout, "%.60Lf", ld);

  /* Print in hexadecimal notation.  */
  do_test_call_rarg (stdout, "%.60La", ld);
  do_test_call_varg (stdout, "%.60La", ld);

  return 0;
}

#include <support/test-driver.c>
