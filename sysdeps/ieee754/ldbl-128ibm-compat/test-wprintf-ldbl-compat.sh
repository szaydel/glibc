#!/bin/sh
# Testing of *w*printf.  IEEE binary128 for powerpc64le version.
# Copyright (C) 2018 Free Software Foundation, Inc.
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
# <http://www.gnu.org/licenses/>.

set -e

test_program=$1; shift
test_program_prefix=$1; shift
test_program_output=$1; shift

status=0

${test_program_prefix} \
  ${test_program} \
  > ${test_program_output} || status=1

cat <<'EOF' |
          fwprintf: -1.000000000000000000000000000000000000000000000000000000000000
          swprintf: -1.000000000000000000000000000000000000000000000000000000000000
           wprintf: -1.000000000000000000000000000000000000000000000000000000000000
         vfwprintf: -1.000000000000000000000000000000000000000000000000000000000000
         vswprintf: -1.000000000000000000000000000000000000000000000000000000000000
          vwprintf: -1.000000000000000000000000000000000000000000000000000000000000
          fwprintf: -0x1.000000000000000000000000000000000000000000000000000000000000p+0
          swprintf: -0x1.000000000000000000000000000000000000000000000000000000000000p+0
           wprintf: -0x1.000000000000000000000000000000000000000000000000000000000000p+0
         vfwprintf: -0x1.000000000000000000000000000000000000000000000000000000000000p+0
         vswprintf: -0x1.000000000000000000000000000000000000000000000000000000000000p+0
          vwprintf: -0x1.000000000000000000000000000000000000000000000000000000000000p+0
EOF
cmp - ${test_program_output} > /dev/null 2>&1 ||
{
  status=1
  echo "*** output comparison failed"
}

exit $status
