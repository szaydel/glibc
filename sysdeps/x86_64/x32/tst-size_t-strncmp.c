/* Test strncmp with size_t in the lower 32 bits of 64-bit register.
   Copyright (C) 2019-2025 Free Software Foundation, Inc.
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

#ifdef WIDE
# define TEST_NAME "wcsncmp"
#else
# define TEST_NAME "strncmp"
#endif

#include "test-size_t.h"

#ifdef WIDE
# include <wchar.h>

# define STRNCMP wcsncmp
# define STRNCPY wcsncpy
# define CHAR wchar_t
#else
# define STRNCMP strncmp
# define STRNCPY strncpy
# define CHAR char
#endif

IMPL (STRNCMP, 1)

typedef int (*proto_t) (const CHAR *, const CHAR *, size_t);


static int
__attribute__ ((noinline, noclone))
do_strncmp (parameter_t a, parameter_t b)
{
  return CALL (&b, a.p, b.p, a.len);
}

static int
test_main (void)
{
  test_init ();

  size_t size = page_size / sizeof (CHAR);
  parameter_t dest = { { size }, buf1 };
  parameter_t src = { { 0 }, buf2 };

  STRNCPY ((CHAR *) buf1, (const CHAR *) buf2, size);

  int ret = 0;
  FOR_EACH_IMPL (impl, 0)
    {
      src.fn = impl->fn;
      int res = do_strncmp (dest, src);
      if (res)
	{
	  error (0, 0, "Wrong result in function %s: %i != 0",
		 impl->name, res);
	  ret = 1;
	}
    }

  return ret ? EXIT_FAILURE : EXIT_SUCCESS;
}

#include <support/test-driver.c>
