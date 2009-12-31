#!/bin/sh

kill `cat /tmp/telskind.pid.1702`
./telskind-Linux-x86_64 -c ./telskind.conf
