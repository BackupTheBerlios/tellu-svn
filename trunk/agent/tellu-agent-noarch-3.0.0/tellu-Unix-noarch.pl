#!/usr/bin/perl -w

use Socket;

#
# Variable declarations
#

$DATA_ARRAYS_COUNT = 17;
$DATA_POINTER_SIZE = 8;

$ITEM_DELIMITER = pack('c', 27);
$ITEM_SEPARATOR = pack('c', 26);
$ITEM_SPLITTER = '|';

$magickCookie = "TELLUTELLUTELLUTELLUTELLUTELLU";

%confData = ();

%nodeData = (
	"node" => "", "domain" => "", "system" => "", "release" => "", "machine" => "", "distribution" => "",
	"useruid" => "", "usergecos" => "", "userhomedir" => "", "usergrp" => ""
);

@cmdArrays = (
	"appGetName", "appGetVersion", "appGetDataPacket",
	"machGetInfo", "userGetInfo",
	"loadGetLoad",
	"cpuGetProcessor",
	"memGetMemory",
	"diskGetMounted",
	"netGetInterfaceData",
	"halGetDevices",
	"servGetCount", "servGetProcesses", "servGetServices",
	"netGetOpenPorts",
	"softGetInstalled",
	"termNull"
);

#
# Initialize local node and domain names
#

&nodeInitNames();

#
# Read and parse configuration files
#

my %cf = ();

$cf[0] = $nodeData{"useruid"} . "." . $nodeData{"domain"} . ".conf";
$cf[1] = $nodeData{"useruid"} . ".conf";
$cf[2] = $nodeData{"node"} . "." . $nodeData{"domain"} . ".conf";
$cf[3] = $nodeData{"node"} . ".conf";
$cf[4] = $nodeData{"domain"} . ".conf";
$cf[5] = $nodeData{"system"} . "-" . $nodeData{"release"} . "." . $nodeData{"machine"} . ".conf";
$cf[6] = $nodeData{"system"} . "-" . $nodeData{"release"} . ".conf";
$cf[7] = $nodeData{"system"} . "." . $nodeData{"machine"} . ".conf";
$cf[8] = $nodeData{"system"} . ".conf";
$cf[9] = "tellu.conf";

foreach my $c (@cf) {
	if(open(FILE, $c)) {
		while(my $newLine = <FILE>) {
			if($newLine =~ /^#|^\r|^\n/) {
				next;
			}

			my @newKey = split('=', $newLine, 2);

			$newKey[0] = cleanString({ string => $newKey[0] });
			$newKey[1] = cleanString({ string => $newKey[1] });

			if($newKey[0] ne "" && $newKey[1] ne "") {
				$confData{$newKey[0]} = $newKey[1];
			}
		}

		close(FILE);

		last;
	}
}

if((my $disabledFunc = &configFetch({ keyword => "disabled_functionality" })) ne "") {
	if($disabledFunc == 1 || $disabledFunc =~ /^y/i) {
		exit(0);
	}
}

if((my $domainName = &configFetch({ keyword => "domain_override" })) ne "") {
	$nodeData{"domain"} = cleanString({ string => $domainName });
}

#
# Initialize magick cookie
#

if((my $confMagCoo = &configFetch({ keyword => "server_password" })) ne "") {
	my $s = int(length($confMagCoo));

	if($s > int(length($magickCookie))) {
		$s = int(length($magickCookie));
	}

	$magickCookie = substr($confMagCoo, 0, $s) . substr($magickCookie, length($confMagCoo));
}

#
# Collect machine data
#

while(1) {
	my $dataPacket = "";
	my $dataPointer = "";

	my $t = int(length($magickCookie) + int($DATA_ARRAYS_COUNT * $DATA_POINTER_SIZE));

	for(my $i = 0; $i < $DATA_ARRAYS_COUNT; $i++) {
		my $q = $cmdArrays[$i];
		my $r = &$q();

		$dataPointer .= sprintf("%.8u", $t);
		$dataPacket .= $r;

		$t += length($r);
	}

	my $infoCookie = sprintf("%.8u%.8u%.8u", 0, $t, $t);

	$dataPacket = $magickCookie . $infoCookie . $dataPointer . $dataPacket;

	#
	# Send data packet to the server
	#

	if((my $serverName = &configFetch({ keyword => "tellud_server" })) ne "") {
		my $serverPort;

		if(($serverPort = &configFetch({ keyword => "tellud_port" })) eq "") {
			$serverPort = 1700;
		}

		my $pr = getprotobyname("tcp") || warn $0 . ": tcp: Unknown protocol: $!" . "\n";
		my $ia = inet_aton($serverName) || warn $0 . ": " . $serverName . ": Unknown host: $!" . "\n";
		my $pa = sockaddr_in($serverPort, $ia);

		socket(S, PF_INET, SOCK_STREAM, $pr) || warn $0 . ": Error occurred while trying to create socket: $!" . "\n";
		connect(S, $pa) || warn $0 . ": Error occurred while trying to connect to " . $serverName . ": $!" . "\n";

		my $r = 0;

		while(1) {
			my $s = send(S, $dataPacket, 0);

			if(!$s) {
				warn $0 . ": Error occurred while trying to send data to peer: $!" . "\n";

				last;
			}

			$r += $s;

			if($r >= length($dataPacket)) {
				last;
			}
		}

		close(S);
	}

	#
	# Loop back if looping mode is requested
	#

	my $l = 0;

	if((my $loopDelay = &configFetch({ keyword => "looping_delay" })) ne "") {
		$l = $loopDelay;
	}

	if($l <= 0 || $l > 2592000) {
		last;
	}
	else {
		$l *= 60;

		sleep($l);
	}
}

#
# Terminate program
#

exit(0);



sub cleanString {
	my ($arg) = @_;

	if($arg->{string} ne "") {
		$arg->{string} =~ s/^"+|^'+|^\s+|^\t+//g;
		$arg->{string} =~ s/"+$|'+$|\s+$|\t+$//g;
		$arg->{string} =~ s/\r+$|\n+$//g;

		return $arg->{string};
	}

	return "";
}

sub configFetch {
	my ($arg) = @_;

	return $confData{$arg->{keyword}};
}

