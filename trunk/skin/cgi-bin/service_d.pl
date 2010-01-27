#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "service.lib";
require "service.js";



&headPrepare();

my @c = ();
my @r = ();

my $n = &headCookieGet({ name => "tellu_service_d_node" });
my $s = &headCookieGet({ name => "tellu_service_d_slice" });
my $m = &headCookieGet({ name => "tellu_service_d_action" });

if($q->param('action')) {
	if(&menuDProvider({ select => $n }) == 0) {
		my $t = "";
		my $u = "";

		@r = &sendCommand({ command => "pullProvider", item => $n, domain => "", param => "", option => "" });

		if(checkError({ packet => \@r }) == 0) {
			require "service_d_edit.lib";

			my @s = split(/$ITEM_SEPARATOR/, $r[3]);

			&tableDProviderDetailSlice();

			if($q->param('action') eq "note") {
				&editDisposedProviderNote({ node => $n });
			}
			elsif($q->param('action') eq "modify") {
				&editDisposedProviderNode({ node => $n });
			}

			if($s[6] && $s[6] ne "") {
				$t .= $s[6];
			}

			if($s[24] && $s[24] ne "" && $s[24] ne "(null)") {
				$u .= $s[24];
			}
		}

		$c[0] = &headCookieSet({ name => "tellu_service_d_action", value => $q->param('action') });

		if($q->param('disposed') && $q->param('disposed') == 2) {
			$c[1] = &headCookieSet({ name => "tellu_service_d_node", value => "" });
		}

		&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => &serviceModifyDisposedFuncs({ form => "modifyDisposedForm" }), header => $t, subheader => $u, content => $PAGE, slices => $MENU, cookie => \@c });
	}
	else {
		&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
	}
}
elsif($q->param('slice')) {
	$s = $q->param('slice');

	if(!$s || $s eq "") {
		$s = "dev";
	}

	&serviceThing({ node => $n, domain => "", slice => $s, sort => $q->param('sort'), order => $q->param('order'), cookie => "tellu_service_d_slice", value => $s });
}
elsif($q->param('serviceNode')) {
	if(!$s || $s eq "") {
		$s = "dev";
	}

	&serviceThing({ node => $q->param('serviceNode'), domain => "", slice => $s, sort => $q->param('sort'), order => $q->param('order'), cookie => "tellu_service_d_node", value => $q->param('serviceNode') });
}
else {
	&tableDProviderSlice();

	if(&menuDProvider({ select => $n }) == 0) {
		&htmlPage({ title => $WINDOW_TITLE, script => "", header => "Disposed services", content => $PAGE, slices => $MENU });
	}
	else {
		&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
	}
}

exit(0);



sub serviceThing {
	my ($arg) = @_;

	my @c = ();
	my @r = ();

	if($arg->{node} eq "Service provider summary") {
		if(&menuDProvider({ select => $arg->{node} }) == 0) {
			&tableProviderBriefSlice();

			if(!$arg->{slice} || $arg->{slice} eq "") {
				$arg->{slice} = "dev";
			}

			if($arg->{slice} eq "dev") {
				@r = &sendCommand({ command => "listDisposedProvider", item => "", domain => "", param => "type_id,name,street,zip,city,country", option => "" });
			}
			elsif($arg->{slice} eq "net") {
				@r = &sendCommand({ command => "listDisposedProvider", item => "", domain => "", param => "telephone1,telephone2,fax1,fax2", option => "" });
			}
			elsif($arg->{slice} eq "security") {
				@r = &sendCommand({ command => "listDisposedProvider", item => "", domain => "", param => "cont_person,cont_telephone1,cont_telephone2,cont_fax1,cont_fax2,cont_email1,cont_email2", option => "" });
			}
			elsif($arg->{slice} eq "repair") {
				@r = &sendCommand({ command => "listDisposedProvider", item => "", domain => "", param => "brands", option => "" });
			}
			elsif($arg->{slice} eq "add") {
				@r = &sendCommand({ command => "listDisposedProvider", item => "", domain => "", param => "addinfo,descr,note", option => "" });
			}

			if(checkError({ packet => \@r }) == 0) {
				&tableProviderBrief({ data => $r[3], slice => $arg->{slice}, sort => $arg->{sort}, order => $arg->{order} });
			}

			$c[0] = &headCookieSet({ name => $arg->{cookie}, value => $arg->{value} });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $arg->{node}, script => "", header => $arg->{node}, content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
	elsif($arg->{node} eq "Service provider listing") {
		if(&menuDProvider({ select => $arg->{node} }) == 0) {
			&tableProviderListingSlice();

			if(!$arg->{slice} || $arg->{slice} eq "") {
				$arg->{slice} = "dev";
			}

			if($arg->{slice} eq "dev") {
				@r = &sendCommand({ command => "listDisposedProvider", item => "", domain => "", param => "type_id,name,street,zip,city,country", option => "" });
			}
			elsif($arg->{slice} eq "net") {
				@r = &sendCommand({ command => "listDisposedProvider", item => "", domain => "", param => "telephone1,telephone2,fax1,fax2", option => "" });
			}
			elsif($arg->{slice} eq "security") {
				@r = &sendCommand({ command => "listDisposedProvider", item => "", domain => "", param => "cont_person,cont_telephone1,cont_telephone2,cont_fax1,cont_fax2,cont_email1,cont_email2", option => "" });
			}
			elsif($arg->{slice} eq "repair") {
				@r = &sendCommand({ command => "listDisposedProvider", item => "", domain => "", param => "brands", option => "" });
			}
			elsif($arg->{slice} eq "add") {
				@r = &sendCommand({ command => "listDisposedProvider", item => "", domain => "", param => "addinfo,descr,note", option => "" });
			}

			if(checkError({ packet => \@r }) == 0) {
				&tableProviderListing({ data => $r[3], slice => $arg->{slice}, sort => $arg->{sort}, order => $arg->{order} });
			}

			$c[0] = &headCookieSet({ name => $arg->{cookie}, value => $arg->{value} });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $arg->{node}, script => &serviceListingDisposedFuncs(), header => $arg->{node}, content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
	else {
		if(&menuDProvider({ select => $arg->{node} }) == 0) {
			my $t = "";
			my $u = "";

			if(!$arg->{slice} || $arg->{slice} eq "") {
				$arg->{slice} = "dev";
			}

			@r = &sendCommand({ command => "pullProvider", item => $arg->{node}, domain => "", param => "", option => "" });

			if(checkError({ packet => \@r }) == 0) {
				&tableProviderDetail({ data => $r[3], slice => $arg->{slice}, sort => $arg->{sort}, order => $arg->{order} });
			}

			@r = &sendCommand({ command => "pullProvider", item => $arg->{node}, domain => "", param => "", option => "" });

			if(checkError({ packet => \@r }) == 0) {
				my @s = split(/$ITEM_SEPARATOR/, $r[3]);

				&tableDProviderDetailSlice();

				if($s[6] && $s[6] ne "") {
					$t .= $s[6];
				}

				if($s[24] && $s[24] ne "" && $s[24] ne "(null)") {
					$u .= $s[24];
				}
			}

			$c[0] = &headCookieSet({ name => $arg->{cookie}, value => $arg->{value} });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => "", header => $t, subheader => $u, content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
}
