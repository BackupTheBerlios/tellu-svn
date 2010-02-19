#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";



&headPrepare();

my $h = "Standard";

if($q->param('theme') && $q->param('theme') ne "") {
	$h = $q->param('theme');
}

my $t = $h;

$t =~ s/_/ /go;
$t .= " theme";

$PAGE .= "<p>Well, what do you think? This is how " . lc($t) . " looks like. If you like to use this theme, press <i>Set theme</i> button in main window.</p>";

&htmlPage({ template => "popup", theme => $h, title => $WINDOW_TITLE . " - " . $t, script => "", header => $t, content => $PAGE, slices => $MENU });

exit(0);
