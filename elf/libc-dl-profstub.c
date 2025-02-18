/* Helper definitions for profiling of shared libraries.
   Copyright (C) 1998-2025 Free Software Foundation, Inc.
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

#include <dlfcn.h>
#include <elf.h>
#include <ldsodefs.h>
#include <shlib-compat.h>

/* This is the map for the shared object we profile.  It is defined here
   only because we test for this value being NULL or not.  */

#if SHLIB_COMPAT(libc, GLIBC_2_1, GLIBC_2_40)
attribute_compat_text_section
void
_dl_mcount_wrapper (void *selfpc)
{
  GLRO(dl_mcount) ((ElfW(Addr)) RETURN_ADDRESS (0), (ElfW(Addr)) selfpc);
}

compat_symbol (libc, _dl_mcount_wrapper, _dl_mcount_wrapper, GLIBC_2_1);
#endif

void
_dl_mcount_wrapper_check (void *selfpc)
{
  if (GL(dl_profile_map) != NULL)
    GLRO(dl_mcount) ((ElfW(Addr)) RETURN_ADDRESS (0), (ElfW(Addr)) selfpc);
}
libc_hidden_def (_dl_mcount_wrapper_check)
