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
	$r .= "function toggleNodeField(param) {" . $CONFIG_LINEFEED;
	$r .= " document." . $arg->{form} . ".node.value = document." . $arg->{form} . ".ext_node.value;" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;
	$r .= "function toggleDomainField(param) {" . $CONFIG_LINEFEED;
	$r .= " document." . $arg->{form} . ".domain.value = document." . $arg->{form} . ".ext_domain.value;" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;
	$r .= "function toggleSystemField(param) {" . $CONFIG_LINEFEED;
	$r .= " document." . $arg->{form} . ".sys.value = document." . $arg->{form} . ".ext_sys.value;" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;
	$r .= "function toggleReleaseField(param) {" . $CONFIG_LINEFEED;
	$r .= " document." . $arg->{form} . ".rel.value = document." . $arg->{form} . ".ext_rel.value;" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;
	$r .= "function toggleDistributionField(param) {" . $CONFIG_LINEFEED;
	$r .= " document." . $arg->{form} . ".dist.value = document." . $arg->{form} . ".ext_dist.value;" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;
	$r .= "function togglePlatformField(param) {" . $CONFIG_LINEFEED;
	$r .= " document." . $arg->{form} . ".arch.value = document." . $arg->{form} . ".ext_arch.value;" . $CONFIG_LINEFEED;
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
	$r .= "function machineNote(action, note, host, width, height) {" . $CONFIG_LINEFEED;
	$r .= " window.open('machine_e.pl?action=' +action+ '&note=' +note+ '&host=' +host+ '', '', 'scrollbars,resizable,height=' +height+ ',width=' +width+ '');" . $CONFIG_LINEFEED;
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

sub machineNoteFuncs {
	my ($arg) = @_;

	my $r = "";

	$r .= "window.opener.location.reload();" . $CONFIG_LINEFEED;
	$r .= "window.close();" . $CONFIG_LINEFEED;

	return $r;
}

1;
