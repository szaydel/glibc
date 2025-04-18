# Copyright (C) 1991-2025 Free Software Foundation, Inc.
# This file is part of the GNU C Library.

# The GNU C Library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.

# The GNU C Library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.

# You should have received a copy of the GNU Lesser General Public
# License along with the GNU C Library; if not, see
# <https://www.gnu.org/licenses/>.

# errno.texinfo contains lines like:
# @errno{ENOSYS, 123, Function not implemented}

BEGIN {
    print "/* This file generated by errnos.awk from";
    for (i = 1; i < ARGC; i++)
      {
	arg = ARGV[i];
	sub(/.*(manual|include|-gnu)\//, "", arg);
	if (arg ~ /.*errnos.d/) continue;
	print "     " arg;
      }
    print "   Do not edit this file; edit errnos.awk and regenerate it.  */";
    print "";
    print "#ifndef _BITS_ERRNO_H";
    print "#define _BITS_ERRNO_H 1";
    print "";
    print "#if !defined _ERRNO_H";
    print "# error \"Never include <bits/errno.h> directly; use <errno.h> instead.\"";
    print "#endif";

    maxerrno = 0;
    maxerrlen = 0;
    in_mach_errors = "";
    seq = 0;
  }

/^@errno\{/ \
  {
    e = substr($1, 8, length($1)-8)
    if (length(e) > maxerrlen)
      maxerrlen = length(e);
    if (e == "EWOULDBLOCK")
      {
	econsts[seq] = e;
	errnos[seq] = "EAGAIN";
	seq++;
	next;
      }

    errno = substr($2, 1, length($2)-1) + 0;
    if (errno == 0)
      next;
    if (errno > 0x3ffff)
      {
	printf("%s:%d: errno value %d too large for the Hurd\n",
	       FILENAME, NR, errno) >> "/dev/stderr";
	exit 1;
      }
    if (errno > maxerrno)
      maxerrno = errno;

    etext = "";
    for (i = 3; i <= NF; ++i)
      etext = etext " " $i;
    etext = substr(etext, 2, length(etext)-2);

    econsts[seq] = e;
    errnos[seq] = sprintf("0x%08x", 0x40000000 + errno);
    etexts[seq] = etext;
    seq++;
    next;
  }

NF == 3 && $1 == "#define" && $2 == "MACH_SEND_IN_PROGRESS" \
  {
    in_mach_errors = FILENAME;
    annot[seq++] = "\n/* Errors from <mach/message.h>.  */";
  }
NF == 3 && $1 == "#define" && $2 == "KERN_SUCCESS" \
  {
    in_mach_errors = FILENAME;
    annot[seq++] = "\n/* Errors from <mach/kern_return.h>.  */";
    next;
  }

in_mach_errors != "" && $2 == "MACH_IPC_COMPAT" \
  {
    in_mach_errors = "";
  }

# FIXME: mach/message.h and mach/kern_return.h do include error
# descriptions which we could slurp, but some of them are very long,
# we would need to word-wrap them.
in_mach_errors == FILENAME && NF == 3 && $1 == "#define" \
  {
    e = "E" $2;
    if (length(e) > maxerrlen)
      maxerrlen = length(e);
    econsts[seq] = e;
    errnos[seq] = $3;
    etexts[seq] = "";
    seq++;
  }

$1 == "#define" && $2 == "_MACH_MIG_ERRORS_H_" \
  {
    in_mig_errors = 1;
    annot[seq++] = "\n/* Errors from <mach/mig_errors.h>.  */";
    next;
  }
in_mig_errors && $1 == "#endif" && $3 == "_MACH_MIG_ERRORS_H_" \
  {
    in_mig_errors = 0;
  }

(in_mig_errors && $1 == "#define" && $3 <= -300) || \
(in_device_errors && $1 == "#define" && /D_/ && NF > 3) \
  {
    etext = "";
    for (i = 5; i < NF; ++i)
      etext = etext " " $i;

    e = "E" $2;
    if (length(e) > maxerrlen)
      maxerrlen = length(e);
    econsts[seq] = e;
    errnos[seq] = $3;
    etexts[seq] = substr(etext, 2, length(etext)-1);
    seq++;
  }

$1 == "#define" && $2 == "D_SUCCESS" \
  {
    in_device_errors = 1;
    annot[seq++] = "\n/* Errors from <device/device_types.h>.  */";
    next;
  }
in_device_errors && $1 == "#endif" \
  {
    in_device_errors = 0;
  }

function print_errno_enum(maxseq)
{
  print "";
  print "#ifndef __ASSEMBLER__";
  print "";
  print "enum __error_t_codes";
  print "{";
  print "  /* The value zero always means success and it is perfectly fine";
  print "     for code to use 0 explicitly (or implicitly, e.g. via Boolean";
  print "     coercion.)  Having an enum entry for zero both makes the";
  print "     debugger print the name for error_t-typed zero values, and";
  print "     prevents the compiler from issuing warnings about 'case 0:'";
  print "     in a switch on an error_t-typed value.  */";
  printf("  %-*s = 0,\n", maxerrlen, "ESUCCESS");

  print "";
  print "  /* The Hurd uses Mach error system 0x10, subsystem 0. */";
  for (i = 0; i < maxseq; i++)
    {
      if (i in annot)
	print annot[i];
      else if (i in etexts && etexts[i] != "")
	printf("  %-*s = %s,\t/* %s */\n",
	       maxerrlen, econsts[i], errnos[i], etexts[i]);
      else if (errnos[i] != "EAGAIN")
	printf("  %-*s = %s,\n", maxerrlen, econsts[i], errnos[i]);
    }

  print "";
  print "  /* Because the C standard requires that errno have type 'int',"
  print "     this enumeration must be a signed type.  */";
  print "  __FORCE_ERROR_T_CODES_SIGNED = -1";
  print "};";
  print "";
  print "#endif /* not __ASSEMBLER__ */";
}

function print_errno_defines(maxseq)
{
  print "";
  print "/* The C standard requires that all of the E-constants be"
  print "   defined as macros.  */"
  print "";
  for (i = 0; i < maxseq; i++)
    {
      if (i in annot)
	print annot[i];
      else
	printf("#define %-*s %s\n", maxerrlen, econsts[i], errnos[i]);
    }
  print "";
  printf("#define _HURD_ERRNOS %d\n", maxerrno+1);
}

END \
  {
    print_errno_enum(seq);
    print_errno_defines(seq);

    print "";
    print "#endif /* bits/errno.h.  */";
  }
