#
# gdb helper commands and functions for LinaOS kernel debugging
#
#  loader module
#
# Copyright (c) Siemens AG, 2012, 2013
#
# Authors:
#  Jan Kiszka <jan.kiszka@siemens.com>
#
# This work is licensed under the terms of the GNU GPL version 2.
#

import os

sys.path.insert(0, os.path.dirname(__file__) + "/scripts/gdb")

try:
    gdb.parse_and_eval("0")
    gdb.execute("", to_string=True)
except:
    gdb.write("NOTE: gdb 7.2 or later required for LinaOS helper scripts to "
              "work.\n")
else:
    import linaos.utils
    import linaos.symbols
    import linaos.modules
    import linaos.dmesg
    import linaos.tasks
    import linaos.config
    import linaos.cpus
    import linaos.lists
    import linaos.rbtree
    import linaos.proc
    import linaos.constants
    import linaos.timerlist
    import linaos.clk
    import linaos.genpd
    import linaos.device
