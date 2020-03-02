#/!/bash/bin
# ARG roz lub maska, modyfikacja do  N dni, nazwa archiwum
MASK="*$1"
DAYS="-$2"
NAME="$3.tar.gz"
#LISTA= "/home/ajozefcz/SCR/SCR2/lista.txt"
echo "$MASK"
find -type f -name "$MASK" -mtime $DAYS  > lista.txt
tar -cvf "$NAME" -T lista.txt

