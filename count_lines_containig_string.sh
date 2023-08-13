#!/bin/bash

if [ $# -ne 2 ]
then
	echo "Sie mussen 2 Parameter eingeben!"
	exit
fi

count=$(grep -c "$2" $1)

echo $count
