/* Test for the long double variants of argp* functions.
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

#include <argp.h>
#include <string.h>

#include <support/check.h>

static const struct argp_option
options[] =
{
  { "test", 't', "format", 0, "Run argp function with a format string", 0 },
  { NULL, 0, NULL, 0, NULL }
};

static error_t
parser (int key, char *arg, struct argp_state *state)
{
  switch (key)
    {
      case 't':
	ARGP_FUNCTION ARGP_FUNCTION_PARAMS;
	break;
      default:
	return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

static struct argp
argp =
{
  options, parser
};

static int
do_test (void)
{
  int remaining;
  int argc = 3;
  char *argv[4] =
    {
      (char *) "test-argp",
      (char *) "--test",
      (char *) "%.60Lf",
      NULL
    };

  argp_parse (&argp, argc, argv, 0, &remaining, NULL);

  return 0;
}

#include <support/test-driver.c>