sub appGetName {
	my ($arg) = @_;

	return "tellu";
}

sub appGetVersion {
	my ($arg) = @_;

	return "3.0.0-noarch";
}

sub appGetDataPacket {
	my ($arg) = @_;

	return "collection";
}

sub machGetInfo {
	my ($arg) = @_;

	my $r = "";

	$r .= $nodeData{"node"} . $ITEM_SEPARATOR;
	$r .= $nodeData{"domain"} . $ITEM_SEPARATOR;
	$r .= $nodeData{"system"} . $ITEM_SEPARATOR;
	$r .= $nodeData{"release"} . $ITEM_SEPARATOR;
	$r .= $nodeData{"distribution"} . $ITEM_SEPARATOR;
	$r .= $nodeData{"machine"};

	return $r;
}

sub userGetInfo {
	my ($arg) = @_;

	my $r = "";

	$r .= $nodeData{"useruid"} . $ITEM_SEPARATOR;
	$r .= $nodeData{"usergrp"} . $ITEM_SEPARATOR;
	$r .= $nodeData{"usergecos"} . $ITEM_SEPARATOR;
	$r .= $nodeData{"userhomedir"};

	return $r;
}

sub loadGetLoad {
	my ($arg) = @_;

	my @l = ("", "", "");
	my @u = ("", "");

	#
	# Fetch load averages from /proc/loadavg
	#

	if(open(FILE, "/proc/loadavg")) {
		@l = split(/\s+/, <FILE>);

		close(FILE);
	}
	else {
		#
		# If /proc/loadavg is unavailable, try alternate method (MacOSX, Solaris)
		#

		@l = split(/average:|averages:/, `uptime 2>/dev/null`);

		$l[1] = cleanString({ string => $l[1] });
		$l[1] =~ s/,/./go;

		@l = split(/\s+/, $l[1], 3);
	}

	#
	# Fetch uptime and idletime from /proc/uptime
	#

	if(open(FILE, "/proc/uptime")) {
		@u = split(/\s+/, <FILE>);

		close(FILE);
	}

	my $r = "";

	$r .= $l[0] . $ITEM_SEPARATOR;
	$r .= $l[1] . $ITEM_SEPARATOR;
	$r .= $l[2] . $ITEM_SEPARATOR;
	$r .= $u[0] . $ITEM_SEPARATOR;
	$r .= $u[1];

	return $r;
}

sub cpuGetProcessor {
	my ($arg) = @_;

	my %newDist = (
		"cpus" => 0, "cores" => "", "siblings" => "", "mhz" => "", "cache" => "", "mips" => ""
	);

	#
	# Fetch cpu info from /proc/cpuinfo
	#

	if(open(FILE, "/proc/cpuinfo")) {
		my @newKeys = (
			"physical id", "cpu cores", "siblings", "cpu MHz", "cache size", "bogomips"
		);

		while(my $newLine = <FILE>) {
			if($newLine =~ /^#|^\r|^\n/) {
				next;
			}

			my @newKey = split(':', $newLine, 2);

			$newKey[0] = cleanString({ string => $newKey[0] });

			for(my $i = 0; $i < @newKeys; $i++) {
				if($newKeys[$i] =~ /^$newKey[0]/i) {
					$newKey[1] = cleanString({ string => $newKey[1] });

					if($newKeys[$i] =~ /^$newKeys[0]/i) {
						if(($newKey[1] + 1) >= $newDist{"cpus"}) {
							$newDist{"cpus"} = $newKey[1] + 1;
						}
					}
					elsif($newKeys[$i] =~ /^$newKeys[1]/i) {
						$newDist{"cores"} = $newKey[1];
					}
					elsif($newKeys[$i] =~ /^$newKeys[2]/i) {
						$newDist{"siblings"} = $newKey[1];
					}
					elsif($newKeys[$i] =~ /^$newKeys[3]/i) {
						$newDist{"mhz"} = $newKey[1];
					}
					elsif($newKeys[$i] =~ /^$newKeys[4]/i) {
						$newDist{"cache"} = $newKey[1];
						$newDist{"cache"} =~ s/\s.*?$//;
					}
					elsif($newKeys[$i] =~ /^$newKeys[5]/i) {
						$newDist{"mips"} = $newKey[1];
					}

					last;
				}
			}
		}

		close(FILE);
	}
	else {
		#
		# If /proc/cpuinfo is unavailable, try alternate method (MacOSX)
		#

		my @newKeys = (
			"Number Of CPUs", "CPU Speed"
		);

		my @l = `/usr/sbin/system_profiler -detailLevel full SPHardwareDataType 2>/dev/null`;

		foreach my $newLine (@l) {
			if($newLine =~ /^#|^\r|^\n/) {
				next;
			}

			my @newKey = split(':', $newLine, 2);

			$newKey[0] = cleanString({ string => $newKey[0] });

			for(my $i = 0; $i < @newKeys; $i++) {
				if($newKeys[$i] =~ /^$newKey[0]/i) {
					$newKey[1] = cleanString({ string => $newKey[1] });

					if($newKeys[$i] =~ /^$newKeys[0]/i) {
						$newDist{"cpus"} = $newKey[1];
					}
					elsif($newKeys[$i] =~ /^$newKeys[1]/i) {
						my @l = split(/\s+/, $newKey[1], 2);

						$newDist{"mhz"} = $l[0];

						if($l[1] =~ /GHz/i) {
							$newDist{"mhz"} *= 1000;
						}
						elsif($l[1] =~ /THz/i) {
							$newDist{"mhz"} *= 1000000;
						}
					}

					last;
				}
			}
		}
	}

	my $r = "";

	$r .= $newDist{"cpus"} . $ITEM_SEPARATOR;
	$r .= $newDist{"cores"} . $ITEM_SEPARATOR;
	$r .= $newDist{"siblings"} . $ITEM_SEPARATOR;
	$r .= $newDist{"mhz"} . $ITEM_SEPARATOR;
	$r .= $newDist{"cache"} . $ITEM_SEPARATOR;
	$r .= $newDist{"mips"};

	return $r;
}

