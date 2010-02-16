#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "personal.lib";
require "personal.js";



&headPrepare();

if($q->param('action') || $q->param('slice')) {
	my $t = "";

	&tablePersonalSlice();

	if($q->param('action') eq "editg") {
		$t = "Edit my factions";

		&editPersonalFaction();

		&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => &modifyFuncs({ form => "modifyForm" }), header => $t, content => $PAGE, slices => $MENU });
	}
	elsif($q->param('action') eq "editf") {
		$t = "Edit my files";

		&editPersonalFile();

		&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => &modifyFuncs({ form => "modifyForm" }), header => $t, content => $PAGE, slices => $MENU });
	}
	elsif($q->param('action') eq "editp") {
		$t = "Edit my passwords";

		&editPersonalPwds();

		&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => &modifyFuncs({ form => "modifyForm" }), header => $t, content => $PAGE, slices => $MENU });
	}
	elsif($q->param('action') eq "listg" || $q->param('slice') eq "grp") {
		require "machine.lib";
		require "faction.js";

		$t = "My factions";

		my @r = &sendCommand({ command => "listFaction", item => "", domain => "", param => "name", option => "" });

		if(checkError({ packet => \@r }) == 0) {
			my @s = split(/$ITEM_DELIMITER/, $r[3]);

			foreach my $s (@s) {
				my @i = split(/$ITEM_SEPARATOR/, $s);

				$i[2] = $i[0] . "|" . $i[2];

				push @w, join($ITEM_SEPARATOR, @i);
			}

			$PAGE .= "<p>&nbsp;</p>";
			$SCRIPT .= &factionListingFuncs();

			&tableMachineDetail({ data => join($ITEM_DELIMITER, @w), slice => "grp", sort => $q->param('sort'), order => $q->param('order') });
		}

		&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => $SCRIPT . &modifyFuncs({ form => "modifyForm" }), header => $t, content => $PAGE, slices => $MENU });
	}
	elsif($q->param('action') eq "listf" || $q->param('slice') eq "fle") {
		require "machine.lib";

		$t = "My files";

		my @r = &sendCommand({ command => "listFile", item => "", domain => "", param => "name", option => "" });

		if(checkError({ packet => \@r }) == 0) {
			$PAGE .= "<p>&nbsp;</p>";

			&tableMachineDetail({ data => $r[3], slice => "fle", sort => $q->param('sort'), order => $q->param('order') });
		}

		&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => &modifyFuncs({ form => "modifyForm" }), header => $t, content => $PAGE, slices => $MENU });
	}
	elsif($q->param('action') eq "listp" || $q->param('slice') eq "pwd") {
		require "machine.lib";

		$t = "My passwords";

		my $k = "";

		if($q->param('key')) {
			$k = $q->param('key');
		}

		my @r = &sendCommand({ command => "listPassword", item => "", domain => "", param => "name", option => "" });

		if(checkError({ packet => \@r }) == 0) {
			$PAGE .= "<p>&nbsp;</p>";

			&tableMachineDetail({ data => $r[3], slice => "pwd", key => $k, sort => $q->param('sort'), order => $q->param('order') });
		}

		&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => &passwordFuncs({ slice => "pwd" }), header => $t, content => $PAGE, slices => $MENU });
	}
	else {
		&htmlPage({ title => $WINDOW_TITLE, script => "", header => "&nbsp;", content => $PAGE, slices => $MENU });
	}
}
else {
	&htmlPage({ title => $WINDOW_TITLE, script => "", header => "&nbsp;", content => $PAGE, slices => $MENU });
}

exit(0);
