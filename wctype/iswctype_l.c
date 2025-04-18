/* Copyright (C) 1996-2025 Free Software Foundation, Inc.
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

#include <ctype.h>
#include <wctype.h>

#define USE_IN_EXTENDED_LOCALE_MODEL	1
#include "wchar-lookup.h"


int
__iswctype_l (wint_t wc, wctype_t desc, locale_t locale)
{
  /* If the user passes in an invalid DESC valid (the one returned from
     `__wctype_l' in case of an error) simply return 0.  */
  if (desc == (wctype_t) 0)
    return 0;

  return wctype_table_lookup ((const char *) desc, wc);
}
weak_alias (__iswctype_l, iswctype_l)
