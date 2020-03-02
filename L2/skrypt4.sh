#!/bin/bash

#email_path = $1
#msg_path = $2
#spec = $3

echo "Uruchomiono skrypt o nazwie $0"

for file in spec/spec*.pdf
do

	att="$att -a ${file}"
done

echo $att

for emails in $(cat adresy.txt)
do
	mail -s Oferta $att  $emails <<< tresc.txt	
done

echo "Zakończono działanie skryptu"