sub memGetMemory {
	my ($arg) = @_;

	my %newDist = (
		"ramtotal" => "", "ramavail" => "", "swaptotal" => "", "swapavail" => "", "buffers" => "", "cached" => ""
	);

	#
	# Fetch memory info from /proc/meminfo
	#

	if(open(FILE, "/proc/meminfo")) {
		my @newKeys = (
			"MemFree", "MemTotal", "SwapFree", "SwapTotal", "Buffers", "Cached"
		);

		while(my $newLine = <FILE>) {
			if($newLine =~ /^#|^\r|^\n/) {
				next;
			}

			my @newKey = split(':', $newLine, 2);

			$newKey[0] = cleanString({ string => $newKey[0] });

			for(my $i = 0; $i < @newKeys; $i++) {
				if($newKeys[$i] =~ /^$newKey[0]/i) {
					$newKey[1] = cleanString({ string => $newKey[1] });

					if($newKeys[$i] =~ /^$newKeys[0]/i) {
						$newDist{"ramtotal"} = $newKey[1];
						$newDist{"ramtotal"} =~ s/\s.*?$//;
					}
					elsif($newKeys[$i] =~ /^$newKeys[1]/i) {
						$newDist{"ramavail"} = $newKey[1];
						$newDist{"ramavail"} =~ s/\s.*?$//;
					}
					elsif($newKeys[$i] =~ /^$newKeys[2]/i) {
						$newDist{"swaptotal"} = $newKey[1];
						$newDist{"swaptotal"} =~ s/\s.*?$//;
					}
					elsif($newKeys[$i] =~ /^$newKeys[3]/i) {
						$newDist{"swapavail"} = $newKey[1];
						$newDist{"swapavail"} =~ s/\s.*?$//;
					}
					elsif($newKeys[$i] =~ /^$newKeys[4]/i) {
						$newDist{"buffers"} = $newKey[1];
						$newDist{"buffers"} =~ s/\s.*?$//;
					}
					elsif($newKeys[$i] =~ /^$newKeys[5]/i) {
						$newDist{"cached"} = $newKey[1];
						$newDist{"cached"} =~ s/\s.*?$//;
					}

					last;
				}
			}
		}

		close(FILE);
	}
	else {
		#
		# If /proc/meminfo is unavailable, try alternate method (MacOSX)
		#

		my @newKeys = (
			"Memory"
		);

		my @l = `/usr/sbin/system_profiler -detailLevel full SPHardwareDataType 2>/dev/null`;

		foreach my $newLine (@l) {
			if($newLine =~ /^#|^\r|^\n/) {
				next;
			}

			my @newKey = split(':', $newLine, 2);

			$newKey[0] = cleanString({ string => $newKey[0] });

			for(my $i = 0; $i < @newKeys; $i++) {
				if($newKeys[$i] =~ /^$newKey[0]/i) {
					$newKey[1] = cleanString({ string => $newKey[1] });

					if($newKeys[$i] =~ /^$newKeys[0]/i) {
						my @l = split(/\s+/, $newKey[1], 2);

						$newDist{"ramtotal"} = $l[0];

						if($l[1] =~ /MB/i) {
							$newDist{"ramtotal"} *= 1000;
						}
						elsif($l[1] =~ /GB/i) {
							$newDist{"ramtotal"} *= 1000000;
						}
						elsif($l[1] =~ /TB/i) {
							$newDist{"ramtotal"} *= 1000000000;
						}
					}

					last;
				}
			}
		}
	}

	my $r = "";

	$r .= $newDist{"ramtotal"} . $ITEM_SEPARATOR;
	$r .= $newDist{"ramavail"} . $ITEM_SEPARATOR;
	$r .= $newDist{"swaptotal"} . $ITEM_SEPARATOR;
	$r .= $newDist{"swapavail"} . $ITEM_SEPARATOR;
	$r .= $newDist{"buffers"} . $ITEM_SEPARATOR;
	$r .= $newDist{"cached"};

	return $r;
}

sub diskGetMounted {
	my ($arg) = @_;

	my $r = "";

	#
	# Fetch mounts from /etc/mtab or /proc/mounts
	#

	my @newKeys = (
		"/etc/mtab", "/proc/mounts"
	);

	foreach my $n (@newKeys) {
		if(open(FILE, $n)) {
			while(my $newLine = <FILE>) {
				if($newLine =~ /^#|^\r|^\n/) {
					next;
				}

				my @newKey = split(/\s+/, $newLine, 6);

				$newKey[0] = cleanString({ string => $newKey[0] });
				$newKey[1] = cleanString({ string => $newKey[1] });
				$newKey[2] = cleanString({ string => $newKey[2] });
				$newKey[3] = cleanString({ string => $newKey[3] });
				$newKey[4] = cleanString({ string => $newKey[4] });
				$newKey[5] = cleanString({ string => $newKey[5] });

				my @k = `df -B 1000 $newKey[1] 2>/dev/null`;

				if($k[1]) {
					$k[1] =~ s/\s+/ /g;

					@k = split(/\s+/, $k[1], 6);

					if(@k != 6) {
						@k = ("", "0", "0", "0", "", "");
					}
				}
				else {
					@k = ("", "0", "0", "0", "", "");
				}

				$r .= $newKey[0] . $ITEM_SEPARATOR;
				$r .= $newKey[1] . $ITEM_SEPARATOR;
				$r .= $newKey[2] . $ITEM_SEPARATOR;
				$r .= $newKey[3] . $ITEM_SEPARATOR;
				$r .= $k[1] . $ITEM_SEPARATOR;
				$r .= $k[3] . $ITEM_SEPARATOR;
				$r .= "0" . $ITEM_DELIMITER;
			}

			close(FILE);

			if($r =~ /$ITEM_DELIMITER$/) {
				$r = substr($r, 0, length($r) - 1);
			}

			last;
		}
	}

	if($r eq "") {
		#
		# If /etc/mtab and /proc/mounts are unavailable, try alternate method (MacOSX)
		#

		my @l = `/sbin/mount 2>/dev/null`;

		foreach my $newLine (@l) {
			if($newLine =~ /^#|^\r|^\n/) {
				next;
			}

			my @newKey = ();
			my @k = split(/ on /, $newLine, 2);

			$newKey[0] = $k[0];
			($newKey[1], $newKey[2]) = split(/\s+/, $k[1], 2);

			$newKey[0] = cleanString({ string => $newKey[0] });
			$newKey[1] = cleanString({ string => $newKey[1] });
			$newKey[2] = cleanString({ string => $newKey[2] });

			@k = `df -k $newKey[1] 2>/dev/null`;

			if($k[1]) {
				$k[1] =~ s/\s+/ /g;

				@k = split(/\s+/, $k[1], 6);

				if(@k != 6) {
					@k = ("", "0", "0", "0", "", "");
				}
			}
			else {
				@k = ("", "0", "0", "0", "", "");
			}

			$r .= $newKey[0] . $ITEM_SEPARATOR;
			$r .= $newKey[1] . $ITEM_SEPARATOR;
			$r .= "" . $ITEM_SEPARATOR;
			$r .= $newKey[2] . $ITEM_SEPARATOR;
			$r .= $k[1] . $ITEM_SEPARATOR;
			$r .= $k[3] . $ITEM_SEPARATOR;
			$r .= "0" . $ITEM_DELIMITER;
		}

		if($r =~ /$ITEM_DELIMITER$/) {
			$r = substr($r, 0, length($r) - 1);
		}
	}

	return $r;
}

