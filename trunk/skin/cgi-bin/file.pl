#!/usr/bin/perl

use CGI;

$q = new CGI;

require "variables.lib";



if($q->param('file') && $q->param('file') ne "" && $q->param('name') && $q->param('name') ne "") {
	if(open(FILE, $DIR_UPLOAD . "/" . substr($q->param('file'), 0, 1) . "/" . $q->param('file'))) {
		my @l = stat($DIR_UPLOAD . "/" . substr($q->param('file'), 0, 1) . "/" . $q->param('file'));

		print STDOUT "Cache-control: no-cache" . $CONFIG_LINEFEED;
		print STDOUT "Content-disposition: attachment; filename=\"" . $q->param('name') . "\"" . $CONFIG_LINEFEED;
		print STDOUT "Content-length: " . $l[7] . $CONFIG_LINEFEED;
		print STDOUT "Content-type: application/x-download" . $CONFIG_LINEFEED . $CONFIG_LINEFEED;

		binmode(FILE);
		binmode(STDOUT);

		while(my $f = <FILE>) {
			print STDOUT $f;
		}

		close(FILE);
	}
	else {
		print STDOUT "Cache-control: no-cache" . $CONFIG_LINEFEED;
		print STDOUT "Content-disposition: attachment; filename=\"DOWNLOAD_FAILED " . $! . "\"" . $CONFIG_LINEFEED;
		print STDOUT "Content-length: 0" . $CONFIG_LINEFEED;
		print STDOUT "Content-type: application/x-download" . $CONFIG_LINEFEED . $CONFIG_LINEFEED;
	}
}
else {
	print STDOUT "Cache-control: no-cache" . $CONFIG_LINEFEED;
	print STDOUT "Content-disposition: attachment; filename=\"DOWNLOAD_FAILED\"" . $CONFIG_LINEFEED;
	print STDOUT "Content-length: 0" . $CONFIG_LINEFEED;
	print STDOUT "Content-type: application/x-download" . $CONFIG_LINEFEED . $CONFIG_LINEFEED;
}

exit(0);
