ifeq ($(subdir),stdio-common)
# Wrappers for *printf functions that take long double arguments with
# IEEE binary128 format
routines += ieee128-asprintf
routines += ieee128-dprintf
routines += ieee128-fprintf
routines += ieee128-printf
routines += ieee128-snprintf
routines += ieee128-sprintf

routines += ieee128-vasprintf
routines += ieee128-vdprintf
routines += ieee128-vfprintf
routines += ieee128-vprintf
routines += ieee128-vsnprintf
routines += ieee128-vsprintf

routines += ieee128-fwprintf
routines += ieee128-swprintf
routines += ieee128-wprintf

routines += ieee128-vfwprintf
routines += ieee128-vswprintf
routines += ieee128-vwprintf

routines += ieee128-asprintf_chk
routines += ieee128-dprintf_chk
routines += ieee128-fprintf_chk
routines += ieee128-printf_chk
routines += ieee128-snprintf_chk
routines += ieee128-sprintf_chk

routines += ieee128-vasprintf_chk
routines += ieee128-vdprintf_chk
routines += ieee128-vfprintf_chk
routines += ieee128-vprintf_chk
routines += ieee128-vsnprintf_chk
routines += ieee128-vsprintf_chk

routines += ieee128-fwprintf_chk
routines += ieee128-swprintf_chk
routines += ieee128-wprintf_chk

routines += ieee128-vfwprintf_chk
routines += ieee128-vswprintf_chk
routines += ieee128-vwprintf_chk

routines += ieee128-fscanf
routines += ieee128-scanf
routines += ieee128-sscanf

routines += ieee128-vfscanf
routines += ieee128-vscanf
routines += ieee128-vsscanf

routines += ieee128-fwscanf
routines += ieee128-swscanf
routines += ieee128-wscanf

routines += ieee128-vfwscanf
routines += ieee128-vswscanf
routines += ieee128-vwscanf

routines += ieee128-isoc99_fscanf
routines += ieee128-isoc99_scanf
routines += ieee128-isoc99_sscanf

routines += ieee128-isoc99_vfscanf
routines += ieee128-isoc99_vscanf
routines += ieee128-isoc99_vsscanf

routines += ieee128-isoc99_fwscanf
routines += ieee128-isoc99_swscanf
routines += ieee128-isoc99_wscanf

routines += ieee128-isoc99_vfwscanf
routines += ieee128-isoc99_vswscanf
routines += ieee128-isoc99_vwscanf

# Printing long double values with IEEE binary128 format reuses part
# of the internal float128 implementation (__printf_fp, __printf_fphex,
# and __float128 variables and union members).  Likewise, reading these
# values reuses __strtof128_internal.  Thus, the compilation of the
# following functions, must have -mfloat128 passed to the compiler.
CFLAGS-vfprintf-internal.c += -mfloat128
CFLAGS-vfwprintf-internal.c += -mfloat128
CFLAGS-vfscanf-internal.c += -mfloat128
CFLAGS-vfwscanf-internal.c += -mfloat128

# Basic tests for the implementation of long double with IEEE binary128
# format and for the related redirections in installed headers.
tests-internal += test-printf-ieee128 test-printf-ibm128
CFLAGS-test-printf-ieee128.c += -mfloat128 -mabi=ieeelongdouble -Wno-psabi
CFLAGS-test-printf-ibm128.c += -mabi=ibmlongdouble -Wno-psabi

tests-internal += test-wprintf-ieee128 test-wprintf-ibm128
CFLAGS-test-wprintf-ieee128.c += -mfloat128 -mabi=ieeelongdouble -Wno-psabi
CFLAGS-test-wprintf-ibm128.c += -mabi=ibmlongdouble -Wno-psabi

tests-internal += test-printf-chk-ieee128 test-printf-chk-ibm128
CFLAGS-test-printf-chk-ieee128.c += -mfloat128 -mabi=ieeelongdouble -Wno-psabi
CFLAGS-test-printf-chk-ibm128.c += -mabi=ibmlongdouble -Wno-psabi

