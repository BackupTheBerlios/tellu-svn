#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "machine.lib";
require "personal.js";



&headPrepare();

my @c = ();
my @r = ();

my $d = &headCookieGet({ name => "tellu_machine_d_popup_domain" });
my $n = &headCookieGet({ name => "tellu_machine_d_popup_node" });

if($q->param('host') && $q->param('host') ne "") {
	@r = split(/\|/, $q->param('host'), 2);

	$n = $r[0];
	$d = $r[1];
}

my $t = "";
my $u = "";

if($q->param('slice') eq "addinfo" || $q->param('slice') eq "repair" || $q->param('slice') eq "security" || $q->param('slice') eq "warranty") {
	@r = &sendCommand({ command => "pullDisposedMachine", item => $n, domain => $d, param => "node", option => "" });

	if(checkError({ packet => \@r }) == 0) {
		&tableMachineDetail({ data => $r[3], slice => $q->param('slice'), sort => $q->param('sort'), order => $q->param('order') });
	}
}
elsif($q->param('slice') eq "files") {
	my @w = ();

	@r = &sendCommand({ command => "pullDisposedMachine", item => $n, domain => $d, param => "node", option => "" });

	if(checkError({ packet => \@r }) == 0) {
		my @s = split(/$ITEM_SEPARATOR/, $r[3]);

		@r = &sendCommand({ command => "attachedFile", item => "", domain => "", param => $s[0], option => "" });

		if(checkError({ packet => \@r }) == 0) {
			@s = split(/$ITEM_DELIMITER/, $r[3]);

			foreach my $s (@s) {
				@r = &sendCommand({ command => "pullFile", item => $s, domain => "", param => "id", option => "" });

				if(checkError({ packet => \@r }) == 0) {
					if($r[3] && $r[3] ne "") {

						push @w, $r[3];
					}
				}
			}

			&tableMachineDetail({ data => join($ITEM_DELIMITER, @w), slice => $q->param('slice'), sort => $q->param('sort'), order => $q->param('order') });
		}
	}
}
elsif($q->param('slice') eq "passwds") {
	my @w = ();
	my $k = "";

	if($q->param('key')) {
		$k = $q->param('key');
	}

	@r = &sendCommand({ command => "pullDisposedMachine", item => $n, domain => $d, param => "node", option => "" });

	if(checkError({ packet => \@r }) == 0) {
		my @s = split(/$ITEM_SEPARATOR/, $r[3]);

		@r = &sendCommand({ command => "attachedPassword", item => "", domain => "", param => $s[0], option => "" });

		if(checkError({ packet => \@r }) == 0) {
			@s = split(/$ITEM_DELIMITER/, $r[3]);

			foreach my $s (@s) {
				@r = &sendCommand({ command => "pullPassword", item => $s, domain => "", param => "id", option => "" });

				if(checkError({ packet => \@r }) == 0) {
					if($r[3] && $r[3] ne "") {

						push @w, $r[3];
					}
				}
			}

			&tableMachineDetail({ data => join($ITEM_DELIMITER, @w), slice => $q->param('slice'), key => $k, sort => $q->param('sort'), order => $q->param('order') });
		}
	}
}
else {
	@r = &sendCommand({ command => "pullDisposedMachine", item => $n, domain => $d, param => $q->param('slice'), option => "" });

	if(checkError({ packet => \@r }) == 0) {
		&tableMachineDetail({ data => $r[3], slice => $q->param('slice'), sort => $q->param('sort'), order => $q->param('order') });
	}
}

@r = &sendCommand({ command => "pullDisposedMachine", item => $n, domain => $d, param => "node", option => "" });

if(checkError({ packet => \@r }) == 0) {
	my @s = split(/$ITEM_SEPARATOR/, $r[3]);

	&tableMachineListingSlice({ system => $s[1], distro => $s[3] });

	if($s[1]) {
		$t .= "&nbsp;-&nbsp;" . $s[1];
	}

	if($s[2]) {
		$t .= ",&nbsp;" . $s[2];
	}

	if($s[18] && $s[18] ne "" && $s[18] ne "(null)") {
		$u .= $s[18]
	}
}

$c[0] = &headCookieSet({ name => "tellu_machine_d_popup_domain", value => $d });
$c[1] = &headCookieSet({ name => "tellu_machine_d_popup_node", value => $n });

&htmlPage({ template => "popup", title => $WINDOW_TITLE . " - " . $n . "." . $d, script => &passwordFuncs({ slice => "passwds" }), header => $n . "." . $d . $t, subheader => $u, content => $PAGE, slices => $MENU, cookie => \@c });

exit(0);
