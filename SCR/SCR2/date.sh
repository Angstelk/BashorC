#!/bin/bash
LC_ALL=C
date= date "+%u"
echo "$date";
if [[ $date -ge 5 ]] 
then 	echo "weekend"
else 	echo "praca"
fi
