#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";

require "search.lib";



&headPrepare();
&tableSearchSlice();

my @c = ();

my $c = &headCookieGet({ name => "tellu_search_caller" });
my $w = &headCookieGet({ name => "tellu_search_this" });

if($q->param('caller') && $q->param('caller') ne "") {
	$c = $q->param('caller');
}
if($q->param('this') && $q->param('this') ne "") {
	$w = $q->param('this');
}

$PAGE .= &htmlFormBegin({ name => "searchForm", action => $SELF, enctype => "application/x-www-form-urlencoded", method => "post" });

if($w && $w ne "") {
	$PAGE .= &htmlInputText({ name => "this", value => $w });
}
else {
	$PAGE .= &htmlInputText({ name => "this", value => "" });
}

$PAGE .= "&nbsp;";
$PAGE .= &htmlButtonSubmit({ name => "submit", value => "Search >>" });

$PAGE .= &htmlFormEnd();
$PAGE .= "<p>&nbsp;</p>";

my $t = "Search";

if($c && $c ne "") {
	if($c !~ /^admin/ && $c !~ /^device_d/ && $c !~ /^device_c|^device/ && $c !~ /^faction/ && $c !~ /^machine_d/ && $c !~ /^machine_c|^machine/ && $c !~ /^peripheral_d/ && $c !~ /^peripheral_c|^peripheral/ && $c !~ /^personal/ && $c !~ /^service_d/ && $c !~ /^service_c|^service/) {
		$c = &headCookieGet({ name => "tellu_search_caller" });
	}

	if($c =~ /^admin/) {
		my @r = &sendCommand({ command => "isUserAdmin", item => "", domain => "", param => "", option => "" });

		if(checkError({ packet => \@r }) == 0) {
			$t .= " from administrative items";

			if($r[3] && $r[3] == 64) {
				&doSearch({ caller => "Histories", command => "searchHistory", search => $w });
				&doSearch({ caller => "Logs", command => "searchLog", search => $w });
			}
			else {
				$PAGE .= "<p>Permission denied: please contact your system administrator or help desk if you need to have an access to this resource.</p>";
			}
		}
		else {
			&htmlPage({ title => $WINDOW_TITLE . " - " . $SESSION_ERR, script => "", header => $SESSION_ERR, content => $PAGE, slices => $MENU });
		}
	}
	elsif($c =~ /^device_d/) {
		$t .= " from disposed devices";

		&doSearch({ disposed => 1, caller => "Disposed devices", command => "searchDevice", search => $w });
	}
	elsif($c =~ /^device_c|^device/) {
		$t .= " from devices";

		&doSearch({ caller => "Devices", command => "searchDevice", search => $w });
	}
	elsif($c =~ /^faction/) {
		$t .= " from factions";

		&doSearch({ caller => "Factions", command => "searchFaction", search => $w });
	}
	elsif($c =~ /^machine_d/) {
		$t .= " from disposed machines";

		&doSearch({ disposed => 1, caller => "Disposed machines", command => "searchDisposedMachine", search => $w });
	}
	elsif($c =~ /^machine_c|^machine/) {
		$t .= " from machines";

		&doSearch({ caller => "Machines", command => "searchMachine", search => $w });
	}
	elsif($c =~ /^peripheral_d/) {
		$t .= " from disposed peripherals";

		&doSearch({ disposed => 1, caller => "Disposed peripherals", command => "searchPeripheral", search => $w });
	}
	elsif($c =~ /^peripheral_c|^peripheral/) {
		$t .= " from peripherals";

		&doSearch({ caller => "Peripherals", command => "searchPeripheral", search => $w });
	}
	elsif($c =~ /^personal/) {
		$t .= " from personal items";

		my $k = "";

		if($q->param('key') && $q->param('key') ne "") {
			$k = $q->param('key');
		}

		&doSearch({ caller => "My factions", command => "searchFaction", search => $w });
		&doSearch({ caller => "My files", command => "searchFile", search => $w });
		&doSearch({ caller => "My passwords", command => "searchPassword", search => $w, key => $k });
	}
	elsif($c =~ /^service_d/) {
		$t .= " from disposed services";

		&doSearch({ disposed => 1, caller => "Disposed services", command => "searchProvider", search => $w });
	}
	elsif($c =~ /^service_c|^service/) {
		$t .= " from services";

		&doSearch({ caller => "Services", command => "searchProvider", search => $w });
	}
}

$c[0] = &headCookieSet({ name => "tellu_search_caller", value => $c });
$c[1] = &headCookieSet({ name => "tellu_search_this", value => $w });

&htmlPage({ title => $WINDOW_TITLE . " - " . $t, script => $SCRIPT, header => $t, content => $PAGE, slices => $MENU, cookie => \@c });

exit(0);
