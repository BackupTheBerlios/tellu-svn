#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "search.lib";



&headPrepare();

&tableSearchSlice();

&htmlPage({ title => $WINDOW_TITLE . " - Search", script => "", header => "Search", content => $PAGE, slices => $MENU });

exit(0);
