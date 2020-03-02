#!/bin/bash

LC_ALL=C

day_week=`date +%u`
#echo $day_week
if [[ $day_week -ge 5 ]]
then
	echo "Weekend! :)"
else 
	echo "Dzień Roboczy :<"
fi
