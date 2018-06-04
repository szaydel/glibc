/* Redirections for error functions for -mabi=ieeelongdouble.
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

/* XXX: DO NOT COMMIT.

   On powerpc64le, the implementation of long double with IEEE binary128
   format is not complete.  The redirections of the err.h functions
   are temporarily implemented in bits/err-ieee128.h.  */

#ifndef _ERROR_H
# error "Never include <bits/error-ieee128.h> directly; use <error.h> instead."
#endif

#define __IEEE128_REDIR(name) \
  extern __typeof (name) __##name##ieee128; \
  extern __typeof (name) name __asm (__ASMNAME ("__" #name "ieee128"));

__IEEE128_REDIR (error)
__IEEE128_REDIR (error_at_line)
