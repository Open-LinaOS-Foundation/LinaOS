Driver Basics
=============

Driver Entry and Exit points
----------------------------

.. kernel-doc:: include/linaos/module.h
   :internal:

Driver device table
-------------------

.. kernel-doc:: include/linaos/mod_devicetable.h
   :internal:
   :no-identifiers: pci_device_id


Delaying, scheduling, and timer routines
----------------------------------------

.. kernel-doc:: include/linaos/sched.h
   :internal:

.. kernel-doc:: kernel/sched/core.c
   :export:

.. kernel-doc:: kernel/sched/cpupri.c
   :internal:

.. kernel-doc:: kernel/sched/fair.c
   :internal:

.. kernel-doc:: include/linaos/completion.h
   :internal:

.. kernel-doc:: kernel/time/timer.c
   :export:

Wait queues and Wake events
---------------------------

.. kernel-doc:: include/linaos/wait.h
   :internal:

.. kernel-doc:: kernel/sched/wait.c
   :export:

High-resolution timers
----------------------

.. kernel-doc:: include/linaos/ktime.h
   :internal:

.. kernel-doc:: include/linaos/hrtimer.h
   :internal:

.. kernel-doc:: kernel/time/hrtimer.c
   :export:

Internal Functions
------------------

.. kernel-doc:: kernel/exit.c
   :internal:

.. kernel-doc:: kernel/signal.c
   :internal:

.. kernel-doc:: include/linaos/kthread.h
   :internal:

.. kernel-doc:: kernel/kthread.c
   :export:

Reference counting
------------------

.. kernel-doc:: include/linaos/refcount.h
   :internal:

.. kernel-doc:: lib/refcount.c
   :export:

Atomics
-------

.. kernel-doc:: arch/x86/include/asm/atomic.h
   :internal:

Kernel objects manipulation
---------------------------

.. kernel-doc:: lib/kobject.c
   :export:

Kernel utility functions
------------------------

.. kernel-doc:: include/linaos/kernel.h
   :internal:
   :no-identifiers: kstrtol kstrtoul

.. kernel-doc:: kernel/printk/printk.c
   :export:
   :no-identifiers: printk

.. kernel-doc:: kernel/panic.c
   :export:

.. kernel-doc:: include/linaos/overflow.h
   :internal:

Device Resource Management
--------------------------

.. kernel-doc:: drivers/base/devres.c
   :export:

