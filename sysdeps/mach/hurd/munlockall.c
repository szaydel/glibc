/* munlockall -- undo the effects of all prior mlock calls.  Hurd version.
   Copyright (C) 2001-2025 Free Software Foundation, Inc.
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

#include <sys/types.h>
#include <sys/mman.h>
#include <errno.h>
#include <hurd.h>
#include <mach/mach_host.h>

/* Undo the effects of all prior mlock calls in this process.  */

int
munlockall (void)
{
  mach_port_t host;
  error_t err;

  err = __get_privileged_ports (&host, NULL);
  if (err)
    return __hurd_fail (err);

  err = __vm_wire_all (host, __mach_task_self (), VM_WIRE_NONE);
  __mach_port_deallocate (__mach_task_self (), host);
  return err ? __hurd_fail (err) : 0;
}
