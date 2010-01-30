#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "admin.lib";
require "admin.js";



&headPrepare();

&tableAdminSlice();

$PAGE .= &htmlFormBegin({ name => "modifyForm", action => $SELF . "?action=admin&verb=update", enctype => "application/x-www-form-urlencoded", method => "post" });

$PAGE .= "<p>&nbsp;</p>";
$PAGE .= "<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\">";
$PAGE .= "<tr class=\"middle\">";

my $t = "";
my $s = 0;

my @l = ('Users', 'Ports', 'Classes', 'Sessions', 'Database status', 'Server status');

foreach my $l (@l) {
	if($s == $q->param('leaf')) {
		$PAGE .= "<td align=\"right\" valign=\"bottom\"><img alt=\"\" src=\"/pics/leaf_left_s.png\"></td><td class=\"leaf_s\"><a href=\"" . $SELF . "?action=admin&leaf=" . $s . "\">" . $l . "</a></td><td align=\"left\" valign=\"bottom\"><img alt=\"\" src=\"/pics/leaf_right_s.png\"></td>";
	}
	else {
		$PAGE .= "<td align=\"right\" valign=\"bottom\"><img alt=\"\" src=\"/pics/leaf_left.png\"></td><td class=\"leaf\"><a href=\"" . $SELF . "?action=admin&leaf=" . $s . "\">" . $l . "</a></td><td align=\"left\" valign=\"bottom\"><img alt=\"\" src=\"/pics/leaf_right.png\"></td>";
	}

	$s++;
}

$PAGE .= "</tr>";
$PAGE .= "</table>";

if(!$q->param('leaf') || $q->param('leaf') == 0) {
	$t = "Manage users";

	&editAdminUser({ leaf => $q->param('leaf') });

	&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => "", header => $t, content => $PAGE, slices => $MENU });
}
elsif($q->param('leaf') == 1) {
	$t = "Manage port descriptions";

	&editAdminPort({ leaf => $q->param('leaf') });

	&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => "", header => $t, content => $PAGE, slices => $MENU });
}
elsif($q->param('leaf') == 2) {
	$t = "Manage service classes";

	&editAdminService({ leaf => $q->param('leaf') });

	&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => "", header => $t, content => $PAGE, slices => $MENU });
}
elsif($q->param('leaf') == 3) {
	$t = "Manage sessions";

	my $l = 0;

	if($q->param('leaf')) {
		$l = $q->param('leaf');
	}

	&editAdminSession({ leaf => $l, action => $q->param('action'), verb => $q->param('verb'), sort => $q->param('sort'), order => $q->param('order'), select => $q->param('select') });

	&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => "", header => $t, content => $PAGE, slices => $MENU });
}
elsif($q->param('leaf') == 4) {
	$t = "View database status";

	my @t = ();

	$t[0] = $q->optgroup( -name => "View database status", -values => [ "Status", "Variables" ], -class => "header" );
	$t[1] = $q->optgroup( -name => "View database messages", -values => [ "Errors", "Warnings" ], -class => "header" );

	$PAGE .= "<table class=\"default\" width=\"100%\" cellpadding=\"3\" cellspacing=\"1\">";

	$PAGE .= "<tr class=\"top\">";
	$PAGE .= "<td></td><td></td>";
	$PAGE .= "</tr>";

	$PAGE .= "<tr class=\"middle\">";
	$PAGE .= "<td align=\"right\" width=\"20%\">Action:</td>";
	$PAGE .= "<td width=\"80%\">" . &htmlSelectMenu({ name => "select", value => \@t, select => $q->param('select') });
	$PAGE .= "&nbsp;";
	$PAGE .= &htmlButtonSubmit({ name => "submit", value => "View >>" }) . "</td>";
	$PAGE .= "</tr>";

	$PAGE .= "<tr class=\"top\">";
	$PAGE .= "<td></td><td></td>";
	$PAGE .= "</tr>";
	$PAGE .= "</table>";
	$PAGE .= "<p>&nbsp;</p>";

	my $l = 0;

	if($q->param('leaf')) {
		$l = $q->param('leaf');
	}

	if($q->param('verb') eq "update") {
		&editAdminDbstat({ leaf => $l, action => $q->param('action'), verb => $q->param('verb'), sort => $q->param('sort'), order => $q->param('order'), select => $q->param('select') });
	}

	$PAGE .= &htmlHiddenField({ name => "action", value => "admin" });
	$PAGE .= &htmlHiddenField({ name => "verb", value => "update" });
	$PAGE .= &htmlHiddenField({ name => "leaf", value => $l });
	$PAGE .= &htmlHiddenField({ name => "subleaf", value => $f });

	$PAGE .= &htmlFormEnd();

	&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => "", header => $t, content => $PAGE, slices => $MENU });
}
elsif($q->param('leaf') == 5) {
	$t = "View server status";

	my @t = ();

	$t[0] = $q->optgroup( -name => "View usage of storage", -values => [ "Uploads" ], -class => "header" );
	$t[1] = $q->optgroup( -name => "View server status", -values => [ "Log", "History" ], -class => "header" );

	$PAGE .= "<table class=\"default\" width=\"100%\" cellpadding=\"3\" cellspacing=\"1\">";

	$PAGE .= "<tr class=\"top\">";
	$PAGE .= "<td></td><td></td>";
	$PAGE .= "</tr>";

	$PAGE .= "<tr class=\"middle\">";
	$PAGE .= "<td align=\"right\" width=\"20%\">Action:</td>";
	$PAGE .= "<td width=\"80%\">" . &htmlSelectMenu({ name => "select", value => \@t, select => $q->param('select') });
	$PAGE .= "&nbsp;";
	$PAGE .= &htmlButtonSubmit({ name => "submit", value => "View >>" }) . "</td>";
	$PAGE .= "</tr>";

	$PAGE .= "<tr class=\"top\">";
	$PAGE .= "<td></td><td></td>";
	$PAGE .= "</tr>";
	$PAGE .= "</table>";
	$PAGE .= "<p>&nbsp;</p>";

	my $l = 0;
	my $f = 0;

	if($q->param('leaf')) {
		$l = $q->param('leaf');
	}

	if($q->param('subleaf')) {
		$f = $q->param('subleaf');
	}

	if($q->param('verb') eq "update") {
		&editAdminSkinstat({ leaf => $l, subleaf => $f, action => $q->param('action'), verb => $q->param('verb'), sort => $q->param('sort'), order => $q->param('order'), select => $q->param('select') });
	}

	$PAGE .= &htmlHiddenField({ name => "action", value => "admin" });
	$PAGE .= &htmlHiddenField({ name => "verb", value => "update" });
	$PAGE .= &htmlHiddenField({ name => "leaf", value => $l });
	$PAGE .= &htmlHiddenField({ name => "subleaf", value => $f });

	$PAGE .= &htmlFormEnd();

	&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => "", header => $t, content => $PAGE, slices => $MENU });
}
else {
	&htmlPage({ title => $WINDOW_TITLE, script => "", header => "&nbsp;", content => $PAGE, slices => $MENU });
}

exit(0);
