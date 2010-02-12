#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";
require "library.lib";
require "network.lib";



&headPrepare();

if($q->param('file') && $q->param('file') ne "" && $q->param('name') && $q->param('name') ne "") {
	my @r = &sendCommand({ command => "checkFile", item => $q->param('file'), domain => "", param => "", option => "" });

	if(int($r[0]) == $ERROR_NOERROR) {
		if(!$r[3] || $r[3] eq "") {
			&fileFail({ reason => "DOWNLOAD_FAILED" });
		}

		if($r[3] ne $q->param('file')) {
			&fileFail({ reason => "DOWNLOAD_FAILED" });
		}

		if(open(FILE, $DIR_UPLOAD . "/" . substr($q->param('file'), 0, 1) . "/" . $q->param('file'))) {
			my @l = stat($DIR_UPLOAD . "/" . substr($q->param('file'), 0, 1) . "/" . $q->param('file'));

			print STDOUT "Cache-control: no-cache" . $CONFIG_LINEFEED;
			print STDOUT "Content-disposition: attachment; filename=\"" . $q->param('name') . "\"" . $CONFIG_LINEFEED;
			print STDOUT "Content-length: " . int($l[7]) . $CONFIG_LINEFEED;
			print STDOUT "Content-type: application/x-download" . $CONFIG_LINEFEED . $CONFIG_LINEFEED;

			binmode(FILE);
			binmode(STDOUT);

			while(my $f = <FILE>) {
				print STDOUT $f;
			}

			close(FILE);
		}
		else {
			&fileFail({ reason => "DOWNLOAD_FAILED" });
		}
	}
	else {
		&fileFail({ reason => "DOWNLOAD_FAILED" });
	}
}
else {
	&fileFail({ reason => "DOWNLOAD_FAILED" });
}

exit(0);



sub fileFail {
	my ($arg) = @_;

	print STDOUT "Cache-control: no-cache" . $CONFIG_LINEFEED;
	print STDOUT "Content-disposition: attachment; filename=\"" . $arg->{reason} . "\"" . $CONFIG_LINEFEED;
	print STDOUT "Content-length: 0" . $CONFIG_LINEFEED;
	print STDOUT "Content-type: application/x-download" . $CONFIG_LINEFEED . $CONFIG_LINEFEED;

	exit(0);
}
