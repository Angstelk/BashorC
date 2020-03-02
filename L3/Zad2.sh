#!/bin/bash
echo "Zadanie 2:"
echo "Kaskadowe uruchamianie trzech procesów (skryptów) A, B, C [...]"
./A.sh &
echo "Procesy A, B, C zostały uruchomione w tle [ok]"
echo "Hierarchia procesów dla użytkownika jkopala [...]:"
ps -u jkopala f l
echo "Oczekiwanie 15 sekund [...]"
sleep 15s
echo "Nastąpi zabicie procesu B [...]"
pidB=$(pgrep B.sh)
kill -KILL $pidB
echo "Zabito proces B :( [ok]"
echo "Hierarchia procesów dla użytkownika jkopala [...]:"
ps -u jkopala f l
echo "Zakończono [ok]"