tests-internal += test-wprintf-chk-ieee128 test-wprintf-chk-ibm128
CFLAGS-test-wprintf-chk-ieee128.c += -mfloat128 -mabi=ieeelongdouble -Wno-psabi
CFLAGS-test-wprintf-chk-ibm128.c += -mabi=ibmlongdouble -Wno-psabi

tests-internal += test-scanf-ieee128 test-scanf-ibm128
CFLAGS-test-scanf-ieee128.c += -mfloat128 -mabi=ieeelongdouble -Wno-psabi
CFLAGS-test-scanf-ibm128.c += -mabi=ibmlongdouble -Wno-psabi

$(objpfx)test-scanf-ieee128: gnulib-tests += $(f128-loader-link)

tests-internal += test-wscanf-ieee128 test-wscanf-ibm128
CFLAGS-test-wscanf-ieee128.c += -mfloat128 -mabi=ieeelongdouble -Wno-psabi
CFLAGS-test-wscanf-ibm128.c += -mabi=ibmlongdouble -Wno-psabi

$(objpfx)test-wscanf-ieee128: gnulib-tests += $(f128-loader-link)

tests-internal += test-isoc99-scanf-ieee128 test-isoc99-scanf-ibm128
CFLAGS-test-isoc99-scanf-ieee128.c += -mfloat128 -mabi=ieeelongdouble -Wno-psabi -std=c99
CFLAGS-test-isoc99-scanf-ibm128.c += -mabi=ibmlongdouble -Wno-psabi -std=c99

$(objpfx)test-isoc99-scanf-ieee128: gnulib-tests += $(f128-loader-link)

tests-internal += test-isoc99-wscanf-ieee128 test-isoc99-wscanf-ibm128
CFLAGS-test-isoc99-wscanf-ieee128.c += -mfloat128 -mabi=ieeelongdouble -Wno-psabi -std=c99
CFLAGS-test-isoc99-wscanf-ibm128.c += -mabi=ibmlongdouble -Wno-psabi -std=c99

$(objpfx)test-isoc99-wscanf-ieee128: gnulib-tests += $(f128-loader-link)

ifeq ($(run-built-tests),yes)
tests-special += $(objpfx)test-printf-ieee128.out
tests-special += $(objpfx)test-printf-ibm128.out

tests-special += $(objpfx)test-wprintf-ieee128.out
tests-special += $(objpfx)test-wprintf-ibm128.out

tests-special += $(objpfx)test-printf-chk-ieee128.out
tests-special += $(objpfx)test-printf-chk-ibm128.out

tests-special += $(objpfx)test-wprintf-chk-ieee128.out
tests-special += $(objpfx)test-wprintf-chk-ibm128.out

tests-special += $(objpfx)test-scanf-ieee128.out
tests-special += $(objpfx)test-scanf-ibm128.out

tests-special += $(objpfx)test-wscanf-ieee128.out
tests-special += $(objpfx)test-wscanf-ibm128.out

tests-special += $(objpfx)test-isoc99-scanf-ieee128.out
tests-special += $(objpfx)test-isoc99-scanf-ibm128.out

tests-special += $(objpfx)test-isoc99-wscanf-ieee128.out
tests-special += $(objpfx)test-isoc99-wscanf-ibm128.out
endif

$(objpfx)test-printf-ieee128.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-printf-ldbl-compat.sh \
  $(objpfx)test-printf-ieee128
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)

$(objpfx)test-printf-ibm128.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-printf-ldbl-compat.sh \
  $(objpfx)test-printf-ibm128
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)

$(objpfx)test-wprintf-ieee128.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-wprintf-ldbl-compat.sh \
  $(objpfx)test-wprintf-ieee128
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)

$(objpfx)test-wprintf-ibm128.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-wprintf-ldbl-compat.sh \
  $(objpfx)test-wprintf-ibm128
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)

