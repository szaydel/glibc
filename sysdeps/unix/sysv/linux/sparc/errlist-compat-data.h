/* Linux sys_errlist compat symbol definitions.  Sparc version.
   Copyright (C) 2020-2025 Free Software Foundation, Inc.
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

#include <errlist-compat.h>

#if SHLIB_COMPAT (libc, GLIBC_2_0, GLIBC_2_1)
DEFINE_COMPAT_ERRLIST (127, GLIBC_2_0)
#endif

#if SHLIB_COMPAT (libc, GLIBC_2_1, GLIBC_2_3)
DEFINE_COMPAT_ERRLIST (127, GLIBC_2_1)
#endif

#if SHLIB_COMPAT (libc, GLIBC_2_3, GLIBC_2_4)
DEFINE_COMPAT_ERRLIST (128, GLIBC_2_3)
#endif

#if SHLIB_COMPAT (libc, GLIBC_2_4, GLIBC_2_12)
DEFINE_COMPAT_ERRLIST (134, GLIBC_2_4)
#endif

#if SHLIB_COMPAT (libc, GLIBC_2_12, GLIBC_2_16)
DEFINE_COMPAT_ERRLIST (135, GLIBC_2_12)
#endif

#if SHLIB_COMPAT (libc, GLIBC_2_16, GLIBC_2_32)
DEFINE_COMPAT_ERRLIST (136, GLIBC_2_16)
#endif
