/* Test for the long double variants of *printf functions.
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

#include <support/check.h>

static void
do_test_call_varg (FILE *stream, const char *format, ...)
{
  char *buffer = NULL;
  char string[128];
  va_list args;

  printf ("%20s", "vasprintf: ");
  va_start (args, format);
  vasprintf (&buffer, format, args);
  va_end (args);
  if (buffer == NULL)
    printf ("Error using vasprintf\n");
  else
    {
      printf ("%s", buffer);
      free (buffer);
    }
  printf ("\n");

  printf ("%20s", "vdprintf: ");
  va_start (args, format);
  vdprintf (1, format, args);
  va_end (args);
  printf ("\n");

  printf ("%20s", "vfprintf: ");
  va_start (args, format);
  vfprintf (stream, format, args);
  va_end (args);
  printf ("\n");

  printf ("%20s", "vprintf: ");
  va_start (args, format);
  vprintf (format, args);
  va_end (args);
  printf ("\n");

  printf ("%20s", "vsnprintf: ");
  va_start (args, format);
  vsnprintf (string, 127, format, args);
  va_end (args);
  printf ("%s", string);
  printf ("\n");

  printf ("%20s", "vsprintf: ");
  va_start (args, format);
  vsprintf (string, format, args);
  va_end (args);
  printf ("%s", string);
  printf ("\n");
}

static void
do_test_call_rarg (FILE *stream, const char *format, long double ld)
{
  char *buffer = NULL;
  char string[128];

  printf ("%20s", "asprintf: ");
  asprintf (&buffer, format, ld);
  if (buffer == NULL)
    printf ("Error using asprintf\n");
  else
    {
      printf ("%s", buffer);
      free (buffer);
    }
  printf ("\n");

  printf ("%20s", "dprintf: ");
  dprintf (1, format, ld);
  printf ("\n");

  printf ("%20s", "fprintf: ");
  fprintf (stdout, format, ld);
  printf ("\n");

  printf ("%20s", "printf: ");
  printf (format, ld);
  printf ("\n");

  printf ("%20s", "snprintf: ");
  snprintf (string, 127, format, ld);
  printf ("%s", string);
  printf ("\n");

  printf ("%20s", "sprintf: ");
  sprintf (string, format, ld);
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
