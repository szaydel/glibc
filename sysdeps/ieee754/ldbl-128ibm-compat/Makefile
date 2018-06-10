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

# Printing long double values with IEEE binary128 format reuses part
# of the internal float128 implementation (__printf_fp, __printf_fphex,
# and __float128 variables and union members).  Thus, the compilation of
# the following functions, must have -mfloat128 passed to the compiler.
CFLAGS-vfprintf-internal.c += -mfloat128
CFLAGS-vfwprintf-internal.c += -mfloat128

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

ifeq ($(run-built-tests),yes)
tests-special += $(objpfx)test-printf-ieee128.out
tests-special += $(objpfx)test-printf-ibm128.out

tests-special += $(objpfx)test-wprintf-ieee128.out
tests-special += $(objpfx)test-wprintf-ibm128.out

tests-special += $(objpfx)test-printf-chk-ieee128.out
tests-special += $(objpfx)test-printf-chk-ibm128.out
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
endif
