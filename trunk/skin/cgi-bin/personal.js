#!/usr/bin/perl

my ($pack, $f, $line) = caller;

if($pack eq "" && $f eq "" && $line eq "") {
	print STDOUT "Content-Type: text/html" . "\r\n\r\n";

	exit(0);
}

sub modifyFuncs {
	my ($arg) = @_;

	my $r = "";

	$r .= "function toggleFileButton(param) {" . $CONFIG_LINEFEED;
	$r .= " if(document." . $arg->{form} . ".public.checked) {" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".submit.value = 'Add public file';" . $CONFIG_LINEFEED;
	$r .= " }" . $CONFIG_LINEFEED;
	$r .= " else {" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".submit.value = 'Add private file';" . $CONFIG_LINEFEED;
	$r .= " }" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;
	$r .= "function toggleFactionButton(param) {" . $CONFIG_LINEFEED;
	$r .= " if(document." . $arg->{form} . ".public.checked) {" . $CONFIG_LINEFEED;
	$r .= "  if(document." . $arg->{form} . ".type.checked) {" . $CONFIG_LINEFEED;
	$r .= "   document." . $arg->{form} . ".submit.value = 'Add pub/temp faction';" . $CONFIG_LINEFEED;
	$r .= "  }" . $CONFIG_LINEFEED;
	$r .= "  else {" . $CONFIG_LINEFEED;
	$r .= "   document." . $arg->{form} . ".submit.value = 'Add public faction';" . $CONFIG_LINEFEED;
	$r .= "  }" . $CONFIG_LINEFEED;
	$r .= " }" . $CONFIG_LINEFEED;
	$r .= " else {" . $CONFIG_LINEFEED;
	$r .= "  if(document." . $arg->{form} . ".type.checked) {" . $CONFIG_LINEFEED;
	$r .= "   document." . $arg->{form} . ".submit.value = 'Add priv/temp faction';" . $CONFIG_LINEFEED;
	$r .= "  }" . $CONFIG_LINEFEED;
	$r .= "  else {" . $CONFIG_LINEFEED;
	$r .= "   document." . $arg->{form} . ".submit.value = 'Add private faction';" . $CONFIG_LINEFEED;
	$r .= "  }" . $CONFIG_LINEFEED;
	$r .= " }" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;
	$r .= "function togglePasswordButton(param) {" . $CONFIG_LINEFEED;
	$r .= " if(document." . $arg->{form} . ".public.checked) {" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".submit.value = 'Add public password';" . $CONFIG_LINEFEED;
	$r .= " }" . $CONFIG_LINEFEED;
	$r .= " else {" . $CONFIG_LINEFEED;
	$r .= "  document." . $arg->{form} . ".submit.value = 'Add private password';" . $CONFIG_LINEFEED;
	$r .= " }" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;

	return $r;
}

sub passwordFuncs {
	my ($arg) = @_;

	my $r = "";

	$r .= "function promptPasswordKey(param) {" . $CONFIG_LINEFEED;
	$r .= " var key = prompt('Please enter decryption key for this password:', '');" . $CONFIG_LINEFEED;
	$r .= " if(key != null && key != '') {" . $CONFIG_LINEFEED;

	if($arg->{leaf} && $arg->{leaf} ne "") {
		$r .= "  window.location='" . $SELF . "?slice=" . $arg->{slice} . "&leaf=" . $arg->{leaf} . "&key=' + key + '';" . $CONFIG_LINEFEED;
	}
	else {
		$r .= "  window.location='" . $SELF . "?slice=" . $arg->{slice} . "&key=' + key + '';" . $CONFIG_LINEFEED;
	}

	$r .= " }" . $CONFIG_LINEFEED;
	$r .= "}" . $CONFIG_LINEFEED;

	return $r;
}

1;
