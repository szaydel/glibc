/* Machine-dependent details of interruptible RPC messaging.  i386 version.
   Copyright (C) 1995-2025 Free Software Foundation, Inc.
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


/* Note that we must mark OPTION and TIMEOUT as outputs of this operation,
   to indicate that the signal thread might mutate them as part
   of sending us to a signal handler.  */

#define INTR_MSG_TRAP(msg, option, send_size, rcv_size, rcv_name, timeout, notify, cancel_p, intr_port_p) \
({									      \
  error_t err;								      \
  asm (".globl _hurd_intr_rpc_msg_about_to\n"				      \
       ".globl _hurd_intr_rpc_msg_setup_done\n"				      \
       ".globl _hurd_intr_rpc_msg_in_trap\n"				      \
       /* Clear eax before we do the check for cancel below.  This is to
          detect eax being set to non-zero (actually MACH_SEND_INTERRUPTED)
          from the outside (namely, _hurdsig_abort_rpcs), which signals us
          to skip the trap we were about to enter.  */			      \
       "				xorl %0, %0\n"			      \
       "_hurd_intr_rpc_msg_about_to:"					      \
       /* We need to make a last check of cancel, in case we got interrupted
          right before _hurd_intr_rpc_msg_about_to.  */			      \
       "				cmpl $0, %5\n"			      \
       "				jz _hurd_intr_rpc_msg_do\n"	      \
       /* We got interrupted, note so and return EINTR.  */		      \
       "				movl $0, %3\n"			      \
       "				movl %6, %0\n"			      \
       "				jmp _hurd_intr_rpc_msg_sp_restored\n" \
       "_hurd_intr_rpc_msg_do:"						      \
       /* Ok, push the mach_msg_trap arguments and a fake return address.  */ \
       "				pushl 24(%4)\n"			      \
       "				pushl %2\n"			      \
       "				pushl 16(%4)\n"			      \
       "				pushl 12(%4)\n"			      \
       "				pushl 8(%4)\n"			      \
       "				pushl %1\n"			      \
       "				pushl (%4)\n"			      \
       "				pushl $0\n"			      \
       "_hurd_intr_rpc_msg_setup_done:"					      \
       /* From here on, it is safe to make us jump over the syscall.  Now
          check if we have been told to skip the syscall while running
          the above.  */						      \
       "				test %0, %0\n"			      \
       "				jnz _hurd_intr_rpc_msg_in_trap\n"     \
       /* Do the actual syscall.  */					      \
       "				movl $-25, %%eax\n"		      \
       "_hurd_intr_rpc_msg_do_trap:	lcall $7, $0 # status in %0\n"	      \
       "_hurd_intr_rpc_msg_in_trap:"					      \
       /* Ok, clean the arguments and update OPTION and TIMEOUT.  */	      \
       "				addl $8, %%esp\n"		      \
       "				popl %1\n"			      \
       "				addl $12, %%esp\n"		      \
       "				popl %2\n"			      \
       "				addl $4, %%esp\n"		      \
       "_hurd_intr_rpc_msg_sp_restored:"				      \
       : "=&a" (err), "+r" (option), "+r" (timeout), "=m" (*intr_port_p)      \
       : "r" (&msg), "m" (*cancel_p), "i" (EINTR));			      \
  err;									      \
})

#include "hurdfault.h"

/* This cannot be an inline function because it calls setjmp.  */
#define SYSCALL_EXAMINE(state, callno)					      \
({									      \
  struct { unsigned int c[2]; } *p = (void *) ((state)->eip - 7);	      \
  int result;								      \
  if (_hurdsig_catch_memory_fault (p))					      \
    return 0;								      \
  if (result = p->c[0] == 0x0000009a && (p->c[1] & 0x00ffffff) == 0x00000700) \
    /* The PC is just after an `lcall $7,$0' instruction.		      \
       This is a system call in progress; %eax holds the call number.  */     \
    *(callno) = (state)->eax;						      \
  _hurdsig_end_catch_fault ();						      \
  result;								      \
})


struct mach_msg_trap_args
  {
    void *retaddr;		/* Address mach_msg_trap will return to.  */
    /* This is the order of arguments to mach_msg_trap.  */
    mach_msg_header_t *msg;
    mach_msg_option_t option;
    mach_msg_size_t send_size;
    mach_msg_size_t rcv_size;
    mach_port_t rcv_name;
    mach_msg_timeout_t timeout;
    mach_port_t notify;
  };


/* This cannot be an inline function because it calls setjmp.  */
#define MSG_EXAMINE(state, msgid, rcvname, send_name, opt, tmout)	      \
({									      \
  const struct mach_msg_trap_args *args = (const void *) (state)->uesp;	      \
  mach_msg_header_t *msg;						      \
  _hurdsig_catch_memory_fault (args) ? -1 :				      \
    ({									      \
      msg = args->msg;							      \
      *(opt) = args->option;						      \
      *(tmout) = args->timeout;						      \
      *(rcvname) = args->rcv_name;					      \
      _hurdsig_end_catch_fault ();					      \
      if (msg == 0)							      \
	{								      \
	  *(send_name) = MACH_PORT_NULL;				      \
	  *(msgid) = 0;							      \
	}								      \
      else								      \
	{								      \
	  if (_hurdsig_catch_memory_fault (msg))			      \
	    return -1;							      \
	  *(send_name) = msg->msgh_remote_port;				      \
	  *(msgid) = msg->msgh_id;					      \
	  _hurdsig_end_catch_fault ();					      \
	}								      \
      0;								      \
    });									      \
})
