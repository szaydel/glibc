/* Declaration for error-reporting function
   Copyright (C) 1995-2018 Free Software Foundation, Inc.
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

#ifndef _ERROR_H
#define _ERROR_H 1

#include <features.h>


__BEGIN_DECLS

/* Print a message with `fprintf (stderr, FORMAT, ...)';
   if ERRNUM is nonzero, follow it with ": " and strerror (ERRNUM).
   If STATUS is nonzero, terminate the program with `exit (STATUS)'.  */

extern void error (int __status, int __errnum, const char *__format, ...)
     __attribute__ ((__format__ (__printf__, 3, 4)));

extern void error_at_line (int __status, int __errnum, const char *__fname,
			   unsigned int __lineno, const char *__format, ...)
     __attribute__ ((__format__ (__printf__, 5, 6)));

/* If NULL, error will flush stdout, then print on stderr the program
   name, a colon and a space.  Otherwise, error will call this
   function without parameters instead.  */
extern void (*error_print_progname) (void);

/* This variable is incremented each time `error' is called.  */
extern unsigned int error_message_count;

/* Sometimes we want to have at most one error per line.  This
   variable controls whether this mode is selected or not.  */
extern int error_one_per_line;


/* XXX: DO NOT COMMIT.

   On powerpc64le, the implementation of long double with IEEE binary128
   format is not complete.  The redirections of the error.h functions
   are temporarily implemented in bits/error-ieee128.h.  */
#include <bits/floatn.h>
#if __HAVE_DISTINCT_FLOAT128 && __LDBL_MANT_DIG__ == 113 && \
    ! defined __BUILDING_EXTRA_LDBL_FORMAT
# include <bits/error-ieee128.h>
#else

/* XXX: The following redirections cause calls to error_at_line and
   error to be always inlined.  That doesn't work with ieee128
   redirections, yet.  */
# if defined __extern_always_inline && defined __va_arg_pack
#  include <bits/error.h>
# endif

#endif

__END_DECLS

#endif /* error.h */
