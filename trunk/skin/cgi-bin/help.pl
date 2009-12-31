#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "help.lib";



&headPrepare();

my @c = ();
my @r = ();

my $h = &headCookieGet({ name => "tellu_help_action" });

if($q->param('action')) {
	my $t = "Help";
	@r = &sendCommand({ command => "pullHelp", item => "", domain => "", param => $q->param('action'), option => "" });

	if(checkError({ packet => \@r }) == 0) {
		my @s = split(/$ITEM_SEPARATOR/, $r[3]);

		&tableHelpSlice({ page => $s[0] });

		if($s[1] && $s[1] ne "" && $s[1] ne "(null)") {
			$t = $s[1];
		}

$PAGE .= "$s[2] <br>";

		$c[0] = &headCookieSet({ name => "tellu_help_action", value => $s[0] });

		&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => "", header => $t, content => $PAGE, slices => $MENU, cookie => \@c });
	}
	else {
		&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
	}
}
else {
	# DISPLAY SOMETHING?
}

exit(0);
