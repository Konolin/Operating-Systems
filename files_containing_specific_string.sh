#!/bin/bash

# Zeigen Sie die Namen allen ".c"-Dateien in einem bestimmten Ordner an, der “define” enthält(#define).
# Der Ordner wird als Parameter in der Befehlszeile angegeben. Die Dateinamen werden in der Standardausgabesortiert
# (nach dem Namen) und einzeln in einer Zeileangezeigt.

cd $1

if [ $# -ne 1 ]
then
	echo "Sie mussen genau ein Parameter eingeben!"
	exit
else
	# -r durhquert alle Dateien aus $1 recursiv
	# -l druckt die Dateinamen
 	grep -r -l "#define" *.c
fi
