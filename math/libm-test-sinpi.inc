/* Test sinpi.
   Copyright (C) 2024-2025 Free Software Foundation, Inc.
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

#include "libm-test-driver.c"

static const struct test_f_f_data sinpi_test_data[] =
  {
    TEST_f_f (sinpi, plus_infty, qnan_value, INVALID_EXCEPTION|ERRNO_EDOM),
    TEST_f_f (sinpi, minus_infty, qnan_value, INVALID_EXCEPTION|ERRNO_EDOM),
    TEST_f_f (sinpi, qnan_value, qnan_value, NO_INEXACT_EXCEPTION|ERRNO_UNCHANGED),
    TEST_f_f (sinpi, -qnan_value, qnan_value, NO_INEXACT_EXCEPTION|ERRNO_UNCHANGED),
    TEST_f_f (sinpi, snan_value, qnan_value, INVALID_EXCEPTION),
    TEST_f_f (sinpi, -snan_value, qnan_value, INVALID_EXCEPTION),

    AUTO_TESTS_f_f (sinpi),
  };

static void
sinpi_test (void)
{
  ALL_RM_TEST (sinpi, 0, sinpi_test_data, RUN_TEST_LOOP_f_f, END);
}

static void
do_test (void)
{
  sinpi_test ();
}

/*
 * Local Variables:
 * mode:c
 * End:
 */
