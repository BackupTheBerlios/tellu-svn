#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "device.lib";
require "device.js";
require "device_edit.lib";



&headPrepare();

my $t = "Create new device";

&tableDeviceSlice();
&editDeviceNew();

&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => &deviceModifyFuncs({ form => "createForm" }), header => $t, content => $PAGE, slices => $MENU });

exit(0);
