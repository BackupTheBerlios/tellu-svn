#!/bin/sh

kill `cat /tmp/tellud.pid.1700`
./tellud-Linux-x86_64 -c ./tellud.conf
