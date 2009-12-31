#!/usr/bin/perl

my ($pack, $f, $line) = caller;

if($pack eq "" && $f eq "" && $line eq "") {
	print STDOUT "Content-Type: text/html" . "\r\n\r\n";

	exit(0);
}

sub machineListingFuncs {
	my ($arg) = @_;

	my $r = "";

	$r .= "function popupMachine(host, slice, width, height) {" . $CONFIG_LINEFEED;
	$r .= " window.open('machine_popup.pl?host=' +host+ '&slice=' +slice+ '', '', 'scrollbars,resizable,height=' +height+ ',width=' +width+ '');" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;

	return $r;
}

sub machineListingDisposedFuncs {
	my ($arg) = @_;

	my $r = "";

	$r .= "function popupMachine(host, slice, width, height) {" . $CONFIG_LINEFEED;
	$r .= " window.open('machine_d_popup.pl?host=' +host+ '&slice=' +slice+ '', '', 'scrollbars,resizable,height=' +height+ ',width=' +width+ '');" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;

	return $r;
}

sub machineModifyFuncs {
	my ($arg) = @_;

	my $r = "";

	$r .= "function toggleUpdateButton(param) {" . $CONFIG_LINEFEED;
	$r .= " if(document." . $arg->{form} . ".disposed.checked) {" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".submit.value = 'Dispose';" . $CONFIG_LINEFEED;
	$r .= " }" . $CONFIG_LINEFEED;
	$r .= " else {" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".submit.value = 'Update';" . $CONFIG_LINEFEED;
	$r .= " }" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;

	return $r;
}

sub machineModifyDisposedFuncs {
	my ($arg) = @_;

	my $r = "";

	$r .= "function toggleUpdateButtons(param) {" . $CONFIG_LINEFEED;
	$r .= " if(document." . $arg->{form} . ".restore.checked) {" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".submit.value = 'Restore';" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".disposed.checked = 0;" . $CONFIG_LINEFEED;
	$r .= " }" . $CONFIG_LINEFEED;
	$r .= " else if(document." . $arg->{form} . ".disposed.checked) {" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".submit.value = 'Dispose';" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".restore.checked = 0;" . $CONFIG_LINEFEED;
	$r .= " }" . $CONFIG_LINEFEED;
	$r .= " else {" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".submit.value = 'Update';" . $CONFIG_LINEFEED;
	$r .= " }" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;

	return $r;
}

1;
