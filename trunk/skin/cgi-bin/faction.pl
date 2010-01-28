#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "faction.lib";



&headPrepare();

my @c = ();
my @r = ();

my $n = &headCookieGet({ name => "tellu_faction_node" });
my $s = &headCookieGet({ name => "tellu_faction_slice" });

if($q->param('slice')) {
	my $k = "";

	if($q->param('key') && $q->param('key') ne "") {
		$k = $q->param('key');
	}

	$s = $q->param('slice');

	if(!$s || $s eq "") {
		$s = "node";
	}

	&factionThing({ node => $n, domain => "", slice => $s, sort => $q->param('sort'), order => $q->param('order'), cookie => "tellu_faction_slice", value => $s, key => $k });
}
elsif($q->param('factionNode')) {
	my $k = "";

	if($q->param('key') && $q->param('key') ne "") {
		$k = $q->param('key');
	}

	if(!$s || $s eq "") {
		$s = "node";
	}

	&factionThing({ node => $q->param('factionNode'), domain => "", slice => $s, sort => $q->param('sort'), order => $q->param('order'), cookie => "tellu_faction_node", value => $q->param('factionNode'), key => $k });
}
else {
	&tableFactionSlice();

	if(&menuFaction({ select => $n }) == 0) {
		&htmlPage({ title => $WINDOW_TITLE, script => $SCRIPT, header => "Factions", content => $PAGE, slices => $MENU });
	}
	else {
		&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
	}
}

exit(0);



sub factionThing {
	my ($arg) = @_;

	my @c = ();
	my @r = ();

	if(&menuFaction({ select => $arg->{node} }) == 0) {
		my $t = "";

		if(!$arg->{slice} || $arg->{slice} eq "") {
			$arg->{slice} = "node";
		}

		&tableFactionDetail({ node => $arg->{node}, slice => $arg->{slice}, sort => $arg->{sort}, order => $arg->{order}, key => $arg->{key} });

		@r = &sendCommand({ command => "pullFaction", item => $arg->{node}, domain => "", param => "id", option => "" });

		if(checkError({ packet => \@r }) == 0) {
			my @s = split(/$ITEM_SEPARATOR/, $r[3]);

			&tableFactionDetailSlice();

			if($s[2] && $s[2] ne "") {
				$t .= $s[2];
			}
		}

		$c[0] = &headCookieSet({ name => $arg->{cookie}, value => $arg->{value} });

		&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => $SCRIPT, header => $t, subheader => "", content => $PAGE, slices => $MENU, cookie => \@c });
	}
	else {
		&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
	}
}
