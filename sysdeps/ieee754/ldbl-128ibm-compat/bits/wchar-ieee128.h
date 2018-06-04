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
   format is not complete.  The redirections of the wchar.h functions
   are supposed to be implemented in bits/wchar-ldbl.h, however, we can
   only redirect all or none.  In the meantime, bits/wchar-ieee128.h
   allows us to redirect part of them for testing purposes.  */

#ifndef _WCHAR_H
# error "Never include <bits/wchar-ieee128.h> directly; use <wchar.h> instead."
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

#if defined __USE_ISOC95 || defined __USE_UNIX98
__IEEE128_REDIR (fwprintf);
__IEEE128_REDIR (wprintf);
__IEEE128_REDIR (swprintf);
__IEEE128_REDIR (vfwprintf);
__IEEE128_REDIR (vwprintf);
__IEEE128_REDIR (vswprintf);
# if defined __USE_ISOC99 && !defined __USE_GNU \
     && (defined __STRICT_ANSI__ || defined __USE_XOPEN2K)
__IEEE128_REDIR_CUSTOM (fwscanf, __isoc99_fwscanfieee128)
__IEEE128_REDIR_CUSTOM (wscanf, __isoc99_wscanfieee128)
__IEEE128_REDIR_CUSTOM (swscanf, __isoc99_swscanfieee128)
# else
__IEEE128_REDIR (fwscanf);
__IEEE128_REDIR (wscanf);
__IEEE128_REDIR (swscanf);
# endif
#endif

#ifdef __USE_ISOC99
#if 0
__IEEE128_REDIR_CUSTOM (wcstold, wcstod);
#endif
# if !defined __USE_GNU \
     && (defined __STRICT_ANSI__ || defined __USE_XOPEN2K)
__IEEE128_REDIR_CUSTOM (vfwscanf, __isoc99_vfwscanfieee128)
__IEEE128_REDIR_CUSTOM (vwscanf, __isoc99_vwscanfieee128)
__IEEE128_REDIR_CUSTOM (vswscanf, __isoc99_vswscanfieee128)
# else
__IEEE128_REDIR (vfwscanf);
__IEEE128_REDIR (vwscanf);
__IEEE128_REDIR (vswscanf);
# endif
#endif

#if 0
#ifdef __USE_GNU
__IEEE128_REDIR_CUSTOM (wcstold_l, wcstod_l);
#endif
#endif

#if __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
__IEEE128_REDIR_PREFIX (swprintf_chk)
__IEEE128_REDIR_PREFIX (vswprintf_chk)
# if __USE_FORTIFY_LEVEL > 1
__IEEE128_REDIR_PREFIX (fwprintf_chk)
__IEEE128_REDIR_PREFIX (wprintf_chk)
__IEEE128_REDIR_PREFIX (vfwprintf_chk)
__IEEE128_REDIR_PREFIX (vwprintf_chk)
# endif
#endif
