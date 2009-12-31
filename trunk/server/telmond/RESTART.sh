#!/bin/sh

kill `cat /tmp/telmond.pid.1701`
./telmond-Linux-x86_64 -c ./telmond.conf
