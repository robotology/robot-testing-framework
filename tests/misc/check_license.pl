#!/usr/bin/perl -w

# Robot Testing Framework
#
# Copyright (C) 2015-2019 Istituto Italiano di Tecnologia (IIT)
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

my @files = `git ls-files`;
s{^\s+|\s+$}{}g foreach @files;

open my $handle, '<', "tests/misc/check_license_skip.txt";
chomp(my @skip_files = <$handle>);
close $handle;


my $copyright_iit = "Copyright \\(C\\) 2015-2019 Istituto Italiano di Tecnologia \\(IIT\\)";


my $str_lgpl2_1_or_later = <<END;
^/\\*
 \\* Robot Testing Framework
 \\*
 \\* $copyright_iit
 \\*
 \\* This library is free software; you can redistribute it and/or
 \\* modify it under the terms of the GNU Lesser General Public
 \\* License as published by the Free Software Foundation; either
 \\* version 2\\.1 of the License, or \\(at your option\\) any later version\\.
 \\*
 \\* This library is distributed in the hope that it will be useful,
 \\* but WITHOUT ANY WARRANTY; without even the implied warranty of
 \\* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE\\.  See the GNU
 \\* Lesser General Public License for more details\\.
 \\*
 \\* You should have received a copy of the GNU Lesser General Public
 \\* License along with this library; if not, write to the Free Software
 \\* Foundation, Inc\\., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 \\*/

END

my $str_lgpl2_1_or_later_script_no_sb = <<END;
^(#\\.rst:(
#[^\n]*)+

)?# Robot Testing Framework
#
# $copyright_iit
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2\\.1 of the License, or \\(at your option\\) any later version\\.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE\\.  See the GNU
# Lesser General Public License for more details\\.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc\\., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

END


my $str_lgpl2_1_or_later_script = <<END;
^#!.+

# Robot Testing Framework
#
# $copyright_iit
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2\\.1 of the License, or \\(at your option\\) any later version\\.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE\\.  See the GNU
# Lesser General Public License for more details\\.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc\\., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

END


my $str_lgpl2_1_or_later_lua = <<END;
^-- Robot Testing Framework
--
-- $copyright_iit
--
-- This library is free software; you can redistribute it and/or
-- modify it under the terms of the GNU Lesser General Public
-- License as published by the Free Software Foundation; either
-- version 2\\.1 of the License, or \\(at your option\\) any later version\\.
--
-- This library is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE\\.  See the GNU
-- Lesser General Public License for more details\\.
--
-- You should have received a copy of the GNU Lesser General Public
-- License along with this library; if not, write to the Free Software
-- Foundation, Inc\\., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

END

my $files = 0;
my $ok = 0;
my $skip = 0;
my $errors = 0;
my $known = 0;

foreach my $filename (@files) {
    $files++;

    # For now skip files known to have a broken license
    my $match = 0;
    for (@skip_files) {
        if ("$filename" eq "$_") {
            $match = 1;
            last;
        }
    }

    if( $match ) {
        print "[SKIP] $filename\n";
        $known++;
        next;
    }


    # Read the file
    my $txt = "";
    open(FIN,"<$filename");
    while (<FIN>) {
        $txt .= $_;
    }
    close(FIN);


    # Check if the file contains the unicode BOM
    if ("$txt" =~ /^\xEF\xBB\xBF/s) {
        print "[NOT OK (Contains BOM)] $filename\n";
        $errors++;
        next;
    }


    # C++ style LGPL2.1+
    if ("$txt" =~ /$str_lgpl2_1_or_later/s) {
        if ("$filename" =~ /\.(cpp|h|h.in|dox)$/) {
            print "[OK - LGPL2.1+ ($1)] $filename\n";
            $ok++;
        } else {
            print "[NOT OK - LGPL2.1+] $filename\n";
            $errors++;
        }
        next;
    }

    # Script style LGPL2.1+ (no shebang)
    if ("$txt" =~ /$str_lgpl2_1_or_later_script_no_sb/s) {
        if ("$filename" =~ /\.(cmake|cmake\.in|cmake\.template|ps1)$/) {
            print "[OK - LGPL2.1+ ($1)] $filename\n";
            $ok++;
        } elsif ("$filename" =~ /CMakeLists.txt$/) {
            print "[OK - LGPL2.1+ (CMakeLists.txt)] $filename\n";
            $ok++;
        } else {
            print "[NOT OK - LGPL2.1+ (script)] $filename\n";
            $errors++;
        }
        next;
    }

    # Script style LGPL2.1+ (with shebang)
    if ("$txt" =~ /$str_lgpl2_1_or_later_script/s) {

        # Ensure that scripts are executable on linux
        if ($^O eq "linux") {
            stat($filename);
            if (! -x _) {
                print "[NOT OK - LGPL2.1+ (script not executable)] $filename\n";
                $errors++;
                next;
            }
        }

        if ("$filename" =~ /\.(sh|py|pl|tcl)$/) {
            print "[OK - LGPL2.1+ (.$1)] $filename\n";
            $ok++;
        } else {
            print "[OK - LGPL2.1+ (script)] $filename\n";
            $ok++;
        }
        next;
    }

    # Lua style LGPL2.1+
    if ("$txt" =~ /$str_lgpl2_1_or_later_lua/s) {
        if ("$filename" =~ /\.(lua|adb|ads|gpr)$/) {
            print "[OK - LGPL2.1+ ($1)] $filename\n";
            $ok++;
        } else {
            print "[NOT OK - LGPL2.1+] $filename\n";
            $errors++;
        }
        next;
    }

    print "[NOT OK (unknown license)] $filename\n";
    $errors++;
    next;
}

print "FILES:  $files\n";
print "OK:     $ok\n";
print "SKIP:   $skip\n";
print "KNOWN:  $known\n";
print "ERRORS: $errors\n";

if ($ok + $skip + $known + $errors != $files) {
    print "\n[ERROR: Some file was not counted]\n";
    exit 1;
}

if ($known < scalar(@skip_files)) {
    print "\n[ERROR: Some known file was not found and the skip file was not updated]\n";
    exit 1;
}

if ($known > scalar(@skip_files)) {
    print "\n[ERROR: Some new known file was added and the skip file was not updated]\n";
    exit 1;
}

if ($errors != 0) {
    print "\n[ERROR: Some file has an invalid license]\n";
    exit 1;
}

exit 0;
