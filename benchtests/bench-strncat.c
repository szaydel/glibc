/* Measure strncat functions.
   Copyright (C) 2013-2025 Free Software Foundation, Inc.
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

#define TEST_MAIN
#ifndef WIDE
# define TEST_NAME "strncat"
#else
# define TEST_NAME "wcsncat"
# define generic_strncat generic_wcsncat
#endif /* WIDE */
#include "bench-string.h"

#define BIG_CHAR MAX_CHAR

#ifndef WIDE
# define SMALL_CHAR 127
#else
# define SMALL_CHAR 1273
#endif /* WIDE */

#include "json-lib.h"

typedef CHAR *(*proto_t) (CHAR *, const CHAR *, size_t);

CHAR *
generic_strncat (CHAR *dst, const CHAR *src, size_t n)
{
  CHAR *end = dst + STRLEN (dst);
  n = STRNLEN (src, n);
  end[n] = 0;
  MEMCPY (end, src, n);
  return dst;
}

IMPL (STRNCAT, 2)
IMPL (generic_strncat, 0)

static void
do_one_test (json_ctx_t *json_ctx, impl_t *impl, CHAR *dst, const CHAR *src,
	     size_t n)
{
  size_t k = STRLEN (dst), i, iters = INNER_LOOP_ITERS8;
  timing_t start, stop, cur;

  if (CALL (impl, dst, src, n) != dst)
    {
      error (0, 0, "Wrong result in function %s %p != %p", impl->name,
	     CALL (impl, dst, src, n), dst);
      ret = 1;
      return;
    }

  size_t len = STRLEN (src);
  if (MEMCMP (dst + k, src, len + 1 > n ? n : len + 1) != 0)
    {
      error (0, 0, "Incorrect concatenation in function %s", impl->name);
      ret = 1;
      return;
    }
  if (n < len && dst[k + n] != '\0')
    {
      error (0, 0, "There is no zero in the end of output string in %s",
	     impl->name);
      ret = 1;
      return;
    }

  TIMING_NOW (start);
  for (i = 0; i < iters; ++i)
    {
      dst[k] = '\0';
      CALL (impl, dst, src, n);
    }
  TIMING_NOW (stop);

  TIMING_DIFF (cur, start, stop);

  json_element_double (json_ctx, (double) cur / (double) iters);
}

static void
do_test (json_ctx_t *json_ctx, size_t align1, size_t align2, size_t len1,
	 size_t len2, size_t n, int max_char)
{
  size_t i;
  CHAR *s1, *s2;

  align1 &= 7;
  if ((align1 + len1) * sizeof (CHAR) >= page_size)
    return;
  if ((align1 + n) * sizeof (CHAR) > page_size)
    return;
  align2 &= 7;
  if ((align2 + len1 + len2) * sizeof (CHAR) >= page_size)
    return;
  if ((align2 + len1 + n) * sizeof (CHAR) > page_size)
    return;
  s1 = (CHAR *) (buf1) + align1;
  s2 = (CHAR *) (buf2) + align2;

  for (i = 0; i < len1; ++i)
    s1[i] = 32 + 23 * i % (max_char - 32);
  s1[len1] = '\0';

  for (i = 0; i < len2; i++)
    s2[i] = 32 + 23 * i % (max_char - 32);

  json_element_object_begin (json_ctx);
  json_attr_uint (json_ctx, "align1", align1);
  json_attr_uint (json_ctx, "align2", align2);
  json_attr_uint (json_ctx, "len1", len1);
  json_attr_uint (json_ctx, "len2", len2);
  json_attr_uint (json_ctx, "n", n);
  json_attr_uint (json_ctx, "max_char", max_char);

  json_array_begin (json_ctx, "timings");

  FOR_EACH_IMPL (impl, 0)
    {
      s2[len2] = '\0';
      do_one_test (json_ctx, impl, s2, s1, n);
    }

  json_array_end (json_ctx);
  json_element_object_end (json_ctx);
}

int
main (void)
{
  json_ctx_t json_ctx;
  size_t i, n;

  test_init ();

  json_init (&json_ctx, 0, stdout);

  json_document_begin (&json_ctx);
  json_attr_string (&json_ctx, "timing_type", TIMING_TYPE);

  json_attr_object_begin (&json_ctx, "functions");
  json_attr_object_begin (&json_ctx, TEST_NAME);
  json_attr_string (&json_ctx, "bench-variant", "");

  json_array_begin (&json_ctx, "ifuncs");
  FOR_EACH_IMPL (impl, 0)
    json_element_string (&json_ctx, impl->name);
  json_array_end (&json_ctx);

  json_array_begin (&json_ctx, "results");

  for (n = 2; n <= 2048; n *= 4)
    {
      do_test (&json_ctx, 0, 2, 2, 2, n, SMALL_CHAR);
      do_test (&json_ctx, 0, 0, 4, 4, n, SMALL_CHAR);
      do_test (&json_ctx, 4, 0, 4, 4, n, BIG_CHAR);
      do_test (&json_ctx, 0, 0, 8, 8, n, SMALL_CHAR);
      do_test (&json_ctx, 0, 8, 8, 8, n, SMALL_CHAR);

      for (i = 1; i < 8; ++i)
	{
	  do_test (&json_ctx, 0, 0, 8 << i, 8 << i, n, SMALL_CHAR);
	  do_test (&json_ctx, 8 - i, 2 * i, 8 << i, 8 << i, n, SMALL_CHAR);
	  do_test (&json_ctx, 0, 0, 8 << i, 2 << i, n, SMALL_CHAR);
	  do_test (&json_ctx, 8 - i, 2 * i, 8 << i, 2 << i, n, SMALL_CHAR);
	}

      for (i = 1; i < 8; ++i)
	{
	  do_test (&json_ctx, i, 2 * i, 8 << i, 1, n, SMALL_CHAR);
	  do_test (&json_ctx, 2 * i, i, 8 << i, 1, n, BIG_CHAR);
	  do_test (&json_ctx, i, i, 8 << i, 10, n, SMALL_CHAR);
	}
    }

  for (i = 128; i < 2048; i += i)
    {
      for (n = i - 64; n <= i + 64; n += 32)
	{
	  do_test (&json_ctx, 1, 0, i, i, n, SMALL_CHAR);
	  do_test (&json_ctx, 0, i, i, i, n, SMALL_CHAR);
	  do_test (&json_ctx, 0, 0, i, i, n, SMALL_CHAR);
	  do_test (&json_ctx, i, i, i, i, n, SMALL_CHAR);
	  do_test (&json_ctx, 1, 0, i, n, i, SMALL_CHAR);
	  do_test (&json_ctx, 0, i, i, n, i, SMALL_CHAR);
	  do_test (&json_ctx, 0, 0, i, n, i, SMALL_CHAR);
	  do_test (&json_ctx, i, i, i, n, i, SMALL_CHAR);
	}
    }

  json_array_end (&json_ctx);
  json_attr_object_end (&json_ctx);
  json_attr_object_end (&json_ctx);
  json_document_end (&json_ctx);

  return ret;
}
