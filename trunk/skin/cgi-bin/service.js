#!/usr/bin/perl

my ($pack, $f, $line) = caller;

if($pack eq "" && $f eq "" && $line eq "") {
	print STDOUT "Content-Type: text/html" . "\r\n\r\n";

	exit(0);
}

sub serviceListingFuncs {
	my ($arg) = @_;

	my $r = "";

	$r .= "function popupProvider(ser, slice, width, height) {" . $CONFIG_LINEFEED;
	$r .= " window.open('service_popup.pl?ser=' +ser+ '&slice=' +slice+ '', '', 'scrollbars,resizable,height=' +height+ ',width=' +width+ '');" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;

	return $r;
}

sub serviceListingDisposedFuncs {
	my ($arg) = @_;

	my $r = "";

	$r .= "function popupProvider(ser, slice, width, height) {" . $CONFIG_LINEFEED;
	$r .= " window.open('service_d_popup.pl?ser=' +ser+ '&slice=' +slice+ '', '', 'scrollbars,resizable,height=' +height+ ',width=' +width+ '');" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;

	return $r;
}

sub serviceModifyFuncs {
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
	$r .= "function toggleNameField(param) {" . $CONFIG_LINEFEED;
	$r .= " document." . $arg->{form} . ".name.value = document." . $arg->{form} . ".ext_name.value;" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;
	$r .= "function toggleStreetField(param) {" . $CONFIG_LINEFEED;
	$r .= " document." . $arg->{form} . ".street.value = document." . $arg->{form} . ".ext_street.value;" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;
	$r .= "function toggleZipField(param) {" . $CONFIG_LINEFEED;
	$r .= " document." . $arg->{form} . ".zip.value = document." . $arg->{form} . ".ext_zip.value;" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;
	$r .= "function toggleCityField(param) {" . $CONFIG_LINEFEED;
	$r .= " document." . $arg->{form} . ".city.value = document." . $arg->{form} . ".ext_city.value;" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;
	$r .= "function toggleCountryField(param) {" . $CONFIG_LINEFEED;
	$r .= " document." . $arg->{form} . ".country.value = document." . $arg->{form} . ".ext_country.value;" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;
	$r .= "function serviceNote(action, note, service, width, height) {" . $CONFIG_LINEFEED;
	$r .= " window.open('service_e.pl?action=' +action+ '&note=' +note+ '&service=' +service+ '', '', 'scrollbars,resizable,height=' +height+ ',width=' +width+ '');" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;

	return $r;
}

sub serviceModifyDisposedFuncs {
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

sub serviceNoteFuncs {
	my ($arg) = @_;

	my $r = "";

	$r .= "window.opener.location.reload();" . $CONFIG_LINEFEED;
	$r .= "window.close();" . $CONFIG_LINEFEED;

	return $r;
}

1;
