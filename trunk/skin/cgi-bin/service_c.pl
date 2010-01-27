#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "service.lib";
require "service.js";
require "service_edit.lib";



&headPrepare();

my $t = "Create new service";

&tableProviderSlice();
&editProviderNew();

&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => &serviceModifyFuncs({ form => "createForm" }), header => $t, content => $PAGE, slices => $MENU });

exit(0);