sub netGetInterfaceData {
	my ($arg) = @_;

	my $r = "";

	my %newDist = (
		"nic" => "", "ip4" => "", "bcast4" => "", "netmask4" => "", "mac" => ""
	);

	#
	# Fetch interface data from /proc/net/dev
	#

	if(open(FILE, "/proc/net/dev")) {
		my @newKeys = (
			"ifconfig", "/sbin/ifconfig"
		);

		while(my $newLine = <FILE>) {
			if($newLine =~ /^#|^\r|^\n/) {
				next;
			}

			my @newKey = split(':', $newLine, 2);

			if(@newKey == 2) {
				$newKey[0] = cleanString({ string => $newKey[0] });

				my @k = ();

				foreach my $n (@newKeys) {
					@k = `$n $newKey[0] 2>/dev/null`;

					if(@k > 0) {
						$newDist{"nic"} = $newKey[0];

						$newDist{"ip4"} = "0.0.0.0";
						$newDist{"bcast4"} = "0.0.0.0";
						$newDist{"netmask4"} = "0.0.0.0";
						$newDist{"mac"} = "00:00:00:00:00:00";

						foreach my $e (@k) {
							if($e =~ /inet addr:/) {
								$f = $e;
								$f =~ s/^.*inet addr://;
								$f = cleanString({ string => $f });
								$f =~ s/ .*?$//;

								$newDist{"ip4"} = cleanString({ string => $f });
							}
							if($e =~ /Bcast:/) {
								$f = $e;
								$f =~ s/^.*Bcast://;
								$f = cleanString({ string => $f });
								$f =~ s/ .*?$//;
								$f = cleanString({ string => $f });

								$newDist{"bcast4"} = cleanString({ string => $f });
							}
							if($e =~ /Mask:/) {
								$f = $e;
								$f =~ s/^.*Mask://;
								$f = cleanString({ string => $f });
								$f =~ s/ .*?$//;
								$f = cleanString({ string => $f });

								$newDist{"netmask4"} = cleanString({ string => $f });
							}
							if($e =~ /HWaddr/) {
								$f = $e;
								$f =~ s/^.*HWaddr//;
								$f = cleanString({ string => $f });
								$f =~ s/ .*?$//;
								$f = cleanString({ string => $f });

								$newDist{"mac"} = cleanString({ string => $f });
							}
						}

						last;
					}
				}

				if($newDist{"nic"} ne "" && $newDist{"ip4"} ne "" && $newDist{"bcast4"} ne "" && $newDist{"netmask4"} ne "" && $newDist{"mac"} ne "") {
					$r .= $newKey[0] . $ITEM_SEPARATOR;
					$r .= $newDist{"ip4"} . $ITEM_SEPARATOR;
					$r .= $newDist{"bcast4"} . $ITEM_SEPARATOR;
					$r .= $newDist{"netmask4"} . $ITEM_SEPARATOR;
					$r .= $newDist{"mac"} . $ITEM_DELIMITER;
				}

				if(!@k) {
					$r .= $newKey[0] . $ITEM_SEPARATOR;
					$r .= "0.0.0.0" . $ITEM_SEPARATOR;
					$r .= "0.0.0.0" . $ITEM_SEPARATOR;
					$r .= "0.0.0.0" . $ITEM_SEPARATOR;
					$r .= "00:00:00:00:00:00" . $ITEM_DELIMITER;
				}
			}
		}

		close(FILE);

		if($r =~ /$ITEM_DELIMITER$/) {
			$r = substr($r, 0, length($r) - 1);
		}
	}
	else {
		#
		# If /proc/net/dev is unavailable, try alternate method (MacOSX)
		#

		my @i = ();
		my @l = `/sbin/ifconfig 2>/dev/null`;

		foreach my $l (@l) {
			if($l =~ /^[a-zA-Z0-9]/) {
				$l =~ s/:.*$//;

				push @i, cleanString({ string => $l });
			}
		}

		foreach my $i (@i) {
			my @k = `/sbin/ifconfig "$i" 2>/dev/null`;

			if(@k > 0) {
				$newDist{"nic"} = $i;

				$newDist{"ip4"} = "0.0.0.0";
				$newDist{"bcast4"} = "0.0.0.0";
				$newDist{"netmask4"} = "0.0.0.0";
				$newDist{"mac"} = "00:00:00:00:00:00";

				foreach my $e (@k) {
					if($e =~ /inet /i) {
						$f = $e;
						$f =~ s/^.*inet //i;
						$f = cleanString({ string => $f });
						$f =~ s/ .*?$//;

						$newDist{"ip4"} = cleanString({ string => $f });
					}
					if($e =~ /broadcast /i) {
						$f = $e;
						$f =~ s/^.*broadcast //i;
						$f = cleanString({ string => $f });
						$f =~ s/ .*?$//;
						$f = cleanString({ string => $f });

						$newDist{"bcast4"} = cleanString({ string => $f });
					}
					if($e =~ /netmask /i) {
						$f = $e;
						$f =~ s/^.*netmask //i;
						$f = cleanString({ string => $f });
						$f =~ s/ .*?$//;
						$f = cleanString({ string => $f });

						$newDist{"netmask4"} = cleanString({ string => $f });
					}
					if($e =~ /ether /i) {
						$f = $e;
						$f =~ s/^.*ether //i;
						$f = cleanString({ string => $f });
						$f =~ s/ .*?$//;
						$f = cleanString({ string => $f });

						$newDist{"mac"} = cleanString({ string => $f });
					}
				}
			}

			if($newDist{"nic"} ne "" && $newDist{"ip4"} ne "" && $newDist{"bcast4"} ne "" && $newDist{"netmask4"} ne "" && $newDist{"mac"} ne "") {
				$r .= $i . $ITEM_SEPARATOR;
				$r .= $newDist{"ip4"} . $ITEM_SEPARATOR;
				$r .= $newDist{"bcast4"} . $ITEM_SEPARATOR;
				$r .= $newDist{"netmask4"} . $ITEM_SEPARATOR;
				$r .= $newDist{"mac"} . $ITEM_DELIMITER;
			}

			if(!@k) {
				$r .= $i . $ITEM_SEPARATOR;
				$r .= "0.0.0.0" . $ITEM_SEPARATOR;
				$r .= "0.0.0.0" . $ITEM_SEPARATOR;
				$r .= "0.0.0.0" . $ITEM_SEPARATOR;
				$r .= "00:00:00:00:00:00" . $ITEM_DELIMITER;
			}
		}

		if($r =~ /$ITEM_DELIMITER$/) {
			$r = substr($r, 0, length($r) - 1);
		}
	}

	return $r;
}

