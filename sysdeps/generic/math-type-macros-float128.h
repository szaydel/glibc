/* Helper macros for _Float128 variants of type generic functions of libm.
   Copyright (C) 2017-2025 Free Software Foundation, Inc.
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

#ifndef _MATH_TYPE_MACROS_FLOAT128
#define _MATH_TYPE_MACROS_FLOAT128

#include <fenv_private.h>

#define M_LIT(c) __f128 (c)
#define M_PFX FLT128
#define M_SUF(c) c ## f128
#define FLOAT _Float128
#define M_STRTO_NAN __strtof128_nan
#define M_USE_BUILTIN(c) USE_ ##c ##F128_BUILTIN

#define CFLOAT __CFLOAT128

#define M_MLIT(c) c ## f128

/* fenv_private.h may not define SET_RESTORE_ROUNDF128.  */
#ifdef SET_RESTORE_ROUNDF128
# define M_SET_RESTORE_ROUND(RM) SET_RESTORE_ROUNDF128 (RM)
#else
# define M_SET_RESTORE_ROUND(RM) SET_RESTORE_ROUNDL (RM)
#endif

#include <libm-alias-float128.h>
#include <math-nan-payload-float128.h>

#ifndef declare_mgen_alias
# define declare_mgen_alias(from, to) libm_alias_float128 (from, to)
#endif

#ifndef declare_mgen_alias_r
# define declare_mgen_alias_r(from, to) libm_alias_float128_r (from, to, _r)
#endif

#ifndef declare_mgen_alias_narrow
# define declare_mgen_alias_narrow(from, to)	\
  libm_alias_float128_narrow (from, to)
#endif

/* Supply the generic macros.  */
#include <math-type-macros.h>

/* Use the type-generic wrapper templates.  */
#define __USE_WRAPPER_TEMPLATE 1

#endif
