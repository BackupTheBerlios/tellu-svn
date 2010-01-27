#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "service.lib";



&headPrepare();

my @c = ();
my @r = ();

my $n = &headCookieGet({ name => "tellu_service_d_popup_node" });

if($q->param('dev') && $q->param('dev') ne "") {
	$n = $q->param('dev');
}

my $t = "";
my $u = "";

my $s = $q->param('slice');

if(!$s || $s eq "") {
	$s = "dev";
}

@r = &sendCommand({ command => "pullProvider", item => $n, domain => "", param => "", option => "" });

if(checkError({ packet => \@r }) == 0) {
	&tableProviderDetail({ data => $r[3], slice => $s, sort => $q->param('sort'), order => $q->param('order') });
}

@r = &sendCommand({ command => "pullProvider", item => $n, domain => "", param => "", option => "" });

if(checkError({ packet => \@r }) == 0) {
	my @s = split(/$ITEM_SEPARATOR/, $r[3]);

	&tableProviderListingSlice();

	if($s[6] && $s[6] ne "") {
		$t .= $s[6];
	}

	if($s[24] && $s[24] ne "" && $s[24] ne "(null)") {
		$u .= $s[24];
	}
}

$c[0] = &headCookieSet({ name => "tellu_service_d_popup_node", value => $n });

&htmlPage({ template => "popup", title => $WINDOW_TITLE . " - " . $t, script => "", header => $t, subheader => $u, content => $PAGE, slices => $MENU, cookie => \@c });

exit(0);
