#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "machine.lib";
require "machine.js";



&headPrepare();

my @r = ();

my $d = &headCookieGet({ name => "tellu_machine_domain" });
my $n = &headCookieGet({ name => "tellu_machine_node" });

if($q->param('host') && $q->param('host') ne "") {
	@r = split(/\|/, $q->param('host'), 2);

	$n = $r[0];
	$d = $r[1];
}

my $t = "";
my $u = "";

if($q->param('action') && $q->param('action') ne "") {
	if($q->param('note') && $q->param('note') ne "") {
		if($q->param('verb') && $q->param('verb') eq "go") {
			if($q->param('action') && $q->param('action') eq "modify") {
				@r = &sendCommand({ command => "noteModifyMachine", item => $q->param('note'), domain => "", param => $q->param('new_note'), option => "" });
			}
			elsif($q->param('action') && $q->param('action') eq "delete") {
				@r = &sendCommand({ command => "noteDeleteMachine", item => $q->param('note'), domain => "", param => "", option => "" });
			}

			&htmlPage({ template => "popup", title => $WINDOW_TITLE . " - " . $n . "." . $d, script => &machineNoteFuncs(), header => "", subheader => "", content => $PAGE, slices => $MENU });

			exit(0);
		}

		@r = &sendCommand({ command => "notePullMachineByID", item => $n, domain => $d, param => $q->param('note'), option => "" });

		if(checkError({ packet => \@r }) == 0) {
			my @s = split(/$ITEM_SEPARATOR/, $r[3]);

			$u .= "Note added by " . $s[2] . " at " . &itemClean({ item => $s[1], flag => 31 });

			if($s[4] && $s[4] ne "") {
				$u .= ", modified by " . $s[4] . " at " . &itemClean({ item => $s[3], flag => 31 });
			}

			$PAGE .= &htmlFormBegin({ name => "modifyForm", action => $SELF, enctype => "application/x-www-form-urlencoded", method => "post" });

			if($q->param('action') && $q->param('action') eq "modify") {
				$t .= " - modify note";

				$PAGE .= "<p>" . &htmlInputField({ name => "new_note", value => cleanNull({ string => $s[5], fixfeed => 1 }) }) . "</p>";
				$PAGE .= "<p>" . &htmlButtonSubmit({ name => "submit", value => "Modify" });
				$PAGE .= "&nbsp;";
				$PAGE .= &htmlButtonAction({ name => "cancel", style => "button", value => "Cancel", function => "window.close();" }) . "</p>";
			}
			elsif($q->param('action') && $q->param('action') eq "delete") {
				$t .= " - delete note";

				$PAGE .= "<p>" . &htmlInputField({ name => "old_note", value => cleanNull({ string => $s[5], fixfeed => 1 }), readonly => 1 }) . "</p>";
				$PAGE .= "<p>" . &htmlButtonSubmit({ name => "submit", value => "Delete" });
				$PAGE .= "&nbsp;";
				$PAGE .= &htmlButtonAction({ name => "cancel", style => "button", value => "Cancel", function => "window.close();" }) . "</p>";
			}

			$PAGE .= &htmlHiddenField({ name => "action", value => $q->param('action') });
			$PAGE .= &htmlHiddenField({ name => "note", value => $q->param('note') });
			$PAGE .= &htmlHiddenField({ name => "verb", value => "go" });

			$PAGE .= &htmlFormEnd();
		}
	}
}

&htmlPage({ template => "popup", title => $WINDOW_TITLE . " - " . $n . "." . $d, script => "", header => $n . "." . $d . $t, subheader => $u, content => $PAGE, slices => $MENU });

exit(0);
