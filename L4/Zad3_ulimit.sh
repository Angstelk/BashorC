#!/bin/bash
proc_limit=10
echo -e "\e[39mUstawienie limitu procesów na ilość $proc_limit \e[91m[...]"
ulimit -u 10
echo -e "\e[39mUstawiono limit procesów na: $proc_limit \e[92m[OK!]"

echo -e "\e[39mRekurencyjne uruchamianie procesów \e[33m(Fork Bomb) \e[91m[...]"
./Zad3_forkbomb.sh &
echo -e "\e[39mUruchomiono rekrurencyjne uruchamianie procesów \e[33m(fork Bomb) \e[92m[OK!]\e[39m"

