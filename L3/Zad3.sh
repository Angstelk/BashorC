#!/bin/bash

echo "Uruchomienie potoków cat | cat | cat | ./gen.sh" 
cat | cat | cat | ./gen.sh &
echo "Hierarchia procesów dla użytkownika jkopala [...]:"
ps -u jkopala f l

pidGen = $(grep gen.sh)
sleep 20s

kill -Kill $pidGen
