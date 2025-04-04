/* Install given floating-point environment and raise exceptions for
   atomic compound assignment.
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
   License along with the GNU C Library.  If not, see
   <https://www.gnu.org/licenses/>.  */

#include "soft-fp.h"
#include "soft-supp.h"
#include <signal.h>

void
__atomic_feupdateenv (const fenv_t *envp)
{
  fenv_union_t u;
  int saved_exceptions = __sim_exceptions_thread;

  /* This function postdates the global variables being turned into
     compat symbols, so no need to set them.  */
  u.fenv = *envp;
  __sim_exceptions_thread |= u.l[0];
  __sim_disabled_exceptions_thread = u.l[1];
  if (saved_exceptions & ~__sim_disabled_exceptions_thread)
    raise (SIGFPE);
}
