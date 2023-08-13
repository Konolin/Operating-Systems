#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Sie mussen genau ein Patameter eingeben!"
	exit 
fi

file=$1
ent_zahlen=0
ent_keine_zahlen=0
sum=0

awk '{

	sum_temp=0  # Summe der Reihe
	nr_anz=0

	# durchquert alle Felder der Reihe 
	for (i=1; i<=NF; i++)

		# uberpruft ob es nur Zahlen gibt
		if ( $i ~ /^[0-9]+$/ ) {
			sum_temp+=$i
			nr_anz++
		}	

	# steigt der Anzahl/totale Summe
	if (nr_anz!=0) {
		ent_zahlen++
		sum+=sum_temp
	}
	else
		ent_keine_zahlen++

}END{

	# am Ende druckt die Losung
	print sum " " ent_zahlen ":" ent_keine_zahlen

}' $file
