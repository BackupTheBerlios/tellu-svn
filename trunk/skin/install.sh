#!/bin/sh

ANSWER=""
STEP=1
STEPS=8

warn() {
	echo "WARN: $1"
}

erhe() {
	echo "FATAL: $1"
	echo ""

	exit 1
}

ask() {
	while(true == 0); do
		echo -n "$1"

		read ANSWER

		if [ "$?" != 0 ]; then
			echo ""
			erhe "Something went wrong while trying to read input. Abort."
		elif [ "$ANSWER" = "" ]; then
			echo ""
			echo "Empty input is not satisfied. Please try again."
			echo ""
		else
			break
		fi
	done
}

step() {
	echo "------------------------------------------------------------------------------"
	echo "STEP $STEP/$STEPS - $1"
	echo "------------------------------------------------------------------------------"

	STEP=$(($STEP+1))
}

#
# Check that required tools exists.
#

for i in awk chmod chown cp cut find grep id mkdir perl sed tr; do
	which $i >/dev/null 2>&1

	if [ "$?" != 0 ]; then
		erhe "Cannot find required executable '$i'. Abort."
	fi
done

#
# Display banner.
#

echo ""
echo "------------------------------------------------------------------------------"
echo ""
echo "This is Tellu Skin installer v3.0.0"
echo "Copyright (c) 2010, Jani Salonen. All Rights Reserved."
echo ""
echo "------------------------------------------------------------------------------"
echo ""
echo "Welcome to Tellu Skin installer. Installer asks you a few questions before it"
echo "actually installs the Skin. Here you need some basic knowledge about unix"
echo "system, as well as you need root privileges for installer to copy Skin files"
echo "on disk. You should have working Tellu client/server environment installed"
echo "before you install Tellu Skin."
echo ""
echo "Tellu Skin requires CGI and Socket Perl modules. Please make sure that you"
echo "have these modules installed before proceeding, although they are almost for"
echo "sure already supplied by your Perl distribution. At any time you can cancel"
echo "the installation process by pressing <ctrl-c>."
echo ""
echo "Press <enter> to continue."

read dummy

#
# Check perl.
#

step "Perl compiler"

echo ""
echo "First we need to find out where your Perl executable resides, as Tellu Skin is"
echo "written in Perl. Installer has found:"
echo ""

PERL=`which perl 2>/dev/null`

echo $PERL

echo ""
echo "Press <enter> to use Perl above, or give alternate below."
echo ""

while(true == 0); do
	echo -n "Enter alternate Perl or press <enter> to accept default: "

	read APERL

	if [ "$?" != 0 ]; then
		echo ""
		erhe "Something went wrong while trying to read input. Abort."
	elif [ "$APERL" = "" ]; then
		echo ""

		break
	elif [ -r "$APERL" ]; then
		echo ""

		PERL=$APERL

		break
	else
		echo ""
		warn "'$APERL' does not exists. Please try again."
		echo ""
	fi
done

#
# Check directory for files.
#

step "Installation directory"

echo ""
echo "Choose directory where to install Skin files. This directory must reside"
echo "outside from your www-root for security issues. That directory will be created"
echo "if it does not exists already. '/usr/local/tellu_skin' is always a good"
echo "choice."
echo ""

ask "Enter installation directory: "

echo ""

INSTDIR=$ANSWER

#
# Check apache and its user.
#

step "File ownerships"

echo ""
echo "Owner of the Tellu Skin files must be set to the same user which runs your"
echo "web server."

HTTPD=""

for i in apachectl apache apache2 httpd; do
	HTTPD=`which $i 2>/dev/null`

	if [ "$HTTPD" != "" ]; then
		break
	fi
done

