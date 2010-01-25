#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "machine.lib";
require "machine.js";
require "machine_edit.lib";



&headPrepare();

my $t = "Create new machine";

&tableMachineDomainSlice();
&editMachineNew();

&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => &machineModifyFuncs({ form => "createForm" }), header => $t, content => $PAGE, slices => $MENU });

exit(0);
