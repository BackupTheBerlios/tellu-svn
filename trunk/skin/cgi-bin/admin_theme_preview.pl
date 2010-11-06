#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";
require "machine.lib";



&headPrepare();

my $s = "1";
my $o = "a";
my $h = &prefsTheme();

if($q->param('sort') && $q->param('sort') ne "") {
	$s = $q->param('sort');
}

if($q->param('order') && $q->param('order') ne "") {
	$o = $q->param('order');
}

if($q->param('theme') && $q->param('theme') ne "") {
	$h = $q->param('theme');
}

my $t = $h;

$t =~ s/_/ /go;
$t .= " theme";

$PAGE .= "<p>Well, what do you think? This is how " . $t . " looks like. If you like to use this theme, press <i>Set theme</i> button in main window.</p>";

my $j = "Breakfast,Lunch,Dinner,Supper";
my $k = "0,0,0,0";

my @j = ();
my $i = 0;

$j[$i] = join($ITEM_SEPARATOR, $i, "Baked beans", "Bacon club", "Beef Wellington", "Beef lasagne"); $i++;
$j[$i] = join($ITEM_SEPARATOR, $i, "Bread", "Chips", "Bread and butter pudding", "Breaded plaice"); $i++;
$j[$i] = join($ITEM_SEPARATOR, $i, "Fried bacon", "Jacket potatoes", "Brussels sprouts with chestnuts", "Chicken curry"); $i++;
$j[$i] = join($ITEM_SEPARATOR, $i, "Kippers", "Meatballs", "Carrot Custard", "Lamb shank"); $i++;
$j[$i] = join($ITEM_SEPARATOR, $i, "Oatcakes", "Omelettes", "Demitasse", "Nut roast"); $i++;
$j[$i] = join($ITEM_SEPARATOR, $i, "Pancakes", "Roasted chicken", "Roast sirloin of beef", "Sausage and eggs"); $i++;
$j[$i] = join($ITEM_SEPARATOR, $i, "Sausages", "Sausage sandwich", "Sliced cucumbers", "Spaghetti Bolognaise"); $i++;
$j[$i] = join($ITEM_SEPARATOR, $i, "Toast", "Sneaky pie", "Whitebait", "Vegetable lasagne"); $i++;
$j[$i] = join($ITEM_SEPARATOR, $i, "Waffles", "Steak ciabatta", "Yorkshire pudding", "Wholetail scampi"); $i++;

&tableMachineDetails({ slice => "", sort => $s, order=> $o, data => join($ITEM_DELIMITER, @j), title => $j, modifier => $k });
&tablePreviewSlice();

&htmlPage({ template => "preview", theme => $h, title => $WINDOW_TITLE . " - " . $t, script => "", header => $t, content => $PAGE, slices => $MENU });

exit(0);



sub tablePreviewSlice {
	my ($arg) = @_;

	$MENU .= "<table class=\"logo\" cellpadding=\"0\" cellspacing=\"0\">";
	$MENU .= "<tr class=\"middle\">";
	$MENU .= "<td class=\"c3\" width=\"1\"><img alt=\"\" id=\"logo\" width=\"32\" height=\"32\" src=\"/pics/admin/preview.png\"></td>";
	$MENU .= "<td class=\"c3\">Preview</td>";
	$MENU .= "</tr>";
	$MENU .= "</table>";

	$MENU .= "<ul id=\"slices\">";
	$MENU .= "</ul>";
}