$(objpfx)test-printf-chk-ieee128.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-printf-chk-ldbl-compat.sh \
  $(objpfx)test-printf-chk-ieee128
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)

$(objpfx)test-printf-chk-ibm128.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-printf-chk-ldbl-compat.sh \
  $(objpfx)test-printf-chk-ibm128
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)

$(objpfx)test-wprintf-chk-ieee128.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-wprintf-chk-ldbl-compat.sh \
  $(objpfx)test-wprintf-chk-ieee128
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)

$(objpfx)test-wprintf-chk-ibm128.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-wprintf-chk-ldbl-compat.sh \
  $(objpfx)test-wprintf-chk-ibm128
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)

$(objpfx)test-scanf-ieee128.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-scanf-ldbl-compat.sh \
  $(objpfx)test-scanf-ieee128
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)

$(objpfx)test-scanf-ibm128.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-scanf-ldbl-compat.sh \
  $(objpfx)test-scanf-ibm128
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)

$(objpfx)test-wscanf-ieee128.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-scanf-ldbl-compat.sh \
  $(objpfx)test-wscanf-ieee128
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)

$(objpfx)test-wscanf-ibm128.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-scanf-ldbl-compat.sh \
  $(objpfx)test-wscanf-ibm128
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)

$(objpfx)test-isoc99-scanf-ieee128.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-isoc99-scanf-ldbl-compat.sh \
  $(objpfx)test-isoc99-scanf-ieee128
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)

$(objpfx)test-isoc99-scanf-ibm128.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-isoc99-scanf-ldbl-compat.sh \
  $(objpfx)test-isoc99-scanf-ibm128
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)

$(objpfx)test-isoc99-wscanf-ieee128.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-isoc99-scanf-ldbl-compat.sh \
  $(objpfx)test-isoc99-wscanf-ieee128
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)

$(objpfx)test-isoc99-wscanf-ibm128.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-isoc99-scanf-ldbl-compat.sh \
  $(objpfx)test-isoc99-wscanf-ibm128
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)
endif

ifeq ($(subdir),argp)
# Wrappers for argp functions that take long double arguments with
# IEEE binary128 format
routines += ieee128-argp_error
routines += ieee128-argp_failure

tests-internal += test-argp-error-ieee128 test-argp-error-ibm128
CFLAGS-test-argp-error-ieee128.c += -mfloat128 -mabi=ieeelongdouble -Wno-psabi
CFLAGS-test-argp-error-ibm128.c += -mabi=ibmlongdouble -Wno-psabi

tests-internal += test-argp-failure-ieee128 test-argp-failure-ibm128
CFLAGS-test-argp-failure-ieee128.c += -mfloat128 -mabi=ieeelongdouble -Wno-psabi
CFLAGS-test-argp-failure-ibm128.c += -mabi=ibmlongdouble -Wno-psabi

ifeq ($(run-built-tests),yes)
tests-special += $(objpfx)test-argp-error-ieee128.out
tests-special += $(objpfx)test-argp-error-ibm128.out
tests-special += $(objpfx)test-argp-failure-ieee128.out
tests-special += $(objpfx)test-argp-failure-ibm128.out
endif

$(objpfx)test-argp-error-ieee128.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-argp-error-ldbl-compat.sh \
  $(objpfx)test-argp-error-ieee128
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)

$(objpfx)test-argp-error-ibm128.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-argp-error-ldbl-compat.sh \
  $(objpfx)test-argp-error-ibm128
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)

$(objpfx)test-argp-failure-ieee128.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-argp-failure-ldbl-compat.sh \
  $(objpfx)test-argp-failure-ieee128
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)

$(objpfx)test-argp-failure-ibm128.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-argp-failure-ldbl-compat.sh \
  $(objpfx)test-argp-failure-ibm128
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)
endif

ifeq ($(subdir),misc)
# Wrappers for err.h functions that take long double arguments with
# IEEE binary128 format
routines += ieee128-err
routines += ieee128-error

