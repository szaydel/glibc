/* Linux getrlimit64 implementation (64 bits rlim_t).
   Copyright (C) 2010-2025 Free Software Foundation, Inc.
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

#include <errno.h>
#include <sys/types.h>
#include <sysdep.h>
#include <shlib-compat.h>

/* Add this redirection so the strong_alias for __RLIM_T_MATCHES_RLIM64_T
   linking getrlimit64 to {__}getrlimit does not throw a type error.  */
#undef getrlimit
#undef __getrlimit
#define getrlimit getrlimit_redirect
#define __getrlimit __getrlimit_redirect
#include <sys/resource.h>
#undef getrlimit
#undef __getrlimit

/* Put the soft and hard limits for RESOURCE in *RLIMITS.
   Returns 0 if successful, -1 if not (and sets errno).  */
int
__getrlimit64 (enum __rlimit_resource resource, struct rlimit64 *rlimits)
{
  return INLINE_SYSCALL_CALL (prlimit64, 0, resource, NULL, rlimits);
}
libc_hidden_def (__getrlimit64)

#if __RLIM_T_MATCHES_RLIM64_T
/* If both rlim_t and rlimt64_t are essentially the same type we can use
   alias both interfaces.  */
strong_alias (__getrlimit64, __GI_getrlimit)
strong_alias (__getrlimit64, __GI___getrlimit)
strong_alias (__getrlimit64, __getrlimit)
/* Alpha defines a versioned getrlimit{64}.  */
# ifndef USE_VERSIONED_RLIMIT
weak_alias (__getrlimit64, getrlimit)
weak_alias (__getrlimit64, getrlimit64)
libc_hidden_weak (getrlimit64)
# else
weak_alias (__getrlimit64, __GI_getrlimit64)
# endif

#elif SHLIB_COMPAT (libc, GLIBC_2_1, GLIBC_2_2)
/* Back compatible 2GiB limited rlimit.  */
extern int __new_getrlimit (enum __rlimit_resource, struct rlimit *)
  attribute_hidden;

int
attribute_compat_text_section
__old_getrlimit64 (enum __rlimit_resource resource, struct rlimit64 *rlimits)
{
  struct rlimit rlimits32;

  if (__new_getrlimit (resource, &rlimits32) < 0)
    return -1;

  if (rlimits32.rlim_cur == RLIM_INFINITY)
    rlimits->rlim_cur = RLIM64_INFINITY >> 1;
  else
    rlimits->rlim_cur = rlimits32.rlim_cur;
  if (rlimits32.rlim_max == RLIM_INFINITY)
    rlimits->rlim_max = RLIM64_INFINITY >> 1;
  else
    rlimits->rlim_max = rlimits32.rlim_max;

  return 0;
}
versioned_symbol (libc, __getrlimit64, getrlimit64, GLIBC_2_2);
compat_symbol (libc, __old_getrlimit64, getrlimit64, GLIBC_2_1);
#else
weak_alias (__getrlimit64, getrlimit64)
libc_hidden_weak (getrlimit64)
#endif /* __RLIM_T_MATCHES_RLIM64_T  */
