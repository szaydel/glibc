/* Optimized strcasecmp_l implementation for POWER7.
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

#define __strcasecmp_l __strcasecmp_l_power7

#undef weak_alias
#define weak_alias(name, alias)

#undef libc_hidden_builtin_def
#define libc_hidden_builtin_def(name)

#define USE_IN_EXTENDED_LOCALE_MODEL
#define __STRCMP __strcasecmp_l
#define STRCMP   strcasecmp_l

#include <sysdeps/powerpc/powerpc64/power7/strcasecmp.S>
