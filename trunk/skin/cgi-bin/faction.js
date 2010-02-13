#!/usr/bin/perl

my ($pack, $f, $line) = caller;

if($pack eq "" && $f eq "" && $line eq "") {
	print STDOUT "Content-Type: text/html" . "\r\n\r\n";

	exit(0);
}

sub factionListingFuncs {
	my ($arg) = @_;

	my $r = "";

	$r .= "function popupFaction(grp, slice, width, height) {" . $CONFIG_LINEFEED;
	$r .= " window.open('faction_popup.pl?grp=' +grp+ '&slice=' +slice+ '', '', 'scrollbars,resizable,height=' +height+ ',width=' +width+ '');" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;

	return $r;
}

1;
