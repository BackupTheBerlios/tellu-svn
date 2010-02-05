#!/usr/bin/perl

my ($pack, $f, $line) = caller;

if($pack eq "" && $f eq "" && $line eq "") {
	print STDOUT "Content-Type: text/html" . "\r\n\r\n";

	exit(0);
}

sub adminModifyFuncs {
	my ($arg) = @_;

	my $r = "";

	$r .= "function toggleUpdateButton(param) {" . $CONFIG_LINEFEED;
	$r .= " if(document." . $arg->{form} . ".disposed.checked) {" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".submit2.value = 'Dispose';" . $CONFIG_LINEFEED;
	$r .= " }" . $CONFIG_LINEFEED;
	$r .= " else {" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".submit2.value = 'Update';" . $CONFIG_LINEFEED;
	$r .= " }" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;
	$r .= "function togglePrivilegeName(param1, param2) {" . $CONFIG_LINEFEED;
	$r .= " var k = document.getElementsByName(param2);" . $CONFIG_LINEFEED;
	$r .= " var j = k.length;" . $CONFIG_LINEFEED;
	$r .= " for(var i = 0; i < j; i++) {" . $CONFIG_LINEFEED;
	$r .= "  if(k[i].checked) {" . $CONFIG_LINEFEED;
	$r .= "   if(k[i].value == 2) {" . $CONFIG_LINEFEED;
	$r .= "    document.getElementById(param1).innerHTML = 'Read';" . $CONFIG_LINEFEED;
	$r .= "   }" . $CONFIG_LINEFEED;
	$r .= "   else if(k[i].value == 4) {" . $CONFIG_LINEFEED;
	$r .= "    document.getElementById(param1).innerHTML = 'Read/Modify';" . $CONFIG_LINEFEED;
	$r .= "   }" . $CONFIG_LINEFEED;
	$r .= "   else if(k[i].value == 8) {" . $CONFIG_LINEFEED;
	$r .= "    document.getElementById(param1).innerHTML = 'Read/Modify/Delete';" . $CONFIG_LINEFEED;
	$r .= "   }" . $CONFIG_LINEFEED;
	$r .= "   else if(k[i].value == 16) {" . $CONFIG_LINEFEED;
	$r .= "    document.getElementById(param1).innerHTML = 'Read/Modify/Delete/Restore';" . $CONFIG_LINEFEED;
	$r .= "   }" . $CONFIG_LINEFEED;
	$r .= "   else {" . $CONFIG_LINEFEED;
	$r .= "    document.getElementById(param1).innerHTML = 'No access';" . $CONFIG_LINEFEED;
	$r .= "   }" . $CONFIG_LINEFEED;
	$r .= "  }" . $CONFIG_LINEFEED;
	$r .= " }" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;

	return $r;
}

1;
