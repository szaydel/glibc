/* Test the support_quote_blob function.
   Copyright (C) 2018-2025 Free Software Foundation, Inc.
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

#include <support/check.h>
#include <support/support.h>
#include <string.h>
#include <stdlib.h>

static int
do_test (void)
{
  /* Check handling of the empty blob, both with and without trailing
     NUL byte.  */
  char *p = support_quote_blob ("", 0);
  TEST_COMPARE (strlen (p), 0);
  free (p);
  p = support_quote_blob ("X", 0);
  TEST_COMPARE (strlen (p), 0);
  free (p);

  /* Check escaping of backslash-escaped characters, and lack of
     escaping for other shell meta-characters.  */
  p = support_quote_blob ("$()*?`@[]{}~\'\"X", 14);
  TEST_COMPARE (strcmp (p, "$()*?`@[]{}~\\'\\\""), 0);
  free (p);

  /* Check lack of escaping for letters and digits.  */
#define LETTERS_AND_DIGTS                       \
  "abcdefghijklmnopqrstuvwxyz"                  \
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"                  \
  "0123456789"
  p = support_quote_blob (LETTERS_AND_DIGTS "@", 2 * 26 + 10);
  TEST_COMPARE (strcmp (p, LETTERS_AND_DIGTS), 0);
  free (p);

  /* Check escaping of control characters and other non-printable
     characters.  */
  p = support_quote_blob ("\r\n\t\a\b\f\v\1\177\200\377\0@", 14);
  TEST_COMPARE (strcmp (p, "\\r\\n\\t\\a\\b\\f\\v\\001"
                        "\\177\\200\\377\\000@\\000"), 0);
  free (p);

  return 0;
}

#include <support/test-driver.c>
