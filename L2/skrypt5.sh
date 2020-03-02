#!/bin/bash

mask_form="*$1"
n_day="$2"
tar_name="$3"

find -type f  -name "$mask_form"  -mtime -$n_day > list_files
echo $list_files
tar -cvf $tar_name.tar -T  list_files




