#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "peripheral.lib";
require "peripheral.js";
require "personal.js";



&headPrepare();

my @c = ();
my @r = ();

my $n = &headCookieGet({ name => "tellu_peripheral_node" });
my $s = &headCookieGet({ name => "tellu_peripheral_slice" });
my $g = &headCookieGet({ name => "tellu_peripheral_leaf" });
my $m = &headCookieGet({ name => "tellu_peripheral_action" });

if($q->param('action')) {
	if(&menuPeripheral({ select => $n }) == 0) {
		my $t = "";
		my $u = "";

		@r = &sendCommand({ command => "pullPeripheral", item => $n, domain => "", param => "", option => "" });

		if(checkError({ packet => \@r }) == 0) {
			require "peripheral_edit.lib";

			my @s = split(/$ITEM_SEPARATOR/, $r[3]);

			&tablePeripheralDetailSlice();

			if($q->param('action') eq "note") {
				&editPeripheralNote({ node => $n });
			}
			elsif($q->param('action') eq "modify") {
				&editPeripheralNode({ node => $n });
			}

			if($s[5] && $s[5] ne "" && $s[6] && $s[6] ne "" && $s[7] && $s[7] ne "") {
				$t .= $s[7] . " " . $s[5] . " (" . $s[6] . ")";
			}

			if($s[27] && $s[27] ne "" && $s[27] ne "(null)") {
				$u .= $s[27];
			}
		}

		$c[0] = &headCookieSet({ name => "tellu_peripheral_action", value => $q->param('action') });

		if($q->param('disposed') && $q->param('disposed') == 1) {
			$c[1] = &headCookieSet({ name => "tellu_peripheral_node", value => "" });
		}

		&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => &peripheralModifyFuncs({ form => "modifyForm" }), header => $t, subheader => $u, content => $PAGE, slices => $MENU, cookie => \@c });
	}
	else {
		&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
	}
}
elsif($q->param('slice')) {
	my $f = $g;

	if($q->param('leaf') && $q->param('leaf') ne "") {
		$f = $q->param('leaf');
	}

	if(!$f || $f eq "") {
		$f = 1;
	}

	$s = $q->param('slice');

	if(!$s || $s eq "") {
		$s = "dev";
	}

	&peripheralThing({ node => $n, domain => "", slice => $s, leaf => $f, sort => $q->param('sort'), order => $q->param('order'), cookie => "tellu_peripheral_slice", value => $s, key => $q->param('key') });
}
elsif($q->param('peripheralNode')) {
	my $f = $g;

	if($q->param('leaf') && $q->param('leaf') ne "") {
		$f = $q->param('leaf');
	}

	if(!$f || $f eq "") {
		$f = 1;
	}

	if(!$s || $s eq "") {
		$s = "dev";
	}

	&peripheralThing({ node => $q->param('peripheralNode'), domain => "", slice => $s, leaf => $f, sort => $q->param('sort'), order => $q->param('order'), cookie => "tellu_peripheral_node", value => $q->param('peripheralNode'), key => $q->param('key') });
}
else {
	&tablePeripheralSlice();

	if(&menuPeripheral({ select => $n }) == 0) {
		&htmlPage({ title => $WINDOW_TITLE, script => "", header => "Active peripherals", content => $PAGE, slices => $MENU });
	}
	else {
		&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
	}
}

exit(0);



