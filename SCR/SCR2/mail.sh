SUBJECT="Temacik"
EMAIL="adresat@domena.com"
EMAILBODY="/home/ajozefcz/SCR/SCR2/mail.txt"
input="/home/ajozefcz/SCR/SCR2/maile.txt"
ATT="/home/ajozefcz/SCR/SCR2/ofer/pliki1.pdf"
FILES="home/ajozefcz/SCR/SCR2/ofer/"


for files in ofer/pliki*.pdf
do
	att="$att -a ${files}"
done

while IFS= read -r line
do
EMAIL="$line"
echo "$EMAIL"

mail -s "$SUBJECT"  $att  "$EMAIL" < $EMAILBODY
#mail -s "$SUBJECT"  -a "$ATT" "$EMAIL" < $EMAILBODY
done < "$input"
echo "done"
