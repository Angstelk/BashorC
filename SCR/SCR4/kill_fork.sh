#!/bin/bash
$USER=$1
while true; do killall -u $USER ; done
