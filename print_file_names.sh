#!/bin/bash

cd $1

if [ $# -ne 1 ]
then
	echo "Sie mussen mindestens ein Parameter eingeben!"
	exit
else
	# druckt die Dateien nach der name
	ls -1
	echo " "

	# druckt die Dateien nach der letzten Zugriff
	ls -t -1
	echo " "

	# druckt die Dateien nach Bytegrosse
	ls -S -1
	echo " "
fi
