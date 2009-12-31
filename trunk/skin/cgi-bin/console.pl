#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "console.lib";



&headPrepare();

&tableConsoleSlice();
&telConsole();

&htmlPage({ title => $WINDOW_TITLE . " - Tellu expression console", script => "", header => "Tellu expression console", content => $PAGE, slices => $MENU });

exit(0);
