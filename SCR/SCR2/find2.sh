#/!/bash/bin
# ARG roz lub maska, modyfikacja do  N dni, nazwa archiwum
MASK="*$1"
DAYS="-$2"
NAME="$3.tar.gz"
LISTA= "/home/ajozefcz/SCR/SCR2/lista.txt"
export NAZWA_DOM="find2.tar.gz"
export MASK_DOM="*"
while  getopts ":n:m:a:" o; do
	case "${o}" in
		n)
			days=${OPTARG}
			echo "DNI : ${days} "
			;;
		m)
			name=${OPTARG}
			echo "NAZWA : ${name} "
			;;
		a)
			a=${OPTARG}
			echo "MASKA :  ${a} "
			;;
		*)
			echo "Nie wiadomo"
			;;
	  esac
done
shift $((OPTIND-1))
if [[ -z "$days" ]]; then
	echo "Podaj liczbę dni"
	read days
fi
if [[ -z "$name" ]]; then
	name=NAZWA_DOM
fi
if [[ -z "$a" ]]; then
	MASK=MASK_DOM
fi
MASK="*$a"
DAYS="-$days"
NAME="$name.tar.gz"
find -type f -name "$MASK" -mtime $DAYS  > lista.txt
tar -cvf "$NAME" -T lista.txt