if [ "$HTTPD" != "" ]; then
	$HTTPD -v 2>/dev/null | grep -i Apache >/dev/null 2>&1

	if [ "$?" = 0 ]; then
		HTTPR=`$HTTPD -V 2>/dev/null | grep HTTPD_ROOT | cut -f 2 -d '=' | tr -d '"'`
		HTTPC=`$HTTPD -V 2>/dev/null | grep SERVER_CONFIG_FILE | cut -f 2 -d '=' | tr -d '"'`

		HTTPU=`grep -w ^User $HTTPR/$HTTPC 2>/dev/null | awk '{print $2}'`
		HTTPG=`grep -w ^Group $HTTPR/$HTTPC 2>/dev/null | awk '{print $2}'`

		if [ "$HTTPU" = "" ] || [ "$HTTPG" = "" ]; then
			HTTPD=""
		else
			echo ""
			echo "Installer has detected that your web server runs with following privileges:"
			echo ""
			echo "User: $HTTPU"
			echo "Group: $HTTPG"
			echo ""
			echo "Do you want to set ownership of Tellu Skin files to user and group above?"
			echo ""

			ask "Please answer either Y(es) or N(o): "

			if [ "$ANSWER" = "n" ] || [ "$ANSWER" = "N" ] || [ "$ANSWER" = "no" ] || [ "$ANSWER" = "No" ]; then
				HTTPD=""
			elif [ "$ANSWER" = "y" ] || [ "$ANSWER" = "Y" ] || [ "$ANSWER" = "yes" ] || [ "$ANSWER" = "Yes" ]; then
				HTTPD="1"
			else
				echo ""
				warn "As answer is not either Y(es) or N(o), assumig no."

				HTTPD=""
			fi
		fi
	fi
fi

if [ "$HTTPD" = "" ]; then
	echo ""
	echo "Please specify the user and that users' group whose privileges your web server"
	echo "runs. Owner of Tellu Skin files will be changed to that user and group, so"
	echo "that your web server has permissions to read them. This user is usually apache,"
	echo "httpd, www-data or something else, but if you are unsure, you need to check"
	echo "this before proceeding."
	echo ""

	while(true == 0); do
		ask "Please give user name whose privileges your web server runs: "

		id $ANSWER >/dev/null 2>&1

		if [ "$?" != 0 ]; then
			echo ""
			warn "User '$ANSWER' does not exists. Please try again."
			echo ""
		else
			break
		fi
	done

	HTTPU=$ANSWER

	ask "Please give group name whose privileges your web server runs: "

	HTTPG=$ANSWER
fi

echo ""

#
# Check telskind variables.
#

step "Variables for telskind"

echo ""
echo "Some variables need to be set in Tellu Skin configuration so it can"
echo "successfully connect to its server, telskind. First we need the hostname where"
echo "telskind is running."

SKINH=""

for i in /etc /usr/etc /usr/local/etc /usr/local/tellu/etc /usr/local/tellu3/etc /opt/etc /opt/tellu/etc /opt/tellu3/etc; do
	if [ -r "$i/telskind.conf" ]; then
		echo ""
		echo "Installed has detected that there is '$i/telskind.conf', so"
		echo "probably telskind is installed on localhost."
		echo ""
		echo "Press <enter> to use localhost, or give alternate host name below."
		echo ""

		SKINH="localhost"

		while(true == 0); do
			echo -n "Enter alternate host name or press <enter> to accept default: "

			read ASKINH

			if [ "$?" != 0 ]; then
				echo ""
				erhe "Something went wrong while trying to read input. Abort."
			elif [ "$ASKINH" = "" ]; then
				echo ""

				break
			else
				echo ""

				SKINH=$ASKINH

				break
			fi
		done

		break
	fi
done

if [ "$SKINH" = "" ]; then
	echo ""
	echo "Please type host name where telskind server is running. If you are installing"
	echo "Tellu Skin on the same machine where telskind is running, just type"
	echo "'localhost'."
	echo ""
	echo "Press <enter> when ready."
	echo ""

	ask "Enter host name where telskind runs: "

	SKINH=$ANSWER
fi

echo "Now we need to know the port number which telskind listens."

SKINP=""

