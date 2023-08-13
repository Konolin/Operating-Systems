#!/bin/bash

# Löschen Sie aus den ersten 30 Zeilen der Dateien diejenigen, die einen 
# bestimmten Text enthalten. Sowohl die Dateien als auch der angegebene 
# Text werden als Parameter in der Befehlszeile angegeben. Der Text wird 
# der erste Parameter sein. Die Dateien werden nicht geändert, aber ihr
# verarbeiteter Inhalt wird in der Standardausgabe angezeigt.

if [ $# -lt 2 ]; then
	echo "Sie mussen genau 2 Parameter eingeben!"
	exit
else
	# haltet den sttring fest
	str_del=$1
	# shift die Parameterliste nach links
	shift
	
	# durchquert alle Parameter (files)
	for file in "$@"; do
		# entfernt die Zeilen die str_del enthalten
		sed "1,30 {/$str_del/d}" $file
	done
fi

