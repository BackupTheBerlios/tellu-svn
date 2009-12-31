#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "device.lib";
require "device.js";
require "personal.js";



&headPrepare();

my @c = ();
my @r = ();

my $n = &headCookieGet({ name => "tellu_device_node" });
my $s = &headCookieGet({ name => "tellu_device_slice" });
my $m = &headCookieGet({ name => "tellu_device_action" });

if($q->param('action')) {
	#
	# Create device edit form and edit requested device data
	#

	if(&menuDevice({ select => $n }) == 0) {
		my $t = "";
		my $u = "";

		@r = &sendCommand({ command => "pullDevice", item => $n, domain => "", param => "", option => "" });

		if(checkError({ packet => \@r }) == 0) {
			require "device_edit.lib";

			my @s = split(/$ITEM_SEPARATOR/, $r[3]);

			&tableDeviceDetailSlice();

			if($q->param('action') eq "note") {
				&editDeviceNote({ node => $n });
			}
			elsif($q->param('action') eq "modify") {
				&editDeviceNode({ node => $n });
			}

					if($s[5] && $s[5] ne "" && $s[6] && $s[6] ne "" && $s[7] && $s[7] ne "") {
						$t .= $s[7] . " " . $s[5] . " (" . $s[6] . ")";
					}

					if($s[27] && $s[27] ne "" && $s[27] ne "(null)") {
						$u .= $s[27];
					}
		}

		$c[0] = &headCookieSet({ name => "tellu_device_action", value => $q->param('action') });

		if($q->param('disposed') && $q->param('disposed') == 1) {
			$c[1] = &headCookieSet({ name => "tellu_device_node", value => "" });
		}

		&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => &deviceModifyFuncs({ form => "modifyForm" }), header => $t, subheader => $u, content => $PAGE, slices => $MENU, cookie => \@c });
	}
	else {
		&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
	}
}
elsif($q->param('slice')) {
	#
	# Create device selection menu and display requested device data
	#

	if($n eq "Device summary") {
		if(&menuDevice({ select => $n }) == 0) {
			&tableDeviceBriefSlice();

			if($q->param('slice') eq "dev") {
				@r = &sendCommand({ command => "listDevice", item => "", domain => "", param => "model,category,manufacturer,size,memory,connection", option => "" });
			}
			elsif($q->param('slice') eq "net") {
				@r = &sendCommand({ command => "listDevice", item => "", domain => "", param => "netsupport,ipaddress", option => "" });
			}
			elsif($q->param('slice') eq "security") {
				@r = &sendCommand({ command => "listDevice", item => "", domain => "", param => "sernum,secnum,location", option => "" });
			}
			elsif($q->param('slice') eq "repair") {
				@r = &sendCommand({ command => "listDevice", item => "", domain => "", param => "iis,esd,dosd,mosd,totrepairs,lastrepair", option => "" });
			}
			elsif($q->param('slice') eq "warranty") {
				@r = &sendCommand({ command => "listDevice", item => "", domain => "", param => "acquired,warranty", option => "" });
			}
			elsif($q->param('slice') eq "add") {
				@r = &sendCommand({ command => "listDevice", item => "", domain => "", param => "addinfo,descr,note", option => "" });
			}

			if(checkError({ packet => \@r }) == 0) {
				&tableDeviceBrief({ data => $r[3], slice => $q->param('slice'), sort => $q->param('sort'), order => $q->param('order') });
			}

			$c[0] = &headCookieSet({ name => "tellu_device_slice", value => $q->param('slice') });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $n, script => "", header => $n, content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
	else {
		#
		# Create device selection menu and display requested device data
		#

		if(&menuDevice({ select => $n }) == 0) {
			my $t = "";
			my $u = "";

			if($q->param('slice') eq "files") {
				my @w = ();

				@r = &sendCommand({ command => "pullDevice", item => $n, domain => "", param => "", option => "" });

				if(checkError({ packet => \@r }) == 0) {
					my @s = split(/$ITEM_SEPARATOR/, $r[3]);

					@r = &sendCommand({ command => "attachedFile", item => "", domain => "", param => $s[0], option => "" });

					if(checkError({ packet => \@r }) == 0) {
						@s = split(/$ITEM_DELIMITER/, $r[3]);

						foreach my $s (@s) {
							@r = &sendCommand({ command => "pullFile", item => $s, domain => "", param => "id", option => "" });

							if(checkError({ packet => \@r }) == 0) {
								if($r[3] && $r[3] ne "") {

									push @w, $r[3];
								}
							}
						}

						&tableDeviceDetail({ data => join($ITEM_DELIMITER, @w), slice => $q->param('slice'), sort => $q->param('sort'), order => $q->param('order') });
					}
				}
			}
			elsif($q->param('slice') eq "passwds") {
				my @w = ();
				my $k = "";

				if($q->param('key')) {
					$k = $q->param('key');
				}

				@r = &sendCommand({ command => "pullDevice", item => $n, domain => "", param => "", option => "" });

				if(checkError({ packet => \@r }) == 0) {
					my @s = split(/$ITEM_SEPARATOR/, $r[3]);

					@r = &sendCommand({ command => "attachedPassword", item => "", domain => "", param => $s[0], option => "" });

					if(checkError({ packet => \@r }) == 0) {
						@s = split(/$ITEM_DELIMITER/, $r[3]);

						foreach my $s (@s) {
							@r = &sendCommand({ command => "pullPassword", item => $s, domain => "", param => "id", option => "" });

							if(checkError({ packet => \@r }) == 0) {
								if($r[3] && $r[3] ne "") {

									push @w, $r[3];
								}
							}
						}

						&tableDeviceDetail({ data => join($ITEM_DELIMITER, @w), slice => $q->param('slice'), key => $k, sort => $q->param('sort'), order => $q->param('order') });
					}
				}
			}
			else {
				@r = &sendCommand({ command => "pullDevice", item => $n, domain => "", param => "", option => "" });

				if(checkError({ packet => \@r }) == 0) {
					my @s = split(/$ITEM_SEPARATOR/, $r[3]);

					&tableDeviceDetailSlice();

					if($s[5] && $s[5] ne "" && $s[6] && $s[6] ne "" && $s[7] && $s[7] ne "") {
						$t .= $s[7] . " " . $s[5] . " (" . $s[6] . ")";
					}

					if($s[27] && $s[27] ne "" && $s[27] ne "(null)") {
						$u .= $s[27];
					}

					&tableDeviceDetail({ data => $r[3], slice => $q->param('slice'), sort => $q->param('sort'), order => $q->param('order') });
				}
			}

			$c[0] = &headCookieSet({ name => "tellu_device_slice", value => $q->param('slice') });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => &passwordFuncs({ slice => "passwds" }), header => $t, subheader => $u, content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
}
elsif($q->param('deviceNode')) {
	#
	# Create device selection menu and display initial device data
	#

	if($q->param('deviceNode') eq "Device summary") {
		if(&menuDevice({ select => $q->param('deviceNode') }) == 0) {
			&tableDeviceBriefSlice();

			if(!$s || $s eq "") {
				$s = "dev";
			}

			if($s eq "dev") {
				@r = &sendCommand({ command => "listDevice", item => "", domain => "", param => "model,category,manufacturer,size,memory,connection", option => "" });
			}
			elsif($s eq "net") {
				@r = &sendCommand({ command => "listDevice", item => "", domain => "", param => "netsupport,ipaddress", option => "" });
			}
			elsif($s eq "security") {
				@r = &sendCommand({ command => "listDevice", item => "", domain => "", param => "sernum,secnum,location", option => "" });
			}
			elsif($s eq "repair") {
				@r = &sendCommand({ command => "listDevice", item => "", domain => "", param => "iis,esd,dosd,mosd,totrepairs,lastrepair", option => "" });
			}
			elsif($s eq "warranty") {
				@r = &sendCommand({ command => "listDevice", item => "", domain => "", param => "acquired,warranty", option => "" });
			}
			elsif($s eq "add") {
				@r = &sendCommand({ command => "listDevice", item => "", domain => "", param => "addinfo,descr,note", option => "" });
			}

			if(checkError({ packet => \@r }) == 0) {
				&tableDeviceBrief({ data => $r[3], slice => $s, sort => $q->param('sort'), order => $q->param('order') });
			}

			$c[0] = &headCookieSet({ name => "tellu_device_node", value => $q->param('deviceNode') });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $q->param('deviceNode'), script => "", header => $q->param('deviceNode'), content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
	else {
		if(&menuDevice({ select => $q->param('deviceNode') }) == 0) {
			if(!$s || $s eq "") {
				$s = "dev";
			}

			my $t = "";
			my $u = "";

			if($s eq "files") {
				my @w = ();

				@r = &sendCommand({ command => "pullDevice", item => $q->param('deviceNode'), domain => "", param => "", option => "" });

				if(checkError({ packet => \@r }) == 0) {
					my @s = split(/$ITEM_SEPARATOR/, $r[3]);

					@r = &sendCommand({ command => "attachedFile", item => "", domain => "", param => $s[0], option => "" });

					if(checkError({ packet => \@r }) == 0) {
						@s = split(/$ITEM_DELIMITER/, $r[3]);

						foreach my $s (@s) {
							@r = &sendCommand({ command => "pullFile", item => $s, domain => "", param => "id", option => "" });

							if(checkError({ packet => \@r }) == 0) {
								if($r[3] && $r[3] ne "") {

									push @w, $r[3];
								}
							}
						}

						&tableDeviceDetail({ data => join($ITEM_DELIMITER, @w), slice => $s, sort => $q->param('sort'), order => $q->param('order') });
					}
				}
			}
			elsif($s eq "passwds") {
				my @w = ();
				my $k = "";

				if($q->param('key')) {
					$k = $q->param('key');
				}

				@r = &sendCommand({ command => "pullDevice", item => $q->param('deviceNode'), domain => "", param => "", option => "" });

				if(checkError({ packet => \@r }) == 0) {
					my @s = split(/$ITEM_SEPARATOR/, $r[3]);

					@r = &sendCommand({ command => "attachedPassword", item => "", domain => "", param => $s[0], option => "" });

					if(checkError({ packet => \@r }) == 0) {
						@s = split(/$ITEM_DELIMITER/, $r[3]);

						foreach my $s (@s) {
							@r = &sendCommand({ command => "pullPassword", item => $s, domain => "", param => "id", option => "" });

							if(checkError({ packet => \@r }) == 0) {
								if($r[3] && $r[3] ne "") {

									push @w, $r[3];
								}
							}
						}

						&tableDeviceDetail({ data => join($ITEM_DELIMITER, @w), slice => $s, key => $k, sort => $q->param('sort'), order => $q->param('order') });
					}
				}
			}
			else {
				@r = &sendCommand({ command => "pullDevice", item => $q->param('deviceNode'), domain => "", param => "", option => "" });

				if(checkError({ packet => \@r }) == 0) {
					my @s = split(/$ITEM_SEPARATOR/, $r[3]);

					&tableDeviceDetailSlice();

					if($s[5] && $s[5] ne "" && $s[6] && $s[6] ne "" && $s[7] && $s[7] ne "") {
						$t .= $s[7] . " " . $s[5] . " (" . $s[6] . ")";
					}

					if($s[27] && $s[27] ne "" && $s[27] ne "(null)") {
						$u .= $s[27];
					}

					&tableDeviceDetail({ data => $r[3], slice => $s, sort => $q->param('sort'), order => $q->param('order') });
				}
			}

			$c[0] = &headCookieSet({ name => "tellu_device_node", value => $q->param('deviceNode') });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => &passwordFuncs({ slice => "passwds" }), header => $t, subheader => $u, content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
}
else {
	#
	# Create initial device selection menu
	#

	&tableDeviceSlice();

	if(&menuDevice({ select => $n }) == 0) {
		&htmlPage({ title => $WINDOW_TITLE, script => "", header => "Active devices", content => $PAGE, slices => $MENU });
	}
	else {
		&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
	}
}

exit(0);
