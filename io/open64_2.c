/* _FORTIFY_SOURCE wrapper for open64.
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

#include <fcntl.h>
#include <stdio.h>

int
__open64_2 (const char *file, int oflag)
{
  if (__OPEN_NEEDS_MODE (oflag))
    __fortify_fail ("invalid open64 call: O_CREAT or O_TMPFILE without mode");

  return __open64 (file, oflag);
}
