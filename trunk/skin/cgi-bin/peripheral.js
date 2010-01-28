#!/usr/bin/perl

my ($pack, $f, $line) = caller;

if($pack eq "" && $f eq "" && $line eq "") {
	print STDOUT "Content-Type: text/html" . "\r\n\r\n";

	exit(0);
}

sub peripheralListingFuncs {
	my ($arg) = @_;

	my $r = "";

	$r .= "function popupPeripheral(per, slice, width, height) {" . $CONFIG_LINEFEED;
	$r .= " window.open('peripheral_popup.pl?per=' +per+ '&slice=' +slice+ '', '', 'scrollbars,resizable,height=' +height+ ',width=' +width+ '');" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;

	return $r;
}

sub peripheralListingDisposedFuncs {
	my ($arg) = @_;

	my $r = "";

	$r .= "function popupPeripheral(per, slice, width, height) {" . $CONFIG_LINEFEED;
	$r .= " window.open('peripheral_d_popup.pl?per=' +per+ '&slice=' +slice+ '', '', 'scrollbars,resizable,height=' +height+ ',width=' +width+ '');" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;

	return $r;
}

sub peripheralModifyFuncs {
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
	$r .= "function toggleNetworkField(param) {" . $CONFIG_LINEFEED;
	$r .= " if(document." . $arg->{form} . ".dhcp.checked) {" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".ipaddress.disabled = 1;" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".ipaddress.value = 'Dynamic';" . $CONFIG_LINEFEED;
	$r .= " }" . $CONFIG_LINEFEED;
	$r .= " else {" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".ipaddress.disabled = 0;" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".ipaddress.value = '';" . $CONFIG_LINEFEED;
	$r .= " }" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;
	$r .= "function toggleCategoryField(param) {" . $CONFIG_LINEFEED;
	$r .= " document." . $arg->{form} . ".category.value = document." . $arg->{form} . ".ext_category.value;" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;
	$r .= "function toggleManufacturerField(param) {" . $CONFIG_LINEFEED;
	$r .= " document." . $arg->{form} . ".manufacturer.value = document." . $arg->{form} . ".ext_manufacturer.value;" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;
	$r .= "function toggleModelField(param) {" . $CONFIG_LINEFEED;
	$r .= " document." . $arg->{form} . ".model.value = document." . $arg->{form} . ".ext_model.value;" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;
	$r .= "function toggleServiceFields(param) {" . $CONFIG_LINEFEED;
	$r .= " if(document." . $arg->{form} . ".iis.checked) {" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".esd.disabled = 0;" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".dosd_day.disabled = 0;" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".dosd_month.disabled = 0;" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".dosd_year.disabled = 0;" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".mosd.disabled = 0;" . $CONFIG_LINEFEED;
	$r .= " }" . $CONFIG_LINEFEED;
	$r .= " else {" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".esd.disabled = 1;" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".dosd_day.disabled = 1;" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".dosd_month.disabled = 1;" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".dosd_year.disabled = 1;" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".mosd.disabled = 1;" . $CONFIG_LINEFEED;
	$r .= " }" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;

	return $r;
}

sub peripheralModifyDisposedFuncs {
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
