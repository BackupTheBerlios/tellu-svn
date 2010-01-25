#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "peripheral.lib";



&headPrepare();

my @c = ();
my @r = ();

my $n = &headCookieGet({ name => "tellu_peripheral_d_popup_node" });

if($q->param('dev') && $q->param('dev') ne "") {
	$n = $q->param('dev');
}

my $t = "";
my $u = "";

my $s = $q->param('slice');

if(!$s || $s eq "") {
	$s = "dev";
}

@r = &sendCommand({ command => "pullPeripheral", item => $n, domain => "", param => "", option => "" });

if(checkError({ packet => \@r }) == 0) {
	&tablePeripheralDetail({ data => $r[3], slice => $s, sort => $q->param('sort'), order => $q->param('order') });
}

@r = &sendCommand({ command => "pullPeripheral", item => $n, domain => "", param => "", option => "" });

if(checkError({ packet => \@r }) == 0) {
	my @s = split(/$ITEM_SEPARATOR/, $r[3]);

	&tablePeripheralListingSlice();

	if($s[5] && $s[5] ne "" && $s[6] && $s[6] ne "" && $s[7] && $s[7] ne "") {
		$t .= $s[7] . " " . $s[5] . " (" . $s[6] . ")";
	}

	if($s[27] && $s[27] ne "" && $s[27] ne "(null)") {
		$u .= $s[27];
	}
}

$c[0] = &headCookieSet({ name => "tellu_peripheral_d_popup_node", value => $n });

&htmlPage({ template => "popup", title => $WINDOW_TITLE . " - " . $t, script => "", header => $t, subheader => $u, content => $PAGE, slices => $MENU, cookie => \@c });

exit(0);