sub halGetDevices {
	my ($arg) = @_;

	return "";
}

sub servGetCount {
	my ($arg) = @_;

	my %newDist = (
		"tasks" => 0, "threads" => 0
	);

	my @newKeys = (
		"Threads"
	);

	my $r = "";

	if(opendir(DIR, "/proc")) {
		my @newDirs = grep { ! /^\./ && -d "/proc/$_" } readdir(DIR);

		closedir(DIR);

		foreach my $d (@newDirs) {
			if($d =~ /^-?\d/) {
				if(open(FILE, "/proc/" . $d . "/status")) {
					while(my $newLine = <FILE>) {
						if($newLine =~ /^#|^\r|^\n/) {
							next;
						}

						my @newKey = split(':', $newLine, 2);

						$newKey[0] = cleanString({ string => $newKey[0] });

						for(my $i = 0; $i < @newKeys; $i++) {
							if($newKeys[$i] eq $newKey[0]) {
								$newKey[1] = cleanString({ string => $newKey[1] });

								if($newKeys[$i] =~ /^$newKeys[0]/i) {
									$newDist{"threads"} += $newKey[1];
								}

								last;
							}
						}
					}

					close(FILE);

					$newDist{"tasks"}++;
				}
			}
		}
	}

	if($newDist{"tasks"} != 0 && $newDist{"threads"} != 0) {
		$r .= $newDist{"tasks"} . $ITEM_SEPARATOR;
		$r .= $newDist{"threads"};
	}

	return $r;
}

sub servGetProcesses {
	my ($arg) = @_;

	my $r = &servGetProcessList({ daemon => "no" });

	return $r;
}

sub servGetServices {
	my ($arg) = @_;

	my $r = &servGetProcessList({ daemon => "yes" });

	return $r;
}

