#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "peripheral.lib";
require "peripheral.js";
require "peripheral_edit.lib";



&headPrepare();

my $t = "Create new peripheral";

&tablePeripheralSlice();
&editPeripheralNew();

&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => &peripheralModifyFuncs({ form => "createForm" }), header => $t, content => $PAGE, slices => $MENU });

exit(0);
