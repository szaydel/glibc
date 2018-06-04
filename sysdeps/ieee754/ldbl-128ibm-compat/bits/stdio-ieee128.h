/* Redirections for stdio functions for -mabi=ieeelongdouble.
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
   format is not complete.  The redirections of the stdio.h functions
   are supposed to be implemented in bits/stdio-ldbl.h, however, we can
   only redirect all or none.  In the meantime, bits/stdio-ieee128.h
   allows us to redirect part of them for testing purposes.  */

#ifndef _STDIO_H
# error "Never include <bits/stdio-ieee128.h> directly; use <stdio.h> instead."
#endif

#define __IEEE128_REDIR(name) \
  extern __typeof (name) __##name##ieee128; \
  extern __typeof (name) name __asm (__ASMNAME ("__" #name "ieee128"));

#define __IEEE128_REDIR_CUSTOM(name, custom) \
  extern __typeof (name) custom; \
  extern __typeof (name) name __asm (__ASMNAME (#custom));

#define __IEEE128_REDIR_PREFIX(name) \
  extern __typeof (__##name) __##name##ieee128; \
  extern __typeof (__##name) __##name __asm (__ASMNAME ("__" #name "ieee128"));

__IEEE128_REDIR (fprintf)
__IEEE128_REDIR (printf)
__IEEE128_REDIR (sprintf)
__IEEE128_REDIR (vfprintf)
__IEEE128_REDIR (vprintf)
__IEEE128_REDIR (vsprintf)
#if defined __USE_ISOC99 && !defined __USE_GNU \
    && (defined __STRICT_ANSI__ || defined __USE_XOPEN2K)
__IEEE128_REDIR_CUSTOM (fscanf, __isoc99_fscanfieee128)
__IEEE128_REDIR_CUSTOM (scanf, __isoc99_scanfieee128)
__IEEE128_REDIR_CUSTOM (sscanf, __isoc99_sscanfieee128)
#else
__IEEE128_REDIR (fscanf)
__IEEE128_REDIR (scanf)
__IEEE128_REDIR (sscanf)
#endif

#if defined __USE_ISOC99 || defined __USE_UNIX98
__IEEE128_REDIR (snprintf)
__IEEE128_REDIR (vsnprintf)
#endif

#ifdef	__USE_ISOC99
# if !defined __USE_GNU \
     && (defined __STRICT_ANSI__ || defined __USE_XOPEN2K)
__IEEE128_REDIR_CUSTOM (vfscanf, __isoc99_vfscanfieee128)
__IEEE128_REDIR_CUSTOM (vscanf, __isoc99_vscanfieee128)
__IEEE128_REDIR_CUSTOM (vsscanf, __isoc99_vsscanfieee128)
# else
__IEEE128_REDIR (vfscanf)
__IEEE128_REDIR (vsscanf)
__IEEE128_REDIR (vscanf)
# endif
#endif

#ifdef __USE_XOPEN2K8
__IEEE128_REDIR (vdprintf)
__IEEE128_REDIR (dprintf)
#endif

#ifdef __USE_GNU
__IEEE128_REDIR (vasprintf)
__IEEE128_REDIR (__asprintf)
__IEEE128_REDIR (asprintf)
__IEEE128_REDIR (obstack_printf)
__IEEE128_REDIR (obstack_vprintf)
#endif

#if __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
__IEEE128_REDIR_PREFIX (sprintf_chk)
__IEEE128_REDIR_PREFIX (vsprintf_chk)
# if defined __USE_ISOC99 || defined __USE_UNIX98
__IEEE128_REDIR_PREFIX (snprintf_chk)
__IEEE128_REDIR_PREFIX (vsnprintf_chk)
# endif
# if __USE_FORTIFY_LEVEL > 1
__IEEE128_REDIR_PREFIX (fprintf_chk)
__IEEE128_REDIR_PREFIX (printf_chk)
__IEEE128_REDIR_PREFIX (vfprintf_chk)
__IEEE128_REDIR_PREFIX (vprintf_chk)
#  ifdef __USE_XOPEN2K8
__IEEE128_REDIR_PREFIX (dprintf_chk)
__IEEE128_REDIR_PREFIX (vdprintf_chk)
#  endif
#  ifdef __USE_GNU
__IEEE128_REDIR_PREFIX (asprintf_chk)
__IEEE128_REDIR_PREFIX (vasprintf_chk)
__IEEE128_REDIR_PREFIX (obstack_printf_chk)
__IEEE128_REDIR_PREFIX (obstack_vprintf_chk)
#  endif
# endif
#endif
/* To be completed with the other functions.  */
