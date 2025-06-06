/* Vector optimized 32/64 bit S/390 version of wcslen.
   Copyright (C) 2015-2025 Free Software Foundation, Inc.
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

#include <ifunc-wcslen.h>
#if HAVE_WCSLEN_Z13

# include "sysdep.h"
# include "asm-syntax.h"

	.text

/* size_t wcslen (const wchar_t *s)
   Returns length of string s.

   Register usage:
   -r1=bytes to 4k-byte boundary
   -r2=s
   -r3=tmp
   -r4=tmp
   -r5=current_len and return_value
   -v16=part of s
*/
ENTRY(WCSLEN_Z13)
	.machine "z13"
	.machinemode "zarch_nohighgprs"

	vlbb	%v16,0(%r2),6	/* Load s until next 4k-byte boundary.  */
	lcbb	%r1,0(%r2),6	/* Get bytes to 4k-byte boundary or 16.  */

	tmll	%r2,3		/* Test if s is 4-byte aligned?   */
	jne	.Lfallback	/* And use common-code variant if not.  */

	vfenezf	%v16,%v16,%v16	/* Find element not equal with zero search.  */
	vlgvb	%r4,%v16,7	/* Load zero index or 16 if not found.  */
	clr	%r4,%r1		/* If found zero within loaded bytes?  */
	locgrl	%r2,%r4		/* Then copy return value.  */
	jl	.Lend		/* And return.  */

	/* Align s to 16 byte.  */
	risbgn	%r3,%r2,60,128+63,0 /* %r3 = bits 60-63 of %r2 'and' 15.  */
	lghi	%r5,16		/* current_len = 16.  */
	slr	%r5,%r3		/* Compute bytes to 16bytes boundary.  */

	/* Find zero in 16byte aligned loop.  */
.Lloop:
	vl	%v16,0(%r5,%r2)	/* Load s.  */
	vfenezfs %v16,%v16,%v16	/* Find element not equal with zero search.  */
	je	.Lfound		/* Jump away if zero was found.  */
	vl	%v16,16(%r5,%r2)
	vfenezfs %v16,%v16,%v16
	je	.Lfound16
	vl	%v16,32(%r5,%r2)
	vfenezfs %v16,%v16,%v16
	je	.Lfound32
	vl	%v16,48(%r5,%r2)
	vfenezfs %v16,%v16,%v16
	je	.Lfound48

	aghi	%r5,64
	j	.Lloop		/* No zero found -> loop.  */

.Lfound48:
	aghi	%r5,16
.Lfound32:
	aghi	%r5,16
.Lfound16:
	aghi	%r5,16
.Lfound:
	vlgvb	%r2,%v16,7	/* Load byte index of zero.  */
	algr	%r2,%r5
.Lend:
	srlg	%r2,%r2,2	/* Convert byte-count to character-count.  */
	br	%r14
.Lfallback:
	jg	WCSLEN_C
END(WCSLEN_Z13)

# if ! HAVE_WCSLEN_IFUNC
strong_alias (WCSLEN_Z13, __wcslen)
weak_alias (__wcslen, wcslen)
# endif
#endif
