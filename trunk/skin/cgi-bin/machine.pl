#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "machine.lib";
require "machine.js";
require "personal.js";



&headPrepare();

my @c = ();
my @r = ();

my $d = &headCookieGet({ name => "tellu_machine_domain" });
my $n = &headCookieGet({ name => "tellu_machine_node" });
my $s = &headCookieGet({ name => "tellu_machine_slice" });
my $g = &headCookieGet({ name => "tellu_machine_leaf" });
my $m = &headCookieGet({ name => "tellu_machine_action" });

if($q->param('action')) {
	if(&menuMachineNode({ select => $n, domain => $d }) == 0) {
		my $t = "";
		my $u = "";

		@r = &sendCommand({ command => "pullMachine", item => $n, domain => $d, param => "node", option => "" });

		if(checkError({ packet => \@r }) == 0) {
			require "machine_edit.lib";

			my @s = split(/$ITEM_SEPARATOR/, $r[3]);

			&tableMachineDetailSlice({ system => $s[1], distro => $s[3] });

			if($q->param('action') eq "note") {
				&editMachineNote({ node => $n, domain => $d });
			}
			elsif($q->param('action') eq "modify") {
				&editMachineNode({ node => $n, domain => $d });
			}

			if($s[1]) {
				$t .= "&nbsp;-&nbsp;" . $s[1];
			}

			if($s[2]) {
				$t .= ",&nbsp;" . $s[2];
			}

			if($s[18] && $s[18] ne "" && $s[18] ne "(null)") {
				$u .= $s[18]
			}
		}

		$c[0] = &headCookieSet({ name => "tellu_machine_action", value => $q->param('action') });

		if($q->param('disposed') && $q->param('disposed') == 1) {
			$c[1] = &headCookieSet({ name => "tellu_machine_node", value => "" });
		}

		&htmlPage({ title => $WINDOW_TITLE . " - " . $n . "." . $d, script => &machineModifyFuncs({ form => "modifyForm" }), header => $n . "." . $d . $t, subheader => $u, content => $PAGE, slices => $MENU, cookie => \@c });
	}
	else {
		&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
	}
}
elsif($q->param('slice')) {
	if($d eq "Global summary") {
		if(&menuMachineDomain({ select => $d }) == 0) {
			&tableMachineBriefSlice({ system => "Summary", distro => "" });

			if($q->param('slice') eq "addinfo" || $q->param('slice') eq "repair" || $q->param('slice') eq "security" || $q->param('slice') eq "warranty") {
				@r = &sendCommand({ command => "pullMachine", item => "", domain => "", param => "node", option => "" });
			}
			else {
				@r = &sendCommand({ command => "pullMachine", item => "", domain => "", param => $q->param('slice'), option => "" });
			}

			if(checkError({ packet => \@r }) == 0) {
				&tableMachineBrief({ data => $r[3], slice => $q->param('slice'), sort => $q->param('sort'), order => $q->param('order') });
			}

			$c[0] = &headCookieSet({ name => "tellu_machine_slice", value => $q->param('slice') });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $d, script => "", header => $d, content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
	elsif($d eq "Global listing") {
		if(&menuMachineDomain({ select => $d }) == 0) {
			&tableMachineListingSlice({ system => "Listing", distro => "" });

			if($q->param('slice') eq "addinfo" || $q->param('slice') eq "repair" || $q->param('slice') eq "security" || $q->param('slice') eq "warranty") {
				@r = &sendCommand({ command => "pullMachine", item => "", domain => "", param => "node", option => "" });
			}
			else {
				@r = &sendCommand({ command => "pullMachine", item => "", domain => "", param => $q->param('slice'), option => "" });
			}

			if(checkError({ packet => \@r }) == 0) {
				&tableMachineListing({ data => $r[3], slice => $q->param('slice'), sort => $q->param('sort'), order => $q->param('order') });
			}

			$c[0] = &headCookieSet({ name => "tellu_machine_slice", value => $q->param('slice') });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $d, script => &machineListingFuncs(), header => $d, content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
	else {
		my $f = $g;

		if($q->param('leaf') && $q->param('leaf') ne "") {
			$f = $q->param('leaf');
		}

		&machineThing({ node => $n, domain => $d, slice => $q->param('slice'), leaf => $f, sort => $q->param('sort'), order => $q->param('order'), cookie => "tellu_machine_slice", value => $q->param('slice'), key => $q->param('key') });
	}
}
elsif($q->param('machineNode')) {
	&machineThing({ node => $q->param('machineNode'), domain => $d, slice => $s, leaf => $g, sort => $q->param('sort'), order => $q->param('order'), cookie => "tellu_machine_node", value => $q->param('machineNode'), key => $q->param('key') });
}
elsif($q->param('machineDomain')) {
	if($q->param('machineDomain') eq "Global summary") {
		if(&menuMachineDomain({ select => $d }) == 0) {
			&tableMachineBriefSlice({ system => "Summary", distro => "" });

			if(!$s || $s eq "") {
				$s = "node";
			}

			if($s eq "addinfo" || $s eq "repair" || $s eq "security" || $s eq "warranty") {
				@r = &sendCommand({ command => "pullMachine", item => "", domain => "", param => "node", option => "" });
			}
			else {
				@r = &sendCommand({ command => "pullMachine", item => "", domain => "", param => $s, option => "" });
			}

			if(checkError({ packet => \@r }) == 0) {
				&tableMachineBrief({ data => $r[3], slice => $s, sort => $q->param('sort'), order => $q->param('order') });
			}

			$c[0] = &headCookieSet({ name => "tellu_machine_domain", value => $q->param('machineDomain') });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $q->param('machineDomain'), script => "", header => $q->param('machineDomain'), content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
	elsif($q->param('machineDomain') eq "Global listing") {
		if(&menuMachineDomain({ select => $d }) == 0) {
			&tableMachineListingSlice({ system => "Listing", distro => "" });

			if(!$s || $s eq "") {
				$s = "node";
			}

			if($s eq "addinfo" || $s eq "repair" || $s eq "security" || $s eq "warranty") {
				@r = &sendCommand({ command => "pullMachine", item => "", domain => "", param => "node", option => "" });
			}
			else {
				@r = &sendCommand({ command => "pullMachine", item => "", domain => "", param => $s, option => "" });
			}

			if(checkError({ packet => \@r }) == 0) {
				&tableMachineListing({ data => $r[3], slice => $s, sort => $q->param('sort'), order => $q->param('order') });
			}

			$c[0] = &headCookieSet({ name => "tellu_machine_domain", value => $q->param('machineDomain') });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $q->param('machineDomain'), script => &machineListingFuncs(), header => $q->param('machineDomain'), content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
	else {
		&tableMachineDomainSlice();

		if(&menuMachineNode({ select => $n, domain => $q->param('machineDomain') }) == 0) {
			$c[0] = &headCookieSet({ name => "tellu_machine_domain", value => $q->param('machineDomain') });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $q->param('machineDomain'), script => "", header => $q->param('machineDomain'), content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
}
else {
	&tableMachineDomainSlice();

	if(&menuMachineDomain({ select => $d }) == 0) {
		&htmlPage({ title => $WINDOW_TITLE, script => "", header => "Active machines", content => $PAGE, slices => $MENU });
	}
	else {
		&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
	}
}

exit(0);



sub machineThing {
	my ($arg) = @_;

	my @c = ();
	my @r = ();

	if($arg->{node} eq "Domain summary") {
		if(&menuMachineNode({ select => $arg->{node}, domain => $arg->{domain} }) == 0) {
			&tableMachineBriefSlice({ system => "Summary", distro => "" });

			if(!$arg->{slice} || $arg->{slice} eq "") {
				$arg->{slice} = "node";
			}

			if($arg->{slice} eq "addinfo" || $arg->{slice} eq "repair" || $arg->{slice} eq "security" || $arg->{slice} eq "warranty") {
				@r = &sendCommand({ command => "pullMachine", item => "", domain => $arg->{domain}, param => "node", option => "" });
			}
			else {
				@r = &sendCommand({ command => "pullMachine", item => "", domain => $arg->{domain}, param => $arg->{slice}, option => "" });
			}

			if(checkError({ packet => \@r }) == 0) {
				&tableMachineBrief({ data => $r[3], slice => $arg->{slice}, sort => $arg->{sort}, order => $arg->{order} });
			}

			$c[0] = &headCookieSet({ name => $arg->{cookie}, value => $arg->{value} });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $arg->{node} . " of " . $arg->{domain}, script => "", header => $arg->{node} . " of " . $arg->{domain}, content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
	elsif($arg->{node} eq "Domain listing") {
		if(&menuMachineNode({ select => $arg->{node}, domain => $arg->{domain} }) == 0) {
			&tableMachineListingSlice({ system => "Listing", distro => "" });

			if(!$arg->{slice} || $arg->{slice} eq "") {
				$arg->{slice} = "node";
			}

			if($arg->{slice} eq "addinfo" || $arg->{slice} eq "repair" || $arg->{slice} eq "security" || $arg->{slice} eq "warranty") {
				@r = &sendCommand({ command => "pullMachine", item => "", domain => $arg->{domain}, param => "node", option => "" });
			}
			else {
				@r = &sendCommand({ command => "pullMachine", item => "", domain => $arg->{domain}, param => $arg->{slice}, option => "" });
			}

			if(checkError({ packet => \@r }) == 0) {
				&tableMachineListing({ data => $r[3], slice => $arg->{slice}, sort => $arg->{sort}, order => $arg->{order} });
			}

			$c[0] = &headCookieSet({ name => $arg->{cookie}, value => $arg->{value} });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $arg->{node} . " of " . $arg->{domain}, script => &machineListingFuncs(), header => $arg->{node} . " of " . $arg->{domain}, content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
	else {
		if(&menuMachineNode({ select => $arg->{node}, domain => $arg->{domain} }) == 0) {
			if(!$arg->{slice} || $arg->{slice} eq "") {
				$arg->{slice} = "node";
			}

			my $t = "";
			my $u = "";

			if($arg->{slice} eq "addinfo" || $arg->{slice} eq "repair" || $arg->{slice} eq "security" || $arg->{slice} eq "warranty") {
				@r = &sendCommand({ command => "pullMachine", item => $arg->{node}, domain => $arg->{domain}, param => "node", option => "" });

				if(checkError({ packet => \@r }) == 0) {
					&tableMachineDetail({ data => $r[3], slice => $arg->{slice}, sort => $arg->{sort}, order => $arg->{order} });
				}
			}
			elsif($arg->{slice} eq "incs") {
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
					@r = &sendCommand({ command => "pullMachine", item => $arg->{node}, domain => $arg->{domain}, param => "node", option => "" });

					if(checkError({ packet => \@r }) == 0) {
						my @s = split(/$ITEM_SEPARATOR/, $r[3]);

						@r = &sendCommand({ command => "attachedFile", item => "", domain => "", param => $s[0], option => "machine" });

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

							&tableMachineDetail({ data => join($ITEM_DELIMITER, @w), slice => $arg->{slice}, leaf => $arg->{leaf}, sort => $arg->{sort}, order => $arg->{order} });
						}
					}
				}
				elsif($arg->{leaf} == 2) {
					my $k = "";

					if($arg->{key} && $arg->{key} ne "") {
						$k = $arg->{key};
					}

					@r = &sendCommand({ command => "pullMachine", item => $arg->{node}, domain => $arg->{domain}, param => "node", option => "" });

					if(checkError({ packet => \@r }) == 0) {
						my @s = split(/$ITEM_SEPARATOR/, $r[3]);

						@r = &sendCommand({ command => "attachedPassword", item => "", domain => "", param => $s[0], option => "machine" });

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

							&tableMachineDetail({ data => join($ITEM_DELIMITER, @w), slice => $arg->{slice}, leaf => $arg->{leaf}, sort => $arg->{sort}, order => $arg->{order}, key => $k });
						}
					}
				}
				elsif($arg->{leaf} == 3) {
					@r = &sendCommand({ command => "pullMachine", item => $arg->{node}, domain => $arg->{domain}, param => "node", option => "" });

					if(checkError({ packet => \@r }) == 0) {
						my @s = split(/$ITEM_SEPARATOR/, $r[3]);

						@r = &sendCommand({ command => "attachedDevice", item => "", domain => "", param => $s[0], option => "machine" });

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

							&tableMachineDetail({ data => join($ITEM_DELIMITER, @w), slice => $arg->{slice}, leaf => $arg->{leaf}, sort => $arg->{sort}, order => $arg->{order} });
						}
					}
				}
				elsif($arg->{leaf} == 4) {
					@r = &sendCommand({ command => "pullMachine", item => $arg->{node}, domain => $arg->{domain}, param => "node", option => "" });

					if(checkError({ packet => \@r }) == 0) {
						my @s = split(/$ITEM_SEPARATOR/, $r[3]);

						@r = &sendCommand({ command => "attachedPeripheral", item => "", domain => "", param => $s[0], option => "machine" });

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

							&tableMachineDetail({ data => join($ITEM_DELIMITER, @w), slice => $arg->{slice}, leaf => $arg->{leaf}, sort => $arg->{sort}, order => $arg->{order} });
						}
					}
				}
				elsif($arg->{leaf} == 5) {
					@r = &sendCommand({ command => "pullMachine", item => $arg->{node}, domain => $arg->{domain}, param => "node", option => "" });

					if(checkError({ packet => \@r }) == 0) {
						my @s = split(/$ITEM_SEPARATOR/, $r[3]);

						@r = &sendCommand({ command => "attachedProvider", item => "", domain => "", param => $s[0], option => "machine" });

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

							&tableMachineDetail({ data => join($ITEM_DELIMITER, @w), slice => $arg->{slice}, leaf => $arg->{leaf}, sort => $arg->{sort}, order => $arg->{order} });
						}
					}
				}

				$c[1] = &headCookieSet({ name => "tellu_machine_leaf", value => $arg->{leaf} });
			}
			else {
				@r = &sendCommand({ command => "pullMachine", item => $arg->{node}, domain => $arg->{domain}, param => $arg->{slice}, option => "" });

				if(checkError({ packet => \@r }) == 0) {
					&tableMachineDetail({ data => $r[3], slice => $arg->{slice}, sort => $arg->{sort}, order => $arg->{order} });
				}
			}

			@r = &sendCommand({ command => "pullMachine", item => $arg->{node}, domain => $arg->{domain}, param => "node", option => "" });

			if(checkError({ packet => \@r }) == 0) {
				my @s = split(/$ITEM_SEPARATOR/, $r[3]);

				&tableMachineDetailSlice({ system => $s[1], distro => $s[3] });

				if($s[1]) {
					$t .= "&nbsp;-&nbsp;" . $s[1];
				}

				if($s[2]) {
					$t .= ",&nbsp;" . $s[2];
				}

				if($s[18] && $s[18] ne "" && $s[18] ne "(null)") {
					$u .= $s[18]
				}
			}

			$c[0] = &headCookieSet({ name => $arg->{cookie}, value => $arg->{value} });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $arg->{node} . "." . $arg->{domain}, script => &passwordFuncs({ slice => "passwds" }), header => $arg->{node} . "." . $arg->{domain} . $t, subheader => $u, content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
}