for i in /etc /usr/etc /usr/local/etc /opt/tellu/etc /opt/tellu3/etc /home/salojan/source/tellu/current/src/server/telskind; do
	if [ -r "$i/telskind.conf" ]; then
		SKINP=`grep '^listen_port' "$i/telskind.conf" 2>/dev/null | cut -f 2 -d '=' | tr -d ' ' | tr -d '\t'`

		if [ "$SKINP" = "" ]; then
			SKINP="1702"
		fi

		echo ""
		echo "Installed has detected that the port is '$SKINP'."
		echo ""
		echo "Press <enter> to use $SKINP, or give alternate port number below."
		echo ""

		while(true == 0); do
			echo -n "Enter alternate port number or press <enter> to accept default: "

			read ASKINP

			if [ "$?" != 0 ]; then
				echo ""
				erhe "Something went wrong while trying to read input. Abort."
			elif [ "$ASKINP" = "" ]; then
				echo ""

				break
			else
				echo ""

				SKINP=$ASKINP

				break
			fi
		done

		break
	fi
done

if [ "$SKINP" = "" ]; then
	echo ""
	echo "Please type port number which telskind server is listening. By default this is"
	echo "1702."
	echo ""
	echo "Press <enter> when ready."
	echo ""

	ask "Enter port number which telskind listens: "

	SKINP=$ANSWER
fi

echo "And last but not least, we need the password for Skin to authenticate with"
echo "telskind. This password is in telskind's configuration, in parameter"
echo "'agent_password'. If installer is unable to detect it, you need to check"
echo "it out by yourself and input it when installer asks for it."

SKINW=""

for i in /etc /usr/etc /usr/local/etc /opt/tellu/etc /opt/tellu3/etc /home/salojan/source/tellu/current/src/server/telskind; do
	if [ -r "$i/telskind.conf" ]; then
		SKINW=`grep '^agent_password' "$i/telskind.conf" 2>/dev/null | cut -f 2 -d '=' | tr -d ' ' | tr -d '\t'`

		if [ "$SKINW" != "" ]; then
			echo ""
			echo "Installed has detected that the password is '<hidden, but detected>'."
			echo ""
			echo "Press <enter> to use detected password, or give alternate below."
			echo ""

			while(true == 0); do
				echo -n "Enter alternate password or press <enter> to accept default: "

				read ASKINW

				if [ "$?" != 0 ]; then
					echo ""
					erhe "Something went wrong while trying to read input. Abort."
				elif [ "$ASKINW" = "" ]; then
					echo ""

					break
				else
					echo ""

					SKINW=$ASKINW

					break
				fi
			done
		fi

		break
	fi
done

if [ "$SKINW" = "" ]; then
	echo ""
	echo "Please type password which telskind is using for authenticating with Skin."
	echo ""
	echo "Press <enter> when ready."
	echo ""

	ask "Enter telskind's password: "

	SKINW=$ANSWER
fi

step "Preview installation information"

echo ""
echo "Please check that all information gathered is correct. Press <enter> for"
echo "installer to continue installation. No modifications are yet made, this is"
echo "last chance to cancel installation. If you want to abort or start over, press"
echo "<ctrl-c> now."
echo ""

echo "perl to use: $PERL"
echo ""
echo "installation directory: $INSTDIR"
echo "owner of Skin files: $HTTPU:$HTTPG"
echo ""
echo "telskind host name: $SKINH"
echo "telskind port: $SKINP"
echo "telskind password: <hidden>"
echo ""

echo "Press <enter> to continue."

read dummy

step "Starting installation"

echo ""

if [ ! -d "$INSTDIR" ]; then
	echo "Creating directory '$INSTDIR'"

	mkdir -p "$INSTDIR"

	if [ "$?" != 0 ]; then
		erhe "Creating directory '$INSTDIR' failed. Abort."
	fi
fi

echo "Copying Skin files to '$INSTDIR'"

for i in cgi-bin files html templates; do
	cp -R "./$i" "$INSTDIR/"

	if [ "$?" != 0 ]; then
		erhe "Copying Skin '$i' files to '$INSTDIR' failed. Abort."
	fi
done

echo "Setting file ownerships in '$INSTDIR'"

chown -R $HTTPU:$HTTPG "$INSTDIR"

if [ "$?" != 0 ]; then
	erhe "Setting file ownerships for '$INSTDIR' failed. Abort."
fi

echo "Setting file permissions in '$INSTDIR'"

