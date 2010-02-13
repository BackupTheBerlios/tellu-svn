#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "machine.lib";



&headPrepare();

my @c = ();
my @r = ();

my $d = &headCookieGet({ name => "tellu_machine_popup_domain" });
my $n = &headCookieGet({ name => "tellu_machine_popup_node" });

if($q->param('host') && $q->param('host') ne "") {
	@r = split(/\|/, $q->param('host'), 2);

	$n = $r[0];
	$d = $r[1];
}

my $t = "";
my $u = "";

my $s = $q->param('slice');

if(!$s || $s eq "" || $s eq "incs" || $s eq "nper") {
	$s = "node";

	@r = &sendCommand({ command => "pullMachine", item => $n, domain => $d, param => $s, option => "" });

	if(checkError({ packet => \@r }) == 0) {
		&tableMachineDetail({ data => $r[3], slice => $s, sort => $q->param('sort'), order => $q->param('order') });
	}
}
elsif($s eq "addinfo" || $s eq "repair" || $s eq "security" || $s eq "warranty") {
	@r = &sendCommand({ command => "pullMachine", item => $n, domain => $d, param => "node", option => "" });

	if(checkError({ packet => \@r }) == 0) {
		&tableMachineDetail({ data => $r[3], slice => $s, sort => $q->param('sort'), order => $q->param('order') });
	}
}
else {
	@r = &sendCommand({ command => "pullMachine", item => $n, domain => $d, param => $s, option => "" });

	if(checkError({ packet => \@r }) == 0) {
		&tableMachineDetail({ data => $r[3], slice => $s, sort => $q->param('sort'), order => $q->param('order') });
	}
}

@r = &sendCommand({ command => "pullMachine", item => $n, domain => $d, param => "node", option => "" });

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

$c[0] = &headCookieSet({ name => "tellu_machine_popup_domain", value => $d });
$c[1] = &headCookieSet({ name => "tellu_machine_popup_node", value => $n });

&htmlPage({ template => "popup", title => $WINDOW_TITLE . " - " . $n . "." . $d, script => "", header => $n . "." . $d . $t, subheader => $u, content => $PAGE, slices => $MENU, cookie => \@c });

exit(0);
