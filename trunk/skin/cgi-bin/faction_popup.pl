#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "faction.lib";



&headPrepare();

my @c = ();
my @r = ();

my $n = &headCookieGet({ name => "tellu_faction_popup_node" });

if($q->param('grp') && $q->param('grp') ne "") {
	$n = $q->param('grp');
}

my $t = "";

my $s = $q->param('slice');

if(!$s || $s eq "" || $s eq "grp") {
	$s = "node";
}

my $k = "";

if($q->param('key') && $q->param('key') ne "") {
	$k = $q->param('key');
}

&tableFactionDetail({ node => $n, slice => $s, sort => $q->param('sort'), order => $q->param('order'), key => $k });

@r = &sendCommand({ command => "pullFaction", item => $n, domain => "", param => "id", option => "" });

if(checkError({ packet => \@r }) == 0) {
	my @s = split(/$ITEM_SEPARATOR/, $r[3]);

	&tableFactionDetailSlice();

	if($s[2] && $s[2] ne "") {
		$t .= $s[2];
	}
}

if($s eq "node") {
	require "machine.js";

	$SCRIPT = &machineListingFuncs();
}
elsif($s eq "dev") {
	require "device.js";

	$SCRIPT = &deviceListingFuncs();
}
elsif($s eq "per") {
	require "peripheral.js";

	$SCRIPT = &peripheralListingFuncs();
}
elsif($s eq "ser") {
	require "service.js";

	$SCRIPT = &serviceListingFuncs();
}
elsif($s eq "pwd") {
	require "personal.js";

	$SCRIPT = &passwordFuncs({ slice => $s });
}

$c[0] = &headCookieSet({ name => "tellu_faction_popup_node", value => $n });

&htmlPage({ template => "popup", title => $WINDOW_TITLE . " - " . $t, script => $SCRIPT, header => $t, content => $PAGE, slices => $MENU, cookie => \@c });

exit(0);
