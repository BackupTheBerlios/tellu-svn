#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "device.lib";
require "device.js";



&headPrepare();

my @c = ();
my @r = ();

my $n = &headCookieGet({ name => "tellu_device_d_node" });
my $s = &headCookieGet({ name => "tellu_device_d_slice" });
my $m = &headCookieGet({ name => "tellu_device_d_action" });

if($q->param('action')) {
	if(&menuDDevice({ select => $n }) == 0) {
		my $t = "";
		my $u = "";

		@r = &sendCommand({ command => "pullDevice", item => $n, domain => "", param => "", option => "" });

		if(checkError({ packet => \@r }) == 0) {
			require "device_d_edit.lib";

			my @s = split(/$ITEM_SEPARATOR/, $r[3]);

			&tableDDeviceDetailSlice();

			if($q->param('action') eq "note") {
				&editDisposedDeviceNote({ node => $n });
			}
			elsif($q->param('action') eq "modify") {
				&editDisposedDeviceNode({ node => $n });
			}

			if($s[5] && $s[5] ne "" && $s[6] && $s[6] ne "" && $s[7] && $s[7] ne "") {
				$t .= $s[7] . " " . $s[5] . " (" . $s[6] . ")";
			}

			if($s[27] && $s[27] ne "" && $s[27] ne "(null)") {
				$u .= $s[27];
			}
		}

		$c[0] = &headCookieSet({ name => "tellu_device_d_action", value => $q->param('action') });

		if($q->param('disposed') && $q->param('disposed') == 2) {
			$c[1] = &headCookieSet({ name => "tellu_device_d_node", value => "" });
		}

		&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => &deviceModifyDisposedFuncs({ form => "modifyDisposedForm" }), header => $t, subheader => $u, content => $PAGE, slices => $MENU, cookie => \@c });
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

	&deviceThing({ node => $n, domain => "", slice => $s, sort => $q->param('sort'), order => $q->param('order'), cookie => "tellu_device_d_slice", value => $s });
}
elsif($q->param('deviceNode')) {
	if(!$s || $s eq "") {
		$s = "dev";
	}

	&deviceThing({ node => $q->param('deviceNode'), domain => "", slice => $s, sort => $q->param('sort'), order => $q->param('order'), cookie => "tellu_device_d_node", value => $q->param('deviceNode') });
}
else {
	&tableDDeviceSlice();

	if(&menuDDevice({ select => $n }) == 0) {
		&htmlPage({ title => $WINDOW_TITLE, script => "", header => "Disposed devices", content => $PAGE, slices => $MENU });
	}
	else {
		&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
	}
}

exit(0);



sub deviceThing {
	my ($arg) = @_;

	my @c = ();
	my @r = ();

	if($arg->{node} eq "Device summary") {
		if(&menuDDevice({ select => $arg->{node} }) == 0) {
			&tableDeviceBriefSlice();

			if(!$arg->{slice} || $arg->{slice} eq "") {
				$arg->{slice} = "dev";
			}

			if($arg->{slice} eq "dev") {
				@r = &sendCommand({ command => "listDisposedDevice", item => "", domain => "", param => "model,category,manufacturer,size,memory,connection", option => "" });
			}
			elsif($arg->{slice} eq "net") {
				@r = &sendCommand({ command => "listDisposedDevice", item => "", domain => "", param => "netsupport,ipaddress", option => "" });
			}
			elsif($arg->{slice} eq "security") {
				@r = &sendCommand({ command => "listDisposedDevice", item => "", domain => "", param => "sernum,secnum,location", option => "" });
			}
			elsif($arg->{slice} eq "repair") {
				@r = &sendCommand({ command => "listDisposedDevice", item => "", domain => "", param => "iis,esd,dosd,mosd,totrepairs,lastrepair", option => "" });
			}
			elsif($arg->{slice} eq "warranty") {
				@r = &sendCommand({ command => "listDisposedDevice", item => "", domain => "", param => "acquired,warranty", option => "" });
			}
			elsif($arg->{slice} eq "add") {
				@r = &sendCommand({ command => "listDisposedDevice", item => "", domain => "", param => "addinfo,descr,note", option => "" });
			}

			if(checkError({ packet => \@r }) == 0) {
				&tableDeviceBrief({ data => $r[3], slice => $arg->{slice}, sort => $arg->{sort}, order => $arg->{order} });
			}

			$c[0] = &headCookieSet({ name => $arg->{cookie}, value => $arg->{value} });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $arg->{node}, script => "", header => $arg->{node}, content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
	elsif($arg->{node} eq "Device listing") {
		if(&menuDDevice({ select => $arg->{node} }) == 0) {
			&tableDeviceListingSlice();

			if(!$arg->{slice} || $arg->{slice} eq "") {
				$arg->{slice} = "dev";
			}

			if($arg->{slice} eq "dev") {
				@r = &sendCommand({ command => "listDisposedDevice", item => "", domain => "", param => "model,category,manufacturer,size,memory,connection", option => "" });
			}
			elsif($arg->{slice} eq "net") {
				@r = &sendCommand({ command => "listDisposedDevice", item => "", domain => "", param => "netsupport,ipaddress", option => "" });
			}
			elsif($arg->{slice} eq "security") {
				@r = &sendCommand({ command => "listDisposedDevice", item => "", domain => "", param => "sernum,secnum,location", option => "" });
			}
			elsif($arg->{slice} eq "repair") {
				@r = &sendCommand({ command => "listDisposedDevice", item => "", domain => "", param => "iis,esd,dosd,mosd,totrepairs,lastrepair", option => "" });
			}
			elsif($arg->{slice} eq "warranty") {
				@r = &sendCommand({ command => "listDisposedDevice", item => "", domain => "", param => "acquired,warranty", option => "" });
			}
			elsif($arg->{slice} eq "add") {
				@r = &sendCommand({ command => "listDisposedDevice", item => "", domain => "", param => "addinfo,descr,note", option => "" });
			}

			if(checkError({ packet => \@r }) == 0) {
				&tableDeviceListing({ data => $r[3], slice => $arg->{slice}, sort => $arg->{sort}, order => $arg->{order} });
			}

			$c[0] = &headCookieSet({ name => $arg->{cookie}, value => $arg->{value} });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $arg->{node}, script => &deviceListingDisposedFuncs(), header => $arg->{node}, content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
	else {
		if(&menuDDevice({ select => $arg->{node} }) == 0) {
			my $t = "";
			my $u = "";

			if(!$arg->{slice} || $arg->{slice} eq "") {
				$arg->{slice} = "dev";
			}

			@r = &sendCommand({ command => "pullDevice", item => $arg->{node}, domain => "", param => "", option => "" });

			if(checkError({ packet => \@r }) == 0) {
				&tableDeviceDetail({ data => $r[3], slice => $arg->{slice}, sort => $arg->{sort}, order => $arg->{order} });
			}

			@r = &sendCommand({ command => "pullDevice", item => $arg->{node}, domain => "", param => "", option => "" });

			if(checkError({ packet => \@r }) == 0) {
				my @s = split(/$ITEM_SEPARATOR/, $r[3]);

				&tableDDeviceDetailSlice();

				if($s[5] && $s[5] ne "" && $s[6] && $s[6] ne "" && $s[7] && $s[7] ne "") {
					$t .= $s[7] . " " . $s[5] . " (" . $s[6] . ")";
				}

				if($s[27] && $s[27] ne "" && $s[27] ne "(null)") {
					$u .= $s[27];
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
