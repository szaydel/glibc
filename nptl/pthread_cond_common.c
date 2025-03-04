/* pthread_cond_common -- shared code for condition variable.
   Copyright (C) 2016-2025 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <atomic.h>
#include <atomic_wide_counter.h>
#include <stdint.h>
#include <pthread.h>

/* We need 3 least-significant bits on __wrefs for something else.
   This also matches __atomic_wide_counter requirements: The highest
   value we add is __PTHREAD_COND_MAX_GROUP_SIZE << 2 to __g1_start
   (the two extra bits are for the lock in the two LSBs of
   __g1_start).  */
#define __PTHREAD_COND_MAX_GROUP_SIZE ((unsigned) 1 << 29)

static inline uint64_t
__condvar_load_wseq_relaxed (pthread_cond_t *cond)
{
  return __atomic_wide_counter_load_relaxed (&cond->__data.__wseq);
}

static inline uint64_t
__condvar_fetch_add_wseq_acquire (pthread_cond_t *cond, unsigned int val)
{
  return __atomic_wide_counter_fetch_add_acquire (&cond->__data.__wseq, val);
}

static inline uint64_t
__condvar_load_g1_start_relaxed (pthread_cond_t *cond)
{
  return __atomic_wide_counter_load_relaxed (&cond->__data.__g1_start);
}

static inline void
__condvar_add_g1_start_relaxed (pthread_cond_t *cond, unsigned int val)
{
  __atomic_wide_counter_add_relaxed (&cond->__data.__g1_start, val);
}

#if __HAVE_64B_ATOMICS == 1

static inline uint64_t
__condvar_fetch_xor_wseq_release (pthread_cond_t *cond, unsigned int val)
{
  return atomic_fetch_xor_release (&cond->__data.__wseq.__value64, val);
}

#else /* !__HAVE_64B_ATOMICS */

/* The xor operation needs to be an atomic read-modify-write.  The write
   itself is not an issue as it affects just the lower-order half but not bits
   used in the add operation.  To make the full fetch-and-xor atomic, we
   exploit that concurrently, the value can increase by at most 1<<31 (*): The
   xor operation is only called while having acquired the lock, so not more
   than __PTHREAD_COND_MAX_GROUP_SIZE waiters can enter concurrently and thus
   increment __wseq.  Therefore, if the xor operation observes a value of
   __wseq, then the value it applies the modification to later on can be
   derived.  */

static uint64_t __attribute__ ((unused))
__condvar_fetch_xor_wseq_release (pthread_cond_t *cond, unsigned int val)
{
  /* First, get the current value.  See __atomic_wide_counter_load_relaxed.  */
  unsigned int h, l, h2;
  do
    {
      h = atomic_load_acquire (&cond->__data.__wseq.__value32.__high);
      l = atomic_load_acquire (&cond->__data.__wseq.__value32.__low);
      h2 = atomic_load_relaxed (&cond->__data.__wseq.__value32.__high);
    }
  while (h != h2);
  if (((l >> 31) > 0) && ((h >> 31) == 0))
    h++;
  h &= ~((unsigned int) 1 << 31);
  l &= ~((unsigned int) 1 << 31);

  /* Now modify.  Due to the coherence rules, the prior load will read a value
     earlier in modification order than the following fetch-xor.
     This uses release MO to make the full operation have release semantics
     (all other operations access the lower-order half).  */
  unsigned int l2
    = (atomic_fetch_xor_release (&cond->__data.__wseq.__value32.__low, val)
       & ~((unsigned int) 1 << 31));
  if (l2 < l)
    /* The lower-order half overflowed in the meantime.  This happened exactly
       once due to the limit on concurrent waiters (see above).  */
    h++;
  return ((uint64_t) h << 31) + l2;
}

#endif /* !__HAVE_64B_ATOMICS */

/* The lock that signalers use.  See pthread_cond_wait_common for uses.
   The lock is our normal three-state lock: not acquired (0) / acquired (1) /
   acquired-with-futex_wake-request (2).  However, we need to preserve the
   other bits in the unsigned int used for the lock, and therefore it is a
   little more complex.  */
static void __attribute__ ((unused))
__condvar_acquire_lock (pthread_cond_t *cond, int private)
{
  unsigned int s = atomic_load_relaxed (&cond->__data.__g1_orig_size);
  while ((s & 3) == 0)
    {
      if (atomic_compare_exchange_weak_acquire (&cond->__data.__g1_orig_size,
	  &s, s | 1))
	return;
      /* TODO Spinning and back-off.  */
    }
  /* We can't change from not acquired to acquired, so try to change to
     acquired-with-futex-wake-request and do a futex wait if we cannot change
     from not acquired.  */
  while (1)
    {
      while ((s & 3) != 2)
	{
	  if (atomic_compare_exchange_weak_acquire
	      (&cond->__data.__g1_orig_size, &s, (s & ~(unsigned int) 3) | 2))
	    {
	      if ((s & 3) == 0)
		return;
	      break;
	    }
	  /* TODO Back off.  */
	}
      futex_wait_simple (&cond->__data.__g1_orig_size,
	  (s & ~(unsigned int) 3) | 2, private);
      /* Reload so we see a recent value.  */
      s = atomic_load_relaxed (&cond->__data.__g1_orig_size);
    }
}

