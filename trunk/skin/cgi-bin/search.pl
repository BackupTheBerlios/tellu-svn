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
	if($c =~ /^admin/) {
		$t .= " from administrative items";

		&doSearch({ caller => "Histories", command => "searchHistory", search => $w });
		&doSearch({ caller => "Logs", command => "searchLog", search => $w });
		&doSearch({ caller => "Users", command => "searchUser", search => $w });
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
	elsif($c =~ /^help/) {
		$t .= " from help pages";

		&doSearch({ caller => "Help pages", command => "searchHelp", search => $w });
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

		&doSearch({ caller => "My factions", command => "searchFaction", search => $w });
		&doSearch({ caller => "My files", command => "searchFile", search => $w });
		&doSearch({ caller => "My passwords", command => "searchPassword", search => $w });
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