find "$INSTDIR" -type d | while read a; do
	chmod 0700 "$a"

	if [ "$?" != 0 ]; then
		erhe "Setting file permissions for '$INSTDIR/$a' failed. Abort."
	fi
done

find "$INSTDIR" -type f | while read a; do
	chmod 0600 "$a"

	if [ "$?" != 0 ]; then
		erhe "Setting file permissions for '$INSTDIR/$a' failed. Abort."
	fi
done

chmod 0700 "$INSTDIR"/cgi-bin/*.pl

if [ "$?" != 0 ]; then
	erhe "Setting file permissions for '$INSTDIR/cgi-bin' failed. Abort."
fi

echo "Setting interpreter for scripts in '$INSTDIR/cgi-bin'"

ls "$INSTDIR"/cgi-bin/*.js "$INSTDIR"/cgi-bin/*.lib "$INSTDIR"/cgi-bin/*.pl | while read a; do
	sed -i -e "s|^#!/usr/bin/perl|#!$PERL|" "$a"

	if [ "$?" != 0 ]; then
		erhe "Setting interpreter for '$INSTDIR/$a' failed. Abort."
	fi
done

echo "Setting variables for '$INSTDIR/cgi-bin/variables.lib'"

sed -i -e "s|^\$CONFIG_SERVER_NAME = .*$|\$CONFIG_SERVER_NAME = \"$SKINH\";|" "$INSTDIR"/cgi-bin/variables.lib

if [ "$?" != 0 ]; then
	erhe "Setting variables for '$INSTDIR/cgi-bin/variables.lib' failed. Abort."
fi

sed -i -e "s|^\$CONFIG_SERVER_PORT = .*$|\$CONFIG_SERVER_PORT = $SKINP;|" "$INSTDIR"/cgi-bin/variables.lib

if [ "$?" != 0 ]; then
	erhe "Setting variables for '$INSTDIR/cgi-bin/variables.lib' failed. Abort."
fi

sed -i -e "s|^\$CONFIG_SERVER_PASSWORD = .*$|\$CONFIG_SERVER_PASSWORD = \"$SKINW\";|" "$INSTDIR"/cgi-bin/variables.lib

if [ "$?" != 0 ]; then
	erhe "Setting variables for '$INSTDIR/cgi-bin/variables.lib' failed. Abort."
fi

sed -i -e "s|^\$DIR_TEMPLATE = .*$|\$DIR_TEMPLATE = \"$INSTDIR/templates\";|" "$INSTDIR"/cgi-bin/variables.lib

if [ "$?" != 0 ]; then
	erhe "Setting variables for '$INSTDIR/cgi-bin/variables.lib' failed. Abort."
fi

sed -i -e "s|^\$DIR_UPLOAD = .*$|\$DIR_UPLOAD = \"$INSTDIR/files\";|" "$INSTDIR"/cgi-bin/variables.lib

if [ "$?" != 0 ]; then
	erhe "Setting variables for '$INSTDIR/cgi-bin/variables.lib' failed. Abort."
fi

echo ""

step "Testing installation"

echo ""
echo "Testing that every script compiles correctly..."

ls "$INSTDIR"/cgi-bin/*.js "$INSTDIR"/cgi-bin/*.lib "$INSTDIR"/cgi-bin/*.pl | while read a; do
	$PERL -c "$a" >/dev/null 2>&1

	if [ "$?" != 0 ]; then
		warn "'$a' has some troubles."
	fi
done

echo ""

step "Installation is complete"

echo ""
echo "Tellu Skin installation is now complete."
echo ""
echo "As a last step you need to tune your web server config as follows:"
echo ""
echo "Point html-root to $INSTDIR/html"
echo "Point cgi-bin to $INSTDIR/cgi-bin"
echo ""
echo "Please check Apache's documentation how to modify those."
echo ""
echo "Skin has two built-in user accounts, 'admin' and 'guest', both's passwords are"
echo "'admin' and 'guest', respectively. Use either one first time you log on to Skin"
echo "if your Skin server, telskind, does not use LDAP authentication. If it does,"
echo "log on using your LDAP account."
echo ""
echo "Have fun!"
echo ""

exit 0