/* See __condvar_acquire_lock.  */
static void __attribute__ ((unused))
__condvar_release_lock (pthread_cond_t *cond, int private)
{
  if ((atomic_fetch_and_release (&cond->__data.__g1_orig_size,
				 ~(unsigned int) 3) & 3)
      == 2)
    futex_wake (&cond->__data.__g1_orig_size, 1, private);
}

/* Only use this when having acquired the lock.  */
static unsigned int __attribute__ ((unused))
__condvar_get_orig_size (pthread_cond_t *cond)
{
  return atomic_load_relaxed (&cond->__data.__g1_orig_size) >> 2;
}

/* Only use this when having acquired the lock.  */
static void __attribute__ ((unused))
__condvar_set_orig_size (pthread_cond_t *cond, unsigned int size)
{
  /* We have acquired the lock, but might get one concurrent update due to a
     lock state change from acquired to acquired-with-futex_wake-request.
     The store with relaxed MO is fine because there will be no further
     changes to the lock bits nor the size, and we will subsequently release
     the lock with release MO.  */
  unsigned int s;
  s = (atomic_load_relaxed (&cond->__data.__g1_orig_size) & 3)
      | (size << 2);
  if ((atomic_exchange_relaxed (&cond->__data.__g1_orig_size, s) & 3)
      != (s & 3))
    atomic_store_relaxed (&cond->__data.__g1_orig_size, (size << 2) | 2);
}

/* Returns FUTEX_SHARED or FUTEX_PRIVATE based on the provided __wrefs
   value.  */
static int __attribute__ ((unused))
__condvar_get_private (int flags)
{
  if ((flags & __PTHREAD_COND_SHARED_MASK) == 0)
    return FUTEX_PRIVATE;
  else
    return FUTEX_SHARED;
}

/* This closes G1 (whose index is in G1INDEX), converts G1 into a fresh G2,
   and then switches group roles so that the former G2 becomes the new G1
   ending at the current __wseq value when we eventually make the switch
   (WSEQ is just an observation of __wseq by the signaler).
   If G2 is empty, it will not switch groups because then it would create an
   empty G1 which would require switching groups again on the next signal.
   Returns false iff groups were not switched because G2 was empty.  */
static bool __attribute__ ((unused))
__condvar_switch_g1 (pthread_cond_t *cond, uint64_t wseq,
    unsigned int *g1index, int private)
{
  unsigned int g1 = *g1index;

  /* If there is no waiter in G2, we don't do anything.  The expression may
     look odd but remember that __g_size might hold a negative value, so
     putting the expression this way avoids relying on implementation-defined
     behavior.
     Note that this works correctly for a zero-initialized condvar too.  */
  unsigned int old_orig_size = __condvar_get_orig_size (cond);
  uint64_t old_g1_start = __condvar_load_g1_start_relaxed (cond);
  uint64_t new_g1_start = old_g1_start + old_orig_size;
  if (((unsigned) (wseq - new_g1_start) + cond->__data.__g_size[g1 ^ 1]) == 0)
	return false;

  /* We have to consider the following kinds of waiters:
     * Waiters from less recent groups than G1 are not affected because
       nothing will change for them apart from __g1_start getting larger.
     * New waiters arriving concurrently with the group switching will all go
       into G2 until we atomically make the switch.  Waiters existing in G2
       are not affected.
     * Waiters in G1 have already received a signal and been woken.  */

  /* Update __g1_start, which closes this group.  Relaxed MO is fine because
     the change comes with no additional constraints that others would have
     to observe.  */
  __condvar_add_g1_start_relaxed (cond, old_orig_size);

  /* At this point, the old G1 is now a valid new G2 (but not in use yet).
     No old waiter can neither grab a signal nor acquire a reference without
     noticing that __g1_start is larger.
     We can now publish the group switch by flipping the G2 index in __wseq.
     Release MO so that this synchronizes with the acquire MO operation
     waiters use to obtain a position in the waiter sequence.  */
  wseq = __condvar_fetch_xor_wseq_release (cond, 1) >> 1;
  g1 ^= 1;
  *g1index ^= 1;

  /* Now advance the new G1 g_signals to the new g1_start, giving it
     an effective signal count of 0 to start.  */
  atomic_store_release (cond->__data.__g_signals + g1, (unsigned)new_g1_start);

  /* These values are just observed by signalers, and thus protected by the
     lock.  */
  unsigned int orig_size = wseq - new_g1_start;
  __condvar_set_orig_size (cond, orig_size);
  /* Use and addition to not loose track of cancellations in what was
     previously G2.  */
  cond->__data.__g_size[g1] += orig_size;

  /* The new G1's size may be zero because of cancellations during its time
     as G2.  If this happens, there are no waiters that have to receive a
     signal, so we do not need to add any and return false.  */
  if (cond->__data.__g_size[g1] == 0)
    return false;

  return true;
}
