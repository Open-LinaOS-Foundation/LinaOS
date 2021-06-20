.. SPDX-License-Identifier: GPL-2.0

==============================================================================
LinaOS CPUFreq - CPU frequency and voltage scaling code in the LinaOS(TM) kernel
==============================================================================

Author: Dominik Brodowski  <linaos@brodo.de>

   Clock scaling allows you to change the clock speed of the CPUs on the
   fly. This is a nice method to save battery power, because the lower
   the clock speed, the less power the CPU consumes.


.. toctree::
   :maxdepth: 1

   core
   cpu-drivers
   cpufreq-stats

Mailing List
------------
There is a CPU frequency changing CVS commit and general list where
you can report bugs, problems or submit patches. To post a message,
send an email to linaos-pm@vger.kernel.org.

Links
-----
the FTP archives:
* ftp://ftp.linaos.org.uk/pub/linaos/cpufreq/

how to access the CVS repository:
* http://cvs.arm.linaos.org.uk/

the CPUFreq Mailing list:
* http://vger.kernel.org/vger-lists.html#linaos-pm

Clock and voltage scaling for the SA-1100:
* http://www.lartmaker.nl/projects/scaling