sub servGetProcessList {
	my ($arg) = @_;

	my %newDist = (
		"cmdline" => "kernel", "name" => "", "state" => "", "pid" => "", "ppid" => "", "uid" => "", "gid" => "",
		"vmpeak" => "", "vmsize" => "", "vmhwm" => "", "vmrss" => "", "vmdata" => "", "vmstk" => "", "vmexe" => "", "vmlib" => "", "vmpte" => "",
		"threads" => "",
		"rchar" => "", "wchar" => "", "syscr" => "", "syscw" => "", "rbyte" => "", "wbyte" => ""
	);

	my @newStatKeys = (
		"Name", "State", "Pid", "PPid", "Uid", "Gid", "VmPeak", "VmSize", "VmHWM",
		"VmRSS", "VmData", "VmStk", "VmExe", "VmLib", "VmPTE", "Threads"
	);

	my @newIoKeys = (
		"rchar", "wchar", "syscr", "syscw", "rbyte", "wbyte"
	);

	my $r = "";

	if(opendir(DIR, "/proc")) {
		my @newDirs = grep { ! /^\./ && -d "/proc/$_" } readdir(DIR);

		closedir(DIR);

		foreach my $d (@newDirs) {
			if($d =~ /^-?\d/) {
				$newDist{"cmdline"} = "kernel";
				$newDist{"name"} = "";
				$newDist{"state"} = "";
				$newDist{"pid"} = "";
				$newDist{"ppid"} = "";
				$newDist{"uid"} = "";
				$newDist{"gid"} = "";
				$newDist{"vmpeak"} = "";
				$newDist{"vmsize"} = "";
				$newDist{"vmhwm"} = "";
				$newDist{"vmrss"} = "";
				$newDist{"vmdata"} = "";
				$newDist{"vmstk"} = "";
				$newDist{"vmexe"} = "";
				$newDist{"vmlib"} = "";
				$newDist{"vmpte"} = "";
				$newDist{"threads"} = "";
				$newDist{"rchar"} = "";
				$newDist{"wchar"} = "";
				$newDist{"syscr"} = "";
				$newDist{"syscw"} = "";
				$newDist{"rbyte"} = "";
				$newDist{"wbyte"} = "";

				if(open(FILE, "/proc/" . $d . "/cmdline")) {
					while(my $newLine = <FILE>) {
						if($newLine =~ /^#|^\r|^\n/) {
							next;
						}

						my @k = split('\0', $newLine, 2);

						$newDist{"cmdline"} = cleanString({ string => $k[0] });

						last;
					}

					close(FILE);
				}

				if($arg->{daemon} =~ /yes/i) {
					$newDist{"cmdline"} =~ s/\s.*?$//;
					$newDist{"cmdline"} =~ s/:$//;

					my @k = split('/', $newDist{"cmdline"});

					$newDist{"cmdline"} = $k[-1];

					if(substr($newDist{"cmdline"}, -1, 1) ne "d") {
						next;
					}
				}

				if(open(FILE, "/proc/" . $d . "/status")) {
					while(my $newLine = <FILE>) {
						if($newLine =~ /^#|^\r|^\n/) {
							next;
						}

						my @newKey = split(':', $newLine, 2);

						$newKey[0] = cleanString({ string => $newKey[0] });

						for(my $i = 0; $i < @newStatKeys; $i++) {
							if($newStatKeys[$i] eq $newKey[0]) {
								$newKey[1] = cleanString({ string => $newKey[1] });

								if($newStatKeys[$i] =~ /^$newStatKeys[0]/i) {
									$newDist{"name"} = $newKey[1];
								}
								elsif($newStatKeys[$i] =~ /^$newStatKeys[1]/i) {
									$newDist{"state"} = $newKey[1];
								}
								elsif($newStatKeys[$i] =~ /^$newStatKeys[2]/i) {
									$newDist{"pid"} = $newKey[1];
								}
								elsif($newStatKeys[$i] =~ /^$newStatKeys[3]/i) {
									$newDist{"ppid"} = $newKey[1];
								}
								elsif($newStatKeys[$i] =~ /^$newStatKeys[4]/i) {
									$newDist{"uid"} = $newKey[1];
									$newDist{"uid"} =~ s/\s.*?$//;
									$newDist{"uid"} = getpwuid($newDist{"uid"});
								}
								elsif($newStatKeys[$i] =~ /^$newStatKeys[5]/i) {
									$newDist{"gid"} = $newKey[1];
									$newDist{"gid"} =~ s/\s.*?$//;
									$newDist{"gid"} = getgrgid($newDist{"gid"});
								}
								elsif($newStatKeys[$i] =~ /^$newStatKeys[6]/i) {
									$newDist{"vmpeak"} = $newKey[1];
									$newDist{"vmpeak"} =~ s/\s.*?$//;
								}
								elsif($newStatKeys[$i] =~ /^$newStatKeys[7]/i) {
									$newDist{"vmsize"} = $newKey[1];
									$newDist{"vmsize"} =~ s/\s.*?$//;
								}
								elsif($newStatKeys[$i] =~ /^$newStatKeys[8]/i) {
									$newDist{"vmhwm"} = $newKey[1];
									$newDist{"vmhwm"} =~ s/\s.*?$//;
								}
								elsif($newStatKeys[$i] =~ /^$newStatKeys[9]/i) {
									$newDist{"vmrss"} = $newKey[1];
									$newDist{"vmrss"} =~ s/\s.*?$//;
								}
								elsif($newStatKeys[$i] =~ /^$newStatKeys[10]/i) {
									$newDist{"vmdata"} = $newKey[1];
									$newDist{"vmdata"} =~ s/\s.*?$//;
								}
								elsif($newStatKeys[$i] =~ /^$newStatKeys[11]/i) {
									$newDist{"vmstk"} = $newKey[1];
									$newDist{"vmstk"} =~ s/\s.*?$//;
								}
								elsif($newStatKeys[$i] =~ /^$newStatKeys[12]/i) {
									$newDist{"vmexe"} = $newKey[1];
									$newDist{"vmexe"} =~ s/\s.*?$//;
								}
								elsif($newStatKeys[$i] =~ /^$newStatKeys[13]/i) {
									$newDist{"vmlib"} = $newKey[1];
									$newDist{"vmlib"} =~ s/\s.*?$//;
								}
								elsif($newStatKeys[$i] =~ /^$newStatKeys[14]/i) {
									$newDist{"vmpte"} = $newKey[1];
									$newDist{"vmpte"} =~ s/\s.*?$//;
								}
								elsif($newStatKeys[$i] =~ /^$newStatKeys[15]/i) {
									$newDist{"threads"} = $newKey[1];
								}

								last;
							}
						}
					}

					close(FILE);
				}

				if(open(FILE, "/proc/" . $d . "/io")) {
					while(my $newLine = <FILE>) {
						if($newLine =~ /^#|^\r|^\n/) {
							next;
						}

						my @newKey = split(':', $newLine, 2);

						$newKey[0] = cleanString({ string => $newKey[0] });

						for(my $i = 0; $i < @newIoKeys; $i++) {
							if($newIoKeys[$i] =~ /^$newKey[0]/i) {
								$newKey[1] = cleanString({ string => $newKey[1] });

								if($newStatKeys[$i] =~ /^$newStatKeys[0]/i) {
									$newDist{"rchar"} = $newKey[1];
								}
								elsif($newStatKeys[$i] =~ /^$newStatKeys[1]/i) {
									$newDist{"wchar"} = $newKey[1];
								}
								elsif($newStatKeys[$i] =~ /^$newStatKeys[2]/i) {
									$newDist{"syscr"} = $newKey[1];
								}
								elsif($newStatKeys[$i] =~ /^$newStatKeys[3]/i) {
									$newDist{"syscw"} = $newKey[1];
								}
								elsif($newStatKeys[$i] =~ /^$newStatKeys[4]/i) {
									$newDist{"rbyte"} = $newKey[1];
								}
								elsif($newStatKeys[$i] =~ /^$newStatKeys[5]/i) {
									$newDist{"wbyte"} = $newKey[1];
								}

								last;
							}
						}
					}

					close(FILE);
				}

				if($newDist{"name"} ne "") {
					$r .= $newDist{"cmdline"} . $ITEM_SEPARATOR;
					$r .= $newDist{"name"} . $ITEM_SEPARATOR;
					$r .= $newDist{"state"} . $ITEM_SEPARATOR;
					$r .= $newDist{"pid"} . $ITEM_SEPARATOR;
					$r .= $newDist{"ppid"} . $ITEM_SEPARATOR;
					$r .= $newDist{"threads"} . $ITEM_SEPARATOR;
					$r .= $newDist{"vmdata"} . $ITEM_SEPARATOR;
					$r .= $newDist{"vmexe"} . $ITEM_SEPARATOR;
					$r .= $newDist{"vmhwm"} . $ITEM_SEPARATOR;
					$r .= $newDist{"vmlib"} . $ITEM_SEPARATOR;
					$r .= $newDist{"vmpeak"} . $ITEM_SEPARATOR;
					$r .= $newDist{"vmpte"} . $ITEM_SEPARATOR;
					$r .= $newDist{"vmrss"} . $ITEM_SEPARATOR;
					$r .= $newDist{"vmsize"} . $ITEM_SEPARATOR;
					$r .= $newDist{"vmstk"} . $ITEM_SEPARATOR;
					$r .= $newDist{"rchar"} . $ITEM_SEPARATOR;
					$r .= $newDist{"wchar"} . $ITEM_SEPARATOR;
					$r .= $newDist{"syscr"} . $ITEM_SEPARATOR;
					$r .= $newDist{"syscw"} . $ITEM_SEPARATOR;
					$r .= $newDist{"rbyte"} . $ITEM_SEPARATOR;
					$r .= $newDist{"wbyte"} . $ITEM_SEPARATOR;
					$r .= $newDist{"uid"} . $ITEM_SEPARATOR;
					$r .= $newDist{"gid"} . $ITEM_DELIMITER;
				}
			}
		}
	}

	if($r =~ /$ITEM_DELIMITER$/) {
		$r = substr($r, 0, length($r) - 1);
	}

	return $r;
}

