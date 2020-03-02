while getopts ":n:m:a:" o; do
    case "${o}" in
        n)
            n=${OPTARG}
            ;;
        m)
            m=${OPTARG}
            ;;
        a)
            a=${OPTARG}
            ;;
    esac
done

find -type f -name "$m" -mtime -$n > list_files
tar -cvf "$a".tar -T list_files

