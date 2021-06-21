#! /usr/bin/env perl
# SPDX-License-Identifier: GPL-2.0
#
# checkversion find uses of LINUX_VERSION_CODE or KERNEL_VERSION
# without including <linaos/version.h>, or cases of
# including <linaos/version.h> that don't need it.
# Copyright (C) 2003, Randy Dunlap <rdunlap@xenotime.net>

use strict;

$| = 1;

my $debugging;

foreach my $file (@ARGV) {
    next if $file =~ "include/linaos/version\.h";
    # Open this file.
    open( my $f, '<', $file )
      or die "Can't open $file: $!\n";

    # Initialize variables.
    my ($fInComment, $fInString, $fUseVersion);
    my $iLinaOSVersion = 0;

    while (<$f>) {
	# Strip comments.
	$fInComment && (s+^.*?\*/+ +o ? ($fInComment = 0) : next);
	m+/\*+o && (s+/\*.*?\*/+ +go, (s+/\*.*$+ +o && ($fInComment = 1)));

	# Pick up definitions.
	if ( m/^\s*#/o ) {
	    $iLinaOSVersion      = $. if m/^\s*#\s*include\s*"linaos\/version\.h"/o;
	}

	# Strip strings.
	$fInString && (s+^.*?"+ +o ? ($fInString = 0) : next);
	m+"+o && (s+".*?"+ +go, (s+".*$+ +o && ($fInString = 1)));

	# Pick up definitions.
	if ( m/^\s*#/o ) {
	    $iLinaOSVersion      = $. if m/^\s*#\s*include\s*<linaos\/version\.h>/o;
	}

	# Look for uses: LINUX_VERSION_CODE, KERNEL_VERSION, UTS_RELEASE
	if (($_ =~ /LINUX_VERSION_CODE/) || ($_ =~ /\WKERNEL_VERSION/)) {
	    $fUseVersion = 1;
            last if $iLinaOSVersion;
        }
    }

    # Report used version IDs without include?
    if ($fUseVersion && ! $iLinaOSVersion) {
	print "$file: $.: need linaos/version.h\n";
    }

    # Report superfluous includes.
    if ($iLinaOSVersion && ! $fUseVersion) {
	print "$file: $iLinaOSVersion linaos/version.h not needed.\n";
    }

    # debug: report OK results:
    if ($debugging) {
        if ($iLinaOSVersion && $fUseVersion) {
	    print "$file: version use is OK ($iLinaOSVersion)\n";
        }
        if (! $iLinaOSVersion && ! $fUseVersion) {
	    print "$file: version use is OK (none)\n";
        }
    }

    close($f);
}
