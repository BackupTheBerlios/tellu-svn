#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "access.lib";



&headPrepare();

my @c = ();
my @r = &sendCommand({ command => "tryLogout", item => "", domain => "", param => "", option => "" });

$c[0] = &headCookieSet({ name => "tellu_cid", value => "" });
$c[1] = &headCookieSet({ name => "tellu_uid", value => "" });

$PAGE .= "<p>If page is not redirected automatically, please click <a href=\"login.pl\">here</a>.</p>";

&htmlPage({ redirect => "login.pl", title => $WINDOW_TITLE, script => "", header => "", content => $PAGE, slices => $MENU, cookie => \@c });

exit(0);
