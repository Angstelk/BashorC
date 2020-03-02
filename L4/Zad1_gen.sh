#!/bin/bash

i=1;

while [ $i -le 10 ] ; do
	echo `date -u`
	i=$[i + 1]
	sleep 1s
done
