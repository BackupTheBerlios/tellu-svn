#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "access.lib";
require "chest.lib";
require "prefs.lib";



&headPrepare();

if($q->param('uid')) {
	my @c = ();

	$SESSION_UID = $q->param('uid');

	if(&formAccessHandshake({ pwd => $q->param('pwd') }) != 0) {
		&tableAccessSlice();
		&formAccessLogin({ message => "Sorry, your username and password are incorrect - please try again" });

		$c[0] = &headCookieSet({ name => "tellu_cid", value => "" });
		$c[1] = &headCookieSet({ name => "tellu_uid", value => "" });

		&htmlPage({ template => "login", title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => "", content => $PAGE, slices => $MENU, cookie => \@c });
	}
	else {
		my $p = &prefsHomepage();

		$c[0] = &headCookieSet({ name => "tellu_cid", value => $SESSION_CID });
		$c[1] = &headCookieSet({ name => "tellu_uid", value => $SESSION_UID });

		$PAGE .= "<p>&nbsp;</p>";
		$PAGE .= "<p>If page is not redirected automatically, please click <a href=\"" . $p . ".pl\">here</a>.</p>";

		&htmlPage({ template => "login", redirect => $p, title => $WINDOW_TITLE, script => "", header => "", content => $PAGE, slices => $MENU, cookie => \@c });
	}
}
else {
	&tableAccessSlice();
	&formAccessLogin({ message => "Enter your account details below to login to " . $WINDOW_TITLE });

	&htmlPage({ template => "login", title => $WINDOW_TITLE, script => "", header => "", content => $PAGE, slices => $MENU });
}

exit(0);
