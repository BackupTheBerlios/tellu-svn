#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "console.lib";



&headPrepare();

&tableConsoleSlice();
&telConsole();

&htmlPage({ title => $WINDOW_TITLE . " - TEL console", script => "", header => "TEL console", content => $PAGE, slices => $MENU });

exit(0);
