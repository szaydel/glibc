/* Copyright (C) 2002-2025 Free Software Foundation, Inc.
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

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static int do_test (void);

#define TEST_FUNCTION do_test ()
#include "../test-skeleton.c"

static void *tf (void *a)
{
  flockfile (stdout);
  /* This call should never return.  */
  return a;
}


int
do_test (void)
{
  pthread_t th;

  flockfile (stdout);

  if (pthread_create (&th, NULL, tf, NULL) != 0)
    {
      write_message ("create failed\n");
      _exit (1);
    }

  delayed__exit (1);
  xpthread_join (th);

  puts ("join returned");

  return 1;
}
