#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "admin.lib";
require "admin.js";



&headPrepare();
&tableAdminSlice();

my $t = "";
my $s = 0;
my $x = 0;

my @r = &sendCommand({ command => "isUserAdmin", item => "", domain => "", param => "", option => "" });
my @l = ();

if(checkError({ packet => \@r }) == 0) {
	if($r[3] && $r[3] == 64) {
		@l = ('My account', 'Users', 'Classes', 'Sessions', 'Database status', 'Server status');

		$x = 1;
	}
}
else {
	&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
}

if(!@l) {
	@l = ('My account');
}

$PAGE .= &htmlFormBegin({ name => "modifyForm", action => $SELF . "?action=admin&verb=update", enctype => "application/x-www-form-urlencoded", method => "post" });

$PAGE .= "<p>&nbsp;</p>";
$PAGE .= "<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\">";
$PAGE .= "<tr class=\"middle\">";

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

if($x == 0) {
	if(!$q->param('leaf') || $q->param('leaf') == 0) {
		$t = "My account";

		my @t = ();

		$t[0] = $q->optgroup( -name => "My account", -values => [ "Change password", "Set front page", "Set popup windows" ], -class => "header" );

		$PAGE .= "<table class=\"default\" width=\"100%\" cellpadding=\"3\" cellspacing=\"1\">";

		$PAGE .= "<tr class=\"top\">";
		$PAGE .= "<td></td><td></td>";
		$PAGE .= "</tr>";

		$PAGE .= "<tr class=\"middle\">";
		$PAGE .= "<td align=\"right\" width=\"20%\">Action:</td>";
		$PAGE .= "<td width=\"80%\">" . &htmlSelectMenu({ name => "select", value => \@t, select => $q->param('select') });
		$PAGE .= "&nbsp;";
		$PAGE .= &htmlButtonSubmit({ name => "submit", value => "Switch >>" }) . "</td>";
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
			&editAdminAccount({ leaf => $l, action => $q->param('action'), verb => $q->param('verb'), select => $q->param('select') });
		}

		$PAGE .= &htmlHiddenField({ name => "action", value => "admin" });
		$PAGE .= &htmlHiddenField({ name => "verb", value => "update" });
		$PAGE .= &htmlHiddenField({ name => "leaf", value => $l });

		$PAGE .= &htmlFormEnd();

		&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => "", header => $t, content => $PAGE, slices => $MENU });
	}
	else {
		&htmlPage({ title => $WINDOW_TITLE, script => "", header => "&nbsp;", content => $PAGE, slices => $MENU });
	}
}
else {
	if(!$q->param('leaf') || $q->param('leaf') == 0) {
		$t = "My account";

		my @t = ();

		$t[0] = $q->optgroup( -name => "My account", -values => [ "Change password", "Set front page", "Set popup windows" ], -class => "header" );

		$PAGE .= "<table class=\"default\" width=\"100%\" cellpadding=\"3\" cellspacing=\"1\">";

		$PAGE .= "<tr class=\"top\">";
		$PAGE .= "<td></td><td></td>";
		$PAGE .= "</tr>";

		$PAGE .= "<tr class=\"middle\">";
		$PAGE .= "<td align=\"right\" width=\"20%\">Action:</td>";
		$PAGE .= "<td width=\"80%\">" . &htmlSelectMenu({ name => "select", value => \@t, select => $q->param('select') });
		$PAGE .= "&nbsp;";
		$PAGE .= &htmlButtonSubmit({ name => "submit", value => "Switch >>" }) . "</td>";
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
			&editAdminAccount({ leaf => $l, action => $q->param('action'), verb => $q->param('verb'), select => $q->param('select') });
		}

		$PAGE .= &htmlHiddenField({ name => "action", value => "admin" });
		$PAGE .= &htmlHiddenField({ name => "verb", value => "update" });
		$PAGE .= &htmlHiddenField({ name => "leaf", value => $l });

		$PAGE .= &htmlFormEnd();

		&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => "", header => $t, content => $PAGE, slices => $MENU });
	}
	elsif($q->param('leaf') == 1) {
		$t = "Manage users";

		my @o = ();
		my @t = ();
		my %l = ();

		my @r = &sendCommand({ command => "listUser", item => "", domain => "", param => "", option => "" });

		if(checkError({ packet => \@r }) == 0) {
			if($r[3] && $r[3] ne "") {
				foreach my $e (split(/$ITEM_DELIMITER/, $r[3])) {
					my ($f, $g, $h) = split(/$ITEM_SEPARATOR/, $e);

					$h = cleanNull({ string => $h });

					push @o, $g;

					if($h && $h ne "") {
						$l{$g} = $g . " (" . $h . ")";
					}
					else {
						$l{$g} = $g;
					}
				}
			}
		}

		$t[0] = $q->optgroup( -name => "Manage users", -values => "Create new user", -class => "header" );
		$t[1] = $q->optgroup( -name => "Modify existing users", -values => \@o, -labels => \%l, -class => "header" );

		$PAGE .= "<table class=\"default\" width=\"100%\" cellpadding=\"3\" cellspacing=\"1\">";

		$PAGE .= "<tr class=\"top\">";
		$PAGE .= "<td></td><td></td>";
		$PAGE .= "</tr>";

		$PAGE .= "<tr class=\"middle\">";
		$PAGE .= "<td align=\"right\" width=\"20%\">Action:</td>";
		$PAGE .= "<td width=\"80%\">" . &htmlSelectMenu({ name => "select", value => \@t, select => $q->param('select') });
		$PAGE .= "&nbsp;";
		$PAGE .= &htmlButtonSubmit({ name => "submit", value => "Switch >>" }) . "</td>";
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
			&editAdminUser({ leaf => $l, action => $q->param('action'), verb => $q->param('verb'), select => $q->param('select') });
		}

		$PAGE .= &htmlHiddenField({ name => "action", value => "admin" });
		$PAGE .= &htmlHiddenField({ name => "verb", value => "update" });
		$PAGE .= &htmlHiddenField({ name => "leaf", value => $l });

		$PAGE .= &htmlFormEnd();

		&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => &adminModifyFuncs({ form => "modifyForm" }), header => $t, content => $PAGE, slices => $MENU });
	}
	elsif($q->param('leaf') == 2) {
		$t = "Manage service classes";

		my @o = ();
		my @t = ();
		my %l = ();

		my @r = &sendCommand({ command => "listService", item => "", domain => "", param => "name", option => "" });

		if(checkError({ packet => \@r }) == 0) {
			if($r[3] && $r[3] ne "") {
				foreach my $e (split(/$ITEM_DELIMITER/, $r[3])) {
					my ($f, $g) = split(/$ITEM_SEPARATOR/, $e);

					push @o, $f;
					$l{$f} = $g;
				}
			}
		}

		$t[0] = $q->optgroup( -name => "Manage service classes", -values => "Create new service class", -class => "header" );
		$t[1] = $q->optgroup( -name => "Modify existing service class", -values => \@o, -labels => \%l, -class => "header" );

		$PAGE .= "<table class=\"default\" width=\"100%\" cellpadding=\"3\" cellspacing=\"1\">";

		$PAGE .= "<tr class=\"top\">";
		$PAGE .= "<td></td><td></td>";
		$PAGE .= "</tr>";

		$PAGE .= "<tr class=\"middle\">";
		$PAGE .= "<td align=\"right\" width=\"20%\">Action:</td>";
		$PAGE .= "<td width=\"80%\">" . &htmlSelectMenu({ name => "select", value => \@t, select => $q->param('select') });
		$PAGE .= "&nbsp;";
		$PAGE .= &htmlButtonSubmit({ name => "submit", value => "Switch >>" }) . "</td>";
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
			&editAdminService({ leaf => $l, action => $q->param('action'), verb => $q->param('verb'), select => $q->param('select') });
		}

		$PAGE .= &htmlHiddenField({ name => "action", value => "admin" });
		$PAGE .= &htmlHiddenField({ name => "verb", value => "update" });
		$PAGE .= &htmlHiddenField({ name => "leaf", value => $l });

		$PAGE .= &htmlFormEnd();

		&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => &adminModifyFuncs({ form => "modifyForm" }), header => $t, content => $PAGE, slices => $MENU });
	}
	elsif($q->param('leaf') == 3) {
		$t = "View active sessions";

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

		$t[0] = $q->optgroup( -name => "View database status", -values => [ "Global status", "Table status", "Variables" ], -class => "header" );
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
}

exit(0);