sub netGetOpenPorts {
	my ($arg) = @_;

	my $s = 0;
	my $e = 0;
	my $r = "";

	if(($s = &configFetch({ keyword => "start_portscan" })) ne "") {
		$s = cleanString({ string => $s });
	}

	if(($e = &configFetch({ keyword => "end_portscan" })) ne "") {
		$e = cleanString({ string => $e });
	}

	if($s <= 0 || $e <= 0 || $s > 65536 || $e > 65536 || $e <= $s) {
		return $r;
	}

	my $pr = getprotobyname("tcp") || warn $0 . ": tcp: Unknown protocol: $!" . "\n";
	my $ia = inet_aton("localhost") || warn $0 . ": localhost: Unknown host: $!" . "\n";

	for(my $i = $s; $i < $e; $i++) {
		my $pa = sockaddr_in($i, $ia);

		socket(S, PF_INET, SOCK_STREAM, $pr) || warn $0 . ": Error occurred while trying to create socket: $!" . "\n";

		if(connect(S, $pa)) {
			$r .= $i . $ITEM_SPLITTER;
		}

		close(S);
	}

	if($r =~ /$ITEM_SPLITTER$/) {
		$r = substr($r, 0, length($r) - 1);
	}

	return $r;
}

sub softGetInstalled {
	my ($arg) = @_;

	my $r = "";
	my $p = "1";

	#
	# Fetch installed software list using dpkg or rpm
	#

	my @s = `WIDTH=1000 dpkg-query -W -f='\${Package}\t\${Version}\t\${Installed-Size}\t\${Homepage}\n' 2>/dev/null`;

	if(!@s) {
		$p = "2";

		@s = `WIDTH=1000 rpm -qa --queryformat '%{NAME}\t%{VERSION}\t%{SIZE}\t%{URL}\n' 2>/dev/null`;
	}

	if(@s) {
		foreach my $s (@s) {
			if($p == 2) {
				my @i = split(/\t/, $s);

				$i[2] = int($i[2] / 1000);

				$s = join("\t", @i);
			}

			$s =~ s/\r+$|\n+$//g;
			$s =~ s/\t/$ITEM_SEPARATOR/g;

			$r .= $p . $ITEM_SEPARATOR . $s . $ITEM_DELIMITER;
		}

		if($r =~ /$ITEM_DELIMITER$/) {
			$r = substr($r, 0, length($r) - 1);
		}
	}
	else {
		#
		# If dpkg and rpm are unavailable, try alternate method (Solaris)
		#

		@s = `WIDTH=1000 pkginfo -i 2>/dev/null`;

		if(@s) {
			$p = 4;

			foreach my $newLine (@s) {
				if($newLine =~ /^#|^\r|^\n/) {
					next;
				}

				my @newKey = split(/\s+/, $newLine, 3);

				$newKey[1] = cleanString({ string => $newKey[1] });
				$newKey[2] = cleanString({ string => $newKey[2] });

				$r .= $p . $ITEM_SEPARATOR . $newKey[1] . ", " . $newKey[2] . "" . $ITEM_SEPARATOR . "" . $ITEM_SEPARATOR . "" . $ITEM_SEPARATOR . "" . $ITEM_DELIMITER;
			}

			if($r =~ /$ITEM_DELIMITER$/) {
				$r = substr($r, 0, length($r) - 1);
			}
		}
		else {
			#
			# If pkginfo is unavailable, try alternate method (MacOSX)
			#

			$p = 3;

			@s = `ls -d /Applications/*.app 2>/dev/null`;

			foreach my $s (@s) {
				$s = cleanString({ string => $s });

				my @l = split(/\s+/, `du -sk "$s" 2>/dev/null`);

				$s =~ s/^\/.*\///;
				$s =~ s/\.app$//i;

				$r .= $p . $ITEM_SEPARATOR . $s . $ITEM_SEPARATOR . "" . $ITEM_SEPARATOR . $l[0] . $ITEM_SEPARATOR . "" . $ITEM_DELIMITER;
			}

			if($r =~ /$ITEM_DELIMITER$/) {
				$r = substr($r, 0, length($r) - 1);
			}
		}
	}

	return $r;
}

sub termNull {
	my ($arg) = @_;

	return "";
}

