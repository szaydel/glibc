/* Round argument to nearest integral value according to current rounding
   direction.
   Copyright (C) 1997-2025 Free Software Foundation, Inc.
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

#include <sysdep.h>
#include <libm-alias-float.h>

	.text
ENTRY(__lrintf)
	flds	4(%esp)
	subl	$4, %esp
	cfi_adjust_cfa_offset (4)
	fistpl	(%esp)
	fwait
	popl	%eax
	cfi_adjust_cfa_offset (-4)
	ret
END(__lrintf)
libm_alias_float (__lrint, lrint)
