#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "machine.lib";
require "machine.js";



&headPrepare();

my @c = ();
my @r = ();

my $d = &headCookieGet({ name => "tellu_machine_d_domain" });
my $n = &headCookieGet({ name => "tellu_machine_d_node" });
my $s = &headCookieGet({ name => "tellu_machine_d_slice" });
my $m = &headCookieGet({ name => "tellu_machine_d_action" });

if($q->param('action')) {
	#
	# Create machine edit form and edit requested machine data
	#

	if(&menuDMachineNode({ select => $n, domain => $d }) == 0) {
		my $t = "";
		my $u = "";
		@r = &sendCommand({ command => "pullDisposedMachine", item => $n, domain => $d, param => "node", option => "" });

		if(checkError({ packet => \@r }) == 0) {
			require "machine_d_edit.lib";

			my @s = split(/$ITEM_SEPARATOR/, $r[3]);

			&tableDMachineDetailSlice({ system => $s[1], distro => $s[3] });

			if($q->param('action') eq "note") {
				&editDisposedMachineNote({ node => $n, domain => $d });
			}
			elsif($q->param('action') eq "modify") {
				&editDisposedMachineNode({ node => $n, domain => $d });
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

		$c[0] = &headCookieSet({ name => "tellu_machine_d_action", value => $q->param('action') });

		if($q->param('disposed') && $q->param('disposed') == 2) {
			$c[1] = &headCookieSet({ name => "tellu_machine_d_node", value => "" });
		}

		&htmlPage({ title => $WINDOW_TITLE . " - " . $n . "." . $d, script => &machineModifyDisposedFuncs({ form => "modifyDisposedForm" }), header => $n . "." . $d . $t, subheader => $u, content => $PAGE, slices => $MENU, cookie => \@c });
	}
	else {
		&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
	}
}
elsif($q->param('slice')) {
	#
	# Domain summary and display requested brief data
	#

	if($d eq "Global summary") {
		if(&menuDMachineDomain({ select => $d }) == 0) {
			&tableMachineBriefSlice({ system => "Summary", distro => "" });

			if($q->param('slice') eq "addinfo" || $q->param('slice') eq "repair" || $q->param('slice') eq "security" || $q->param('slice') eq "warranty") {
				@r = &sendCommand({ command => "pullDisposedMachine", item => "", domain => "", param => "node", option => "" });
			}
			else {
				@r = &sendCommand({ command => "pullDisposedMachine", item => "", domain => "", param => $q->param('slice'), option => "" });
			}

			if(checkError({ packet => \@r }) == 0) {
				&tableMachineBrief({ data => $r[3], slice => $q->param('slice'), sort => $q->param('sort'), order => $q->param('order') });
			}

			$c[0] = &headCookieSet({ name => "tellu_machine_d_slice", value => $q->param('slice') });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $d, script => "", header => $d, content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
	elsif($d eq "Global listing") {
		if(&menuDMachineDomain({ select => $d }) == 0) {
			&tableMachineListingSlice({ system => "Listing", distro => "" });

			if($q->param('slice') eq "addinfo" || $q->param('slice') eq "repair" || $q->param('slice') eq "security" || $q->param('slice') eq "warranty") {
				@r = &sendCommand({ command => "pullDisposedMachine", item => "", domain => "", param => "node", option => "" });
			}
			else {
				@r = &sendCommand({ command => "pullDisposedMachine", item => "", domain => "", param => $q->param('slice'), option => "" });
			}

			if(checkError({ packet => \@r }) == 0) {
				&tableMachineListing({ data => $r[3], slice => $q->param('slice'), sort => $q->param('sort'), order => $q->param('order') });
			}

			$c[0] = &headCookieSet({ name => "tellu_machine_d_slice", value => $q->param('slice') });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $d, script => &machineListingDisposedFuncs(), header => $d, content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
	else {
		#
		# Create machine selection menu and display requested machine data
		#

		if($n eq "Domain summary") {
			if(&menuDMachineNode({ select => $n, domain => $d }) == 0) {
				&tableMachineBriefSlice({ system => "Summary", distro => "" });

				if($q->param('slice') eq "addinfo" || $q->param('slice') eq "repair" || $q->param('slice') eq "security" || $q->param('slice') eq "warranty") {
					@r = &sendCommand({ command => "pullDisposedMachine", item => "", domain => $d, param => "node", option => "" });
				}
				else {
					@r = &sendCommand({ command => "pullDisposedMachine", item => "", domain => $d, param => $q->param('slice'), option => "" });
				}

				if(checkError({ packet => \@r }) == 0) {
					&tableMachineBrief({ data => $r[3], slice => $q->param('slice'), sort => $q->param('sort'), order => $q->param('order') });
				}

				$c[0] = &headCookieSet({ name => "tellu_machine_d_slice", value => $q->param('slice') });

				&htmlPage({ title => $WINDOW_TITLE . " - " . $n . " of " . $d, script => "", header => $n . " of " . $d, content => $PAGE, slices => $MENU, cookie => \@c });
			}
			else {
				&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
			}
		}
		elsif($n eq "Domain listing") {
			if(&menuDMachineNode({ select => $n, domain => $d }) == 0) {
				&tableMachineListingSlice({ system => "Listing", distro => "" });

				if($q->param('slice') eq "addinfo" || $q->param('slice') eq "repair" || $q->param('slice') eq "security" || $q->param('slice') eq "warranty") {
					@r = &sendCommand({ command => "pullDisposedMachine", item => "", domain => $d, param => "node", option => "" });
				}
				else {
					@r = &sendCommand({ command => "pullDisposedMachine", item => "", domain => $d, param => $q->param('slice'), option => "" });
				}

				if(checkError({ packet => \@r }) == 0) {
					&tableMachineListing({ data => $r[3], slice => $q->param('slice'), sort => $q->param('sort'), order => $q->param('order') });
				}

				$c[0] = &headCookieSet({ name => "tellu_machine_d_slice", value => $q->param('slice') });

				&htmlPage({ title => $WINDOW_TITLE . " - " . $n . " of " . $d, script => &machineListingDisposedFuncs(), header => $n . " of " . $d, content => $PAGE, slices => $MENU, cookie => \@c });
			}
			else {
				&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
			}
		}
		else {
			#
			# Create machine selection menu and display requested machine data
			#

			if(&menuDMachineNode({ select => $n, domain => $d }) == 0) {
				my $t = "";
				my $u = "";

				if($q->param('slice') eq "addinfo" || $q->param('slice') eq "repair" || $q->param('slice') eq "security" || $q->param('slice') eq "warranty") {
					@r = &sendCommand({ command => "pullDisposedMachine", item => $n, domain => $d, param => "node", option => "" });
				}
				else {
					@r = &sendCommand({ command => "pullDisposedMachine", item => $n, domain => $d, param => $q->param('slice'), option => "" });
				}

				if(checkError({ packet => \@r }) == 0) {
					&tableMachineDetail({ data => $r[3], slice => $q->param('slice'), sort => $q->param('sort'), order => $q->param('order') });
				}

				@r = &sendCommand({ command => "pullDisposedMachine", item => $n, domain => $d, param => "node", option => "" });

				if(checkError({ packet => \@r }) == 0) {
					my @s = split(/$ITEM_SEPARATOR/, $r[3]);

					&tableDMachineDetailSlice({ system => $s[1], distro => $s[3] });

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

				$c[0] = &headCookieSet({ name => "tellu_machine_d_slice", value => $q->param('slice') });

				&htmlPage({ title => $WINDOW_TITLE . " - " . $n . "." . $d, script => "", header => $n . "." . $d . $t, subheader => $u, content => $PAGE, slices => $MENU, cookie => \@c });
			}
			else {
				&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
			}
		}
	}
}
elsif($q->param('machineNode')) {
	#
	# Create machine selection menu and display initial machine data
	#

	if($q->param('machineNode') eq "Domain summary") {
		if(&menuDMachineNode({ select => $q->param('machineNode'), domain => $d }) == 0) {
			&tableMachineBriefSlice({ system => "Summary", distro => "" });

			if(!$s || $s eq "") {
				$s = "node";
			}

			if($s eq "addinfo" || $s eq "repair" || $s eq "security" || $s eq "warranty") {
				@r = &sendCommand({ command => "pullDisposedMachine", item => "", domain => $d, param => "node", option => "" });
			}
			else {
				@r = &sendCommand({ command => "pullDisposedMachine", item => "", domain => $d, param => $s, option => "" });
			}

			if(checkError({ packet => \@r }) == 0) {
				&tableMachineBrief({ data => $r[3], slice => $s, sort => $q->param('sort'), order => $q->param('order') });
			}

			$c[0] = &headCookieSet({ name => "tellu_machine_d_node", value => $q->param('machineNode') });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $q->param('machineNode') . " of " . $d, script => "", header => $q->param('machineNode') . " of " . $d, content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
	elsif($q->param('machineNode') eq "Domain listing") {
		if(&menuDMachineNode({ select => $q->param('machineNode'), domain => $d }) == 0) {
			&tableMachineListingSlice({ system => "Listing", distro => "" });

			if(!$s || $s eq "") {
				$s = "node";
			}

			if($s eq "addinfo" || $s eq "repair" || $s eq "security" || $s eq "warranty") {
				@r = &sendCommand({ command => "pullDisposedMachine", item => "", domain => $d, param => "node", option => "" });
			}
			else {
				@r = &sendCommand({ command => "pullDisposedMachine", item => "", domain => $d, param => $s, option => "" });
			}

			if(checkError({ packet => \@r }) == 0) {
				&tableMachineListing({ data => $r[3], slice => $s, sort => $q->param('sort'), order => $q->param('order') });
			}

			$c[0] = &headCookieSet({ name => "tellu_machine_d_node", value => $q->param('machineNode') });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $q->param('machineNode') . " of " . $d, script => &machineListingDisposedFuncs(), header => $q->param('machineNode') . " of " . $d, content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
	else {
		if(&menuDMachineNode({ select => $q->param('machineNode'), domain => $d }) == 0) {
			if(!$s || $s eq "") {
				$s = "node";
			}

			my $t = "";
			my $u = "";

			if($s eq "addinfo" || $s eq "repair" || $s eq "security" || $s eq "warranty") {
				@r = &sendCommand({ command => "pullDisposedMachine", item => $q->param('machineNode'), domain => $d, param => "node", option => "" });
			}
			else {
				@r = &sendCommand({ command => "pullDisposedMachine", item => $q->param('machineNode'), domain => $d, param => $s, option => "" });
			}

			if(checkError({ packet => \@r }) == 0) {
				&tableMachineDetail({ data => $r[3], slice => $s, sort => $q->param('sort'), order => $q->param('order') });
			}

			@r = &sendCommand({ command => "pullDisposedMachine", item => $q->param('machineNode'), domain => $d, param => "node", option => "" });

			if(checkError({ packet => \@r }) == 0) {
				my @s = split(/$ITEM_SEPARATOR/, $r[3]);

				&tableDMachineDetailSlice({ system => $s[1], distro => $s[3] });

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

			$c[0] = &headCookieSet({ name => "tellu_machine_d_node", value => $q->param('machineNode') });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $q->param('machineNode') . "." . $d, script => "", header => $q->param('machineNode') . "." . $d . $t, subheader => $u, content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
}
elsif($q->param('machineDomain')) {
	#
	# Domain summary and display initial brief data
	#

	if($q->param('machineDomain') eq "Global summary") {
		if(&menuDMachineDomain({ select => $d }) == 0) {
			&tableMachineBriefSlice({ system => "Summary", distro => "" });

			if(!$s || $s eq "") {
				$s = "node";
			}

			if($s eq "addinfo" || $s eq "repair" || $s eq "security" || $s eq "warranty") {
				@r = &sendCommand({ command => "pullDisposedMachine", item => "", domain => "", param => "node", option => "" });
			}
			else {
				@r = &sendCommand({ command => "pullDisposedMachine", item => "", domain => "", param => $s, option => "" });
			}

			if(checkError({ packet => \@r }) == 0) {
				&tableMachineBrief({ data => $r[3], slice => $s, sort => $q->param('sort'), order => $q->param('order') });
			}

			$c[0] = &headCookieSet({ name => "tellu_machine_d_domain", value => $q->param('machineDomain') });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $q->param('machineDomain'), script => "", header => $q->param('machineDomain'), content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
	elsif($q->param('machineDomain') eq "Global listing") {
		if(&menuDMachineDomain({ select => $d }) == 0) {
			&tableMachineListingSlice({ system => "Listing", distro => "" });

			if(!$s || $s eq "") {
				$s = "node";
			}

			if($s eq "addinfo" || $s eq "repair" || $s eq "security" || $s eq "warranty") {
				@r = &sendCommand({ command => "pullDisposedMachine", item => "", domain => "", param => "node", option => "" });
			}
			else {
				@r = &sendCommand({ command => "pullDisposedMachine", item => "", domain => "", param => $s, option => "" });
			}

			if(checkError({ packet => \@r }) == 0) {
				&tableMachineListing({ data => $r[3], slice => $s, sort => $q->param('sort'), order => $q->param('order') });
			}

			$c[0] = &headCookieSet({ name => "tellu_machine_d_domain", value => $q->param('machineDomain') });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $q->param('machineDomain'), script => &machineListingDisposedFuncs(), header => $q->param('machineDomain'), content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
	else {
		#
		# Create initial machine selection menu
		#

		&tableDMachineDomainSlice();

		if(&menuDMachineNode({ select => $n, domain => $q->param('machineDomain') }) == 0) {
			$c[0] = &headCookieSet({ name => "tellu_machine_d_domain", value => $q->param('machineDomain') });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $q->param('machineDomain'), script => "", header => $q->param('machineDomain'), content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
}
else {
	#
	# Create initial domain selection menu
	#

	&tableDMachineDomainSlice();

	if(&menuDMachineDomain({ select => $d }) == 0) {
		&htmlPage({ title => $WINDOW_TITLE, script => "", header => "Disposed machines", content => $PAGE, slices => $MENU });
	}
	else {
		&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
	}
}

exit(0);
