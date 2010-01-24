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
	$s = $q->param('slice');

	if(!$s || $s eq "") {
		$s = "node";
	}

	if(&machineGlobal({ domain => $d, slice => $s, sort => $q->param('sort'), order => $q->param('order'), cookie => "tellu_machine_d_slice", value => $s }) == 0) {
		&machineThing({ node => $n, domain => $d, slice => $s, sort => $q->param('sort'), order => $q->param('order'), cookie => "tellu_machine_d_slice", value => $s });
	}
}
elsif($q->param('machineNode')) {
	&machineThing({ node => $q->param('machineNode'), domain => $d, slice => $s, sort => $q->param('sort'), order => $q->param('order'), cookie => "tellu_machine_d_node", value => $q->param('machineNode') });
}
elsif($q->param('machineDomain')) {
	if(!$s || $s eq "") {
		$s = "node";
	}

	if(&machineGlobal({ domain => $q->param('machineDomain'), slice => $s, sort => $q->param('sort'), order => $q->param('order'), cookie => "tellu_machine_d_domain", value => $q->param('machineDomain') }) == 0) {
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
	&tableDMachineDomainSlice();

	if(&menuDMachineDomain({ select => $d }) == 0) {
		&htmlPage({ title => $WINDOW_TITLE, script => "", header => "Disposed machines", content => $PAGE, slices => $MENU });
	}
	else {
		&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
	}
}

exit(0);



sub machineGlobal {
	my ($arg) = @_;

	my @c = ();
	my @r = ();

	my $r = 0;

	my $s = $q->param('slice');

	if(!$s || $s eq "") {
		$s = "node";
	}

	if($arg->{domain} eq "Global summary") {
		if(&menuDMachineDomain({ select => $arg->{domain} }) == 0) {
			&tableMachineBriefSlice({ system => "Summary", distro => "" });

			if($s eq "addinfo" || $s eq "repair" || $s eq "security" || $s eq "warranty") {
				@r = &sendCommand({ command => "pullDisposedMachine", item => "", domain => "", param => "node", option => "" });
			}
			else {
				@r = &sendCommand({ command => "pullDisposedMachine", item => "", domain => "", param => $s, option => "" });
			}

			if(checkError({ packet => \@r }) == 0) {
				&tableMachineBrief({ data => $r[3], slice => $s, sort => $arg->{sort}, order => $arg->{order} });
			}

			$c[0] = &headCookieSet({ name => $arg->{cookie}, value => $arg->{value} });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $arg->{domain}, script => "", header => $arg->{domain}, content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}

		$r++;
	}
	elsif($arg->{domain} eq "Global listing") {
		if(&menuDMachineDomain({ select => $arg->{domain} }) == 0) {
			&tableMachineListingSlice({ system => "Listing", distro => "" });

			if($s eq "addinfo" || $s eq "repair" || $s eq "security" || $s eq "warranty") {
				@r = &sendCommand({ command => "pullDisposedMachine", item => "", domain => "", param => "node", option => "" });
			}
			else {
				@r = &sendCommand({ command => "pullDisposedMachine", item => "", domain => "", param => $s, option => "" });
			}

			if(checkError({ packet => \@r }) == 0) {
				&tableMachineListing({ data => $r[3], slice => $s, sort => $arg->{sort}, order => $arg->{order} });
			}

			$c[0] = &headCookieSet({ name => $arg->{cookie}, value => $arg->{value} });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $arg->{domain}, script => &machineListingDisposedFuncs({ form => "modifyDisposedForm" }), header => $arg->{domain}, content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}

		$r++;
	}

	return $r;
}

sub machineThing {
	my ($arg) = @_;

	my @c = ();
	my @r = ();

	if($arg->{node} eq "Domain summary") {
		if(&menuDMachineNode({ select => $arg->{node}, domain => $arg->{domain} }) == 0) {
			&tableMachineBriefSlice({ system => "Summary", distro => "" });

			if(!$arg->{slice} || $arg->{slice} eq "") {
				$arg->{slice} = "node";
			}

			if($arg->{slice} eq "addinfo" || $arg->{slice} eq "repair" || $arg->{slice} eq "security" || $arg->{slice} eq "warranty") {
				@r = &sendCommand({ command => "pullDisposedMachine", item => "", domain => $arg->{domain}, param => "node", option => "" });
			}
			else {
				@r = &sendCommand({ command => "pullDisposedMachine", item => "", domain => $arg->{domain}, param => $arg->{slice}, option => "" });
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
		if(&menuDMachineNode({ select => $arg->{node}, domain => $arg->{domain} }) == 0) {
			&tableMachineListingSlice({ system => "Listing", distro => "" });

			if(!$arg->{slice} || $arg->{slice} eq "") {
				$arg->{slice} = "node";
			}

			if($arg->{slice} eq "addinfo" || $arg->{slice} eq "repair" || $arg->{slice} eq "security" || $arg->{slice} eq "warranty") {
				@r = &sendCommand({ command => "pullDisposedMachine", item => "", domain => $arg->{domain}, param => "node", option => "" });
			}
			else {
				@r = &sendCommand({ command => "pullDisposedMachine", item => "", domain => $arg->{domain}, param => $arg->{slice}, option => "" });
			}

			if(checkError({ packet => \@r }) == 0) {
				&tableMachineListing({ data => $r[3], slice => $arg->{slice}, sort => $arg->{sort}, order => $arg->{order} });
			}

			$c[0] = &headCookieSet({ name => $arg->{cookie}, value => $arg->{value} });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $arg->{node} . " of " . $arg->{domain}, script => &machineListingDisposedFuncs({ form => "modifyDisposedForm" }), header => $arg->{node} . " of " . $arg->{domain}, content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
	else {
		if(&menuDMachineNode({ select => $arg->{node}, domain => $arg->{domain} }) == 0) {
			my $t = "";
			my $u = "";

			if(!$arg->{slice} || $arg->{slice} eq "") {
				$arg->{slice} = "node";
			}

			if($arg->{slice} eq "addinfo" || $arg->{slice} eq "repair" || $arg->{slice} eq "security" || $arg->{slice} eq "warranty") {
				@r = &sendCommand({ command => "pullDisposedMachine", item => $arg->{node}, domain => $arg->{domain}, param => "node", option => "" });
			}
			else {
				@r = &sendCommand({ command => "pullDisposedMachine", item => $arg->{node}, domain => $arg->{domain}, param => $arg->{slice}, option => "" });
			}

			if(checkError({ packet => \@r }) == 0) {
				&tableMachineDetail({ data => $r[3], slice => $arg->{slice}, sort => $arg->{sort}, order => $arg->{order} });
			}

			@r = &sendCommand({ command => "pullDisposedMachine", item => $arg->{node}, domain => $arg->{domain}, param => "node", option => "" });

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

			$c[0] = &headCookieSet({ name => $arg->{cookie}, value => $arg->{value} });

			&htmlPage({ title => $WINDOW_TITLE . " - " . $arg->{node} . "." . $arg->{domain}, script => "", header => $arg->{node} . "." . $arg->{domain} . $t, subheader => $u, content => $PAGE, slices => $MENU, cookie => \@c });
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
}
