#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "help.lib";



&headPrepare();

my @c = ();
my @r = ();

my $t = "Help";

if($q->param('action')) {
	@r = &sendCommand({ command => "pullHelp", item => "", domain => "", param => $q->param('action'), option => "" });

	if(checkError({ packet => \@r }) == 0) {
		my @s = split(/$ITEM_SEPARATOR/, $r[3]);

		&tableHelpSlice({ page => $s[0] });

		if($s[1] && $s[1] ne "" && $s[1] ne "(null)") {
			$t = $s[1];
		}

		$PAGE .= cleanNull({ string => $s[2] });
	}
	else {
		&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
	}
}

&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => "", header => $t, content => $PAGE, slices => $MENU });

exit(0);
