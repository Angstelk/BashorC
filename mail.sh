#!/bin/bash
SUBJECT="Temat wiadomosci"
EMAIL="adresat@domena.com"
EMAILBODY="/home/apeiron/SCR/mail.txt"
input="/home/apeiron/SCR/maile.txt"
while IFS= read -r line
do
EMAIL="$line"
mail -s "$SUBJECT" "$EMAIL" < $EMAILBODY --attach="/home/apeiron/SCR/wyklad7.pdf"

done < "$input"