sub nodeInitNames {
	my ($arg) = @_;

	my %newDist = (
		"id" => "", "release" => "", "codename" => "", "description" => ""
	);

	my @newKeys = (
		"DISTRIB_ID", "DISTRIB_RELEASE", "DISTRIB_CODENAME", "DISTRIB_DESCRIPTION"
	);

	my @newName = (
		"/etc/debian_release", "/etc/debian_version", "/etc/fedora-release", "/etc/gentoo-release", "/etc/mandrake-release",
		"/etc/redhat-release", "/etc/redhat_version", "/etc/slackware-release", "/etc/slackware-version",
		"/etc/sun-release", "/etc/SUSE-release", "/etc/UnitedLinux-release", "/etc/yellowdog-release"
	);

	my @newDesc = (
		"Debian release", "Debian version", "Fedora release", "Gentoo release", "Mandrake release",
		"Red Hat release", "Red Hat version", "Slackware release", "Slackware version",
		"Sun JDS release", "Novell SuSE release", "United Linux release", "Yellow Dog release"
	);

	#
	# Fetch host name and such
	#

	my $st = `hostname 2>/dev/null | cut -f 1 -d '.'`;
	$nodeData{"node"} = cleanString({ string => $st });

	if($nodeData{"node"} eq "") {
		$st = `uname -n 2>/dev/null | cut -f 1 -d '.'`;
		$nodeData{"node"} = cleanString({ string => $st });

		if($nodeData{"node"} eq "") {
			$st = `cat /proc/sys/kernel/hostname 2>/dev/null | cut -f 1 -d '.'`;
			$nodeData{"node"} = cleanString({ string => $st });
		}
	}

	$st = `domainname 2>/dev/null`;
	$nodeData{"domain"} = cleanString({ string => $st });

	if($nodeData{"domain"} eq "") {
		$st = `hostname -d 2>/dev/null`;
		$nodeData{"domain"} = cleanString({ string => $st });

		if($nodeData{"domain"} eq "") {
			$st = `cat /proc/sys/kernel/domainname 2>/dev/null`;
			$nodeData{"domain"} = cleanString({ string => $st });
		}
	}

	if($nodeData{"domain"} =~ /^$nodeData{"node"}\./) {
		$nodeData{"domain"} =~ s/^$nodeData{"node"}\.//;
	}

	$st = `uname -s 2>/dev/null`;
	$nodeData{"system"} = cleanString({ string => $st });

	if($nodeData{"system"} eq "") {
		$st = `cat /proc/sys/kernel/ostype 2>/dev/null`;
		$nodeData{"system"} = cleanString({ string => $st });

		if($nodeData{"system"} eq "") {
			$st = $^O;
			$nodeData{"system"} = cleanString({ string => $st });
			$nodeData{"system"} = ucfirst($nodeData{"system"});
		}
	}

	$st = `uname -r 2>/dev/null`;
	$nodeData{"release"} = cleanString({ string => $st });

	if($nodeData{"release"} eq "") {
		$st = `cat /proc/sys/kernel/osrelease 2>/dev/null`;
		$nodeData{"release"} = cleanString({ string => $st });
	}

	$st = `uname -m`;
	$nodeData{"machine"} = cleanString({ string => $st });

	#
	# Fetch distribution name using linux specific method
	#

	if(open(FILE, "/etc/lsb-release")) {
		while(my $newLine = <FILE>) {
			if($newLine =~ /^#|^\r|^\n/) {
				next;
			}

			my @newKey = split('=', $newLine, 2);

			$newKey[0] = cleanString({ string => $newKey[0] });

			for(my $i = 0; $i < @newKeys; $i++) {
				if($newKeys[$i] =~ /^$newKey[0]/i) {
					$newKey[1] = cleanString({ string => $newKey[1] });

					if($newKeys[$i] =~ /^$newKeys[0]/i) {
						$newDist{"id"} = $newKey[1];
					}
					elsif($newKeys[$i] =~ /^$newKeys[1]/i) {
						$newDist{"release"} = $newKey[1];
					}
					elsif($newKeys[$i] =~ /^$newKeys[2]/i) {
						$newDist{"codename"} = $newKey[1];
					}
					elsif($newKeys[$i] =~ /^$newKeys[3]/i) {
						$newDist{"description"} = $newKey[1];
					}

					last;
				}
			}
		}

		if($newDist{"id"} ne "" && $newDist{"release"} ne "" && $newDist{"codename"} ne "") {
			$nodeData{"distribution"} = $newDist{"id"} . " " . $newDist{"release"} . " (" . $newDist{"codename"} . ")";
		}

		close(FILE);
	}

	if($nodeData{"distribution"} eq "") {
		for(my $i = 0; $i < @newName; $i++) {
			if(open(FILE, $newName[$i])) {
				while(my $newLine = <FILE>) {
					if($newLine =~ /^#|^\r|^\n/) {
						next;
					}

					$newLine = cleanString({ string => $newLine });

					$nodeData{"distribution"} = $newDesc[$i] . " " . $newLine;

					last;
				}

				close(FILE);

				last;
			}
		}
	}

	#
	# If distribution name is unavailable, try alternate method (Solaris)
	#

	if($nodeData{"distribution"} eq "") {
		if(open(FILE, "/etc/release")) {
			while(my $newLine = <FILE>) {
				if($newLine =~ /^#|^\r|^\n/) {
					next;
				}

				$nodeData{"distribution"} = cleanString({ string => $newLine });

				last;
			}

			close(FILE);
		}
	}

	#
	# If distribution name is unavailable, try alternate method (MacOSX)
	#

	if($nodeData{"distribution"} eq "") {
		my @l = `/usr/sbin/system_profiler -detailLevel full SPSoftwareDataType 2>/dev/null`;

		foreach my $newLine (@l) {
			if($newLine =~ /^#|^\r|^\n/) {
				next;
			}

			my @k = split(':', $newLine, 2);

			$k[0] = cleanString({ string => $k[0] });

			if($k[0] =~ /^System Version/) {
				$nodeData{"distribution"} = cleanString({ string => $k[1] });

				last;
			}
		}
	}

	#
	# Fetch user id, gecos and homedir
	#

	$st = `id -nu 2>/dev/null`;
	$nodeData{"useruid"} = cleanString({ string => $st });

	$st = `id -ng 2>/dev/null`;
	$nodeData{"usergrp"} = cleanString({ string => $st });

	my @st = getpwnam($nodeData{"useruid"});

	$st[6] =~ s/,+$//g;

	$nodeData{"usergecos"} = cleanString({ string => $st[6] });
	$nodeData{"userhomedir"} = cleanString({ string => $st[7] });

	return "";
}