sub peripheralThing {
	my ($arg) = @_;

	my @c = ();
	my @r = ();

	if($arg->{node} eq "Peripheral summary") {
		if(&menuPeripheral({ select => $arg->{node} }) == 0) {
			&tablePeripheralBriefSlice();

			if(!$arg->{slice} || $arg->{slice} eq "" || $arg->{slice} eq "incs") {
				$arg->{slice} = "dev";
			}

			if($arg->{slice} eq "dev") {
				@r = &sendCommand({ command => "listPeripheral", item => "", domain => "", param => "model,category,manufacturer,size,memory,connection", option => "" });
			}
			elsif($arg->{slice} eq "net") {
				@r = &sendCommand({ command => "listPeripheral", item => "", domain => "", param => "netsupport,ipaddress", option => "" });
			}
			elsif($arg->{slice} eq "security") {
				@r = &sendCommand({ command => "listPeripheral", item => "", domain => "", param => "sernum,secnum,location", option => "" });
			}
			elsif($arg->{slice} eq "repair") {
				@r = &sendCommand({ command => "listPeripheral", item => "", domain => "", param => "iis,esd,dosd,mosd,totrepairs,lastrepair", option => "" });
			}
			elsif($arg->{slice} eq "warranty") {
				@r = &sendCommand({ command => "listPeripheral", item => "", domain => "", param => "acquired,warranty", option => "" });
			}
			elsif($arg->{slice} eq "add") {
				@r = &sendCommand({ command => "listPeripheral", item => "", domain => "", param => "addinfo,descr,note", option => "" });
			}

			if(checkError({ packet => \@r }) == 0) {
				&tablePeripheralBrief({ data => $r[3], slice => $arg->{slice}, sort => $arg->{sort}, order => $arg->{order} });
			}

			$c[0] = &headCookieSet({ name => $arg->{cookie}, value => $arg->{value} });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $arg->{node}, script => "", header => $arg->{node}, content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
	elsif($arg->{node} eq "Peripheral listing") {
		if(&menuPeripheral({ select => $arg->{node} }) == 0) {
			&tablePeripheralListingSlice();

			if(!$arg->{slice} || $arg->{slice} eq "" || $arg->{slice} eq "incs") {
				$arg->{slice} = "dev";
			}

			if($arg->{slice} eq "dev") {
				@r = &sendCommand({ command => "listPeripheral", item => "", domain => "", param => "model,category,manufacturer,size,memory,connection", option => "" });
			}
			elsif($arg->{slice} eq "net") {
				@r = &sendCommand({ command => "listPeripheral", item => "", domain => "", param => "netsupport,ipaddress", option => "" });
			}
			elsif($arg->{slice} eq "security") {
				@r = &sendCommand({ command => "listPeripheral", item => "", domain => "", param => "sernum,secnum,location", option => "" });
			}
			elsif($arg->{slice} eq "repair") {
				@r = &sendCommand({ command => "listPeripheral", item => "", domain => "", param => "iis,esd,dosd,mosd,totrepairs,lastrepair", option => "" });
			}
			elsif($arg->{slice} eq "warranty") {
				@r = &sendCommand({ command => "listPeripheral", item => "", domain => "", param => "acquired,warranty", option => "" });
			}
			elsif($arg->{slice} eq "add") {
				@r = &sendCommand({ command => "listPeripheral", item => "", domain => "", param => "addinfo,descr,note", option => "" });
			}

			if(checkError({ packet => \@r }) == 0) {
				&tablePeripheralListing({ data => $r[3], slice => $arg->{slice}, sort => $arg->{sort}, order => $arg->{order} });
			}

			$c[0] = &headCookieSet({ name => $arg->{cookie}, value => $arg->{value} });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $arg->{node}, script => &peripheralListingFuncs(), header => $arg->{node}, content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
	else {
		if(&menuPeripheral({ select => $arg->{node} }) == 0) {
			my $t = "";
			my $u = "";

			if(!$arg->{slice} || $arg->{slice} eq "") {
				$arg->{slice} = "dev";
			}

			if($arg->{slice} eq "incs") {
				my @l = ('Files', 'Passwords', 'Devices', 'Peripherals', 'Services');
				my @w = ();

				$PAGE .= "<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\">";
				$PAGE .= "<tr class=\"middle\">";

				my $s = 1;

				foreach my $l (@l) {
					if($s == $arg->{leaf}) {
						$PAGE .= "<td align=\"right\" valign=\"bottom\"><img alt=\"\" src=\"/pics/leaf_left_s.png\"></td><td class=\"leaf_s\"><a href=\"" . $SELF . "?slice=" . $arg->{slice} . "&leaf=" . $s . "\">" . $l . "</a></td><td align=\"left\" valign=\"bottom\"><img alt=\"\" src=\"/pics/leaf_right_s.png\"></td>";
					}
					else {
						$PAGE .= "<td align=\"right\" valign=\"bottom\"><img alt=\"\" src=\"/pics/leaf_left.png\"></td><td class=\"leaf\"><a href=\"" . $SELF . "?slice=" . $arg->{slice} . "&leaf=" . $s . "\">" . $l . "</a></td><td align=\"left\" valign=\"bottom\"><img alt=\"\" src=\"/pics/leaf_right.png\"></td>";
					}

					$s++;
				}

				$PAGE .= "</tr>";
				$PAGE .= "</table>";

				if(!$arg->{leaf} || $arg->{leaf} == 1) {
					@r = &sendCommand({ command => "pullPeripheral", item => $arg->{node}, domain => "", param => "", option => "" });

					if(checkError({ packet => \@r }) == 0) {
						my @s = split(/$ITEM_SEPARATOR/, $r[3]);

						@r = &sendCommand({ command => "attachedFile", item => "", domain => "", param => $arg->{node}, option => "peripheral" });

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

							&tablePeripheralDetail({ data => join($ITEM_DELIMITER, @w), slice => $arg->{slice}, leaf => $arg->{leaf}, sort => $arg->{sort}, order => $arg->{order} });
						}
					}
				}
				elsif($arg->{leaf} == 2) {
					my $k = "";

					if($arg->{key}) {
						$k = $arg->{key};
					}

					@r = &sendCommand({ command => "pullPeripheral", item => $arg->{node}, domain => "", param => "", option => "" });

					if(checkError({ packet => \@r }) == 0) {
						my @s = split(/$ITEM_SEPARATOR/, $r[3]);

						@r = &sendCommand({ command => "attachedPassword", item => "", domain => "", param => $arg->{node}, option => "peripheral" });

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

							&tablePeripheralDetail({ data => join($ITEM_DELIMITER, @w), slice => $arg->{slice}, leaf => $arg->{leaf}, sort => $arg->{sort}, order => $arg->{order}, key => $k });
						}
					}
				}
				elsif($arg->{leaf} == 3) {
					@r = &sendCommand({ command => "pullPeripheral", item => $arg->{node}, domain => "", param => "", option => "" });

					if(checkError({ packet => \@r }) == 0) {
						my @s = split(/$ITEM_SEPARATOR/, $r[3]);

						@r = &sendCommand({ command => "attachedPeripheralDevice", item => "", domain => "", param => $arg->{node}, option => "peripheral" });

						if(checkError({ packet => \@r }) == 0) {
							@s = split(/$ITEM_DELIMITER/, $r[3]);

							foreach my $s (@s) {
								@r = &sendCommand({ command => "pullDevice", item => $s, domain => "", param => "", option => "" });

								if(checkError({ packet => \@r }) == 0) {
									if($r[3] && $r[3] ne "") {
										for(my $i = 0; $i < 4; $i++) {
											$r[3] =~ s/^.*?$ITEM_SEPARATOR//;
										}

										push @w, $r[3];
									}
								}
							}

							&tablePeripheralDetail({ data => join($ITEM_DELIMITER, @w), slice => $arg->{slice}, leaf => $arg->{leaf}, sort => $arg->{sort}, order => $arg->{order} });
						}
					}
				}
				elsif($arg->{leaf} == 4) {
					@r = &sendCommand({ command => "pullPeripheral", item => $arg->{node}, domain => "", param => "", option => "" });

					if(checkError({ packet => \@r }) == 0) {
						my @s = split(/$ITEM_SEPARATOR/, $r[3]);

						@r = &sendCommand({ command => "attachedPeripheralPeripheral", item => "", domain => "", param => $arg->{node}, option => "peripheral" });

						if(checkError({ packet => \@r }) == 0) {
							@s = split(/$ITEM_DELIMITER/, $r[3]);

							foreach my $s (@s) {
								@r = &sendCommand({ command => "pullPeripheral", item => $s, domain => "", param => "", option => "" });

								if(checkError({ packet => \@r }) == 0) {
									if($r[3] && $r[3] ne "") {
										for(my $i = 0; $i < 4; $i++) {
											$r[3] =~ s/^.*?$ITEM_SEPARATOR//;
										}

										push @w, $r[3];
									}
								}
							}

							&tablePeripheralDetail({ data => join($ITEM_DELIMITER, @w), slice => $arg->{slice}, leaf => $arg->{leaf}, sort => $arg->{sort}, order => $arg->{order} });
						}
					}
				}
				elsif($arg->{leaf} == 5) {
					@r = &sendCommand({ command => "pullPeripheral", item => $arg->{node}, domain => "", param => "", option => "" });

					if(checkError({ packet => \@r }) == 0) {
						my @s = split(/$ITEM_SEPARATOR/, $r[3]);

						@r = &sendCommand({ command => "attachedProvider", item => "", domain => "", param => $arg->{node}, option => "peripheral" });

						if(checkError({ packet => \@r }) == 0) {
							@s = split(/$ITEM_DELIMITER/, $r[3]);

							foreach my $s (@s) {
								@r = &sendCommand({ command => "pullProvider", item => $s, domain => "", param => "", option => "" });

								if(checkError({ packet => \@r }) == 0) {
									if($r[3] && $r[3] ne "") {
										for(my $i = 0; $i < 5; $i++) {
											$r[3] =~ s/^.*?$ITEM_SEPARATOR//;
										}

										push @w, $r[3];
									}
								}
							}

							&tablePeripheralDetail({ data => join($ITEM_DELIMITER, @w), slice => $arg->{slice}, leaf => $arg->{leaf}, sort => $arg->{sort}, order => $arg->{order} });
						}
					}
				}

				$c[1] = &headCookieSet({ name => "tellu_peripheral_leaf", value => $arg->{leaf} });
			}
			else {
				@r = &sendCommand({ command => "pullPeripheral", item => $arg->{node}, domain => "", param => "", option => "" });

				if(checkError({ packet => \@r }) == 0) {
					&tablePeripheralDetail({ data => $r[3], slice => $arg->{slice}, sort => $arg->{sort}, order => $arg->{order} });
				}
			}

			@r = &sendCommand({ command => "pullPeripheral", item => $arg->{node}, domain => "", param => "", option => "" });

			if(checkError({ packet => \@r }) == 0) {
				my @s = split(/$ITEM_SEPARATOR/, $r[3]);

				&tablePeripheralDetailSlice();

				if($s[5] && $s[5] ne "" && $s[6] && $s[6] ne "" && $s[7] && $s[7] ne "") {
					$t .= $s[7] . " " . $s[5] . " (" . $s[6] . ")";
				}

				if($s[27] && $s[27] ne "" && $s[27] ne "(null)") {
					$u .= $s[27];
				}
			}

			$c[0] = &headCookieSet({ name => $arg->{cookie}, value => $arg->{value} });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => &passwordFuncs({ slice => "incs", leaf => "2" }), header => $t, subheader => $u, content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
}