tests-internal += test-warn-ibm128 test-warn-ieee128
CFLAGS-test-warn-ieee128.c += -mfloat128 -mabi=ieeelongdouble -Wno-psabi
CFLAGS-test-warn-ibm128.c += -mabi=ibmlongdouble -Wno-psabi

tests-internal += test-err-ibm128 test-err-ieee128
tests-internal += test-errx-ibm128 test-errx-ieee128
tests-internal += test-verr-ibm128 test-verr-ieee128
tests-internal += test-verrx-ibm128 test-verrx-ieee128
CFLAGS-test-err-ieee128.c += -mfloat128 -mabi=ieeelongdouble -Wno-psabi
CFLAGS-test-err-ibm128.c += -mabi=ibmlongdouble -Wno-psabi
CFLAGS-test-errx-ieee128.c += -mfloat128 -mabi=ieeelongdouble -Wno-psabi
CFLAGS-test-errx-ibm128.c += -mabi=ibmlongdouble -Wno-psabi
CFLAGS-test-verr-ieee128.c += -mfloat128 -mabi=ieeelongdouble -Wno-psabi
CFLAGS-test-verr-ibm128.c += -mabi=ibmlongdouble -Wno-psabi
CFLAGS-test-verrx-ieee128.c += -mfloat128 -mabi=ieeelongdouble -Wno-psabi
CFLAGS-test-verrx-ibm128.c += -mabi=ibmlongdouble -Wno-psabi

tests-internal += test-error1-ibm128 test-error1-ieee128
tests-internal += test-error2-ibm128 test-error2-ieee128
CFLAGS-test-error1-ieee128.c += -mfloat128 -mabi=ieeelongdouble -Wno-psabi
CFLAGS-test-error1-ibm128.c += -mabi=ibmlongdouble -Wno-psabi
CFLAGS-test-error2-ieee128.c += -mfloat128 -mabi=ieeelongdouble -Wno-psabi
CFLAGS-test-error2-ibm128.c += -mabi=ibmlongdouble -Wno-psabi

ifeq ($(run-built-tests),yes)
tests-special += $(objpfx)test-warn-ieee128.out
tests-special += $(objpfx)test-warn-ibm128.out

tests-special += $(objpfx)test-err-ieee128.out
tests-special += $(objpfx)test-err-ibm128.out
tests-special += $(objpfx)test-errx-ieee128.out
tests-special += $(objpfx)test-errx-ibm128.out
tests-special += $(objpfx)test-verr-ieee128.out
tests-special += $(objpfx)test-verr-ibm128.out
tests-special += $(objpfx)test-verrx-ieee128.out
tests-special += $(objpfx)test-verrx-ibm128.out

tests-special += $(objpfx)test-error1-ieee128.out
tests-special += $(objpfx)test-error1-ibm128.out
tests-special += $(objpfx)test-error2-ieee128.out
tests-special += $(objpfx)test-error2-ibm128.out
endif

$(objpfx)test-warn-%.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-warn-ldbl-compat.sh \
  $(objpfx)test-warn-%
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)

$(objpfx)test-err-%.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-err-ldbl-compat.sh \
  $(objpfx)test-err-%
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)

$(objpfx)test-errx-%.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-err-ldbl-compat.sh \
  $(objpfx)test-errx-%
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)

$(objpfx)test-verr-%.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-err-ldbl-compat.sh \
  $(objpfx)test-verr-%
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)

$(objpfx)test-verrx-%.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-err-ldbl-compat.sh \
  $(objpfx)test-verrx-%
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)

$(objpfx)test-error1-%.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-err-ldbl-compat.sh \
  $(objpfx)test-error1-%
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)

$(objpfx)test-error2-%.out: \
  ../sysdeps/ieee754/ldbl-128ibm-compat/test-err-ldbl-compat.sh \
  $(objpfx)test-error2-%
	$(SHELL) $^ '$(test-program-prefix)' $@; \
	$(evaluate-test)
endif
