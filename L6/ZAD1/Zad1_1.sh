#!/bin/bash

echo -e "\e[39mUruchomienie prostego programu iterującego zmienną (itloop1) \e[91m[...]"
./itloop1 &
echo -e "\e[39mUruchomiono \e[92m[OK!]"
echo -e "\e[39mUruchomienie programu \e[35m{TOP}\e[39m celem sprawdzenia obciążenia procesora przez program iterujący \e[91m[...]"
sleep 3s
top -u jkopala
echo -e "\e[39mUruchomiono \e[92m[OK!]\e[39m"

echo -e "\e[39mZabijanie wcześniejszego programu iterującego \e[91m[...]\e[39m"
pids=$(pgrep itloop1)
kill -9 $pids
echo -e "\e[39mZabito \e[92m[OK!]\e[39m"

sleep 1s

echo -e "\e[39mUruchomienie prostego programu iterującego zmienną z dodanym opóźnieniem (itloop2_delay) \e[91m[...]"
./itloop2_delay &
echo -e "\e[39mUruchomiono \e[92m[OK!]"
echo -e "\e[39mUruchomienie programu \e[35m{TOP}\e[39m celem sprawdzenia obciążenia procesora przez program iterujący \e[91m[...]"
sleep 3s
top -u jkopala
echo -e "\e[39mUruchomiono \e[92m[OK!]\e[39m"

echo -e "\e[39mZabijanie wcześniejszego programu iterującego \e[91m[...]\e[39m"
pids=$(pgrep itloop2_delay)
kill -9 $pids
echo -e "\e[39mZabito \e[92m[OK!]\e[39m"


echo - e"\e[39mUruchomienie programu iterującego z obsługą przechwytywania sygnałów (itloop3_signal) \e[91m[...]"
./itloop3_signal &
echo -e "\e[39mUruchomiono \e[92m[OK!]"
pid_it3=$(pgrep itloop3_signal)
echo -e "PID uruchomionego programu to \e[35m$pid_it3"
sleep 1s

echo -e "\e[39mWysłanie do programu sygnału \e[35m{SIGUSR2} \e[91m[...]\e[39m"
kill -SIGUSR2 $pid_it3
echo -e "\e[39mWysłano \e[92m[OK!]\e[39m"
sleep 1s

echo -e "\e[39mWysłanie do programu sygnału \e[35m{SIGUSR1} \e[91m[...]\e[39m"
kill -SIGUSR1 $pid_it3
echo -e "\e[39mWysłano \e[92m[OK!]\e[39m"
sleep 1s


echo -e "\e[39mWysłanie do programu sygnału \e[35m{SIGTERM} \e[91m[...]\e[39m"
kill -SIGTERM $pid_it3
echo -e "\e[39mWysłano \e[92m[OK!]\e[39m"
sleep 1s


echo -e "\e[39mWysłanie do programu sygnału \e[35m{SIGALRM} \e[91m[...]\e[39m"
kill -SIGALRM $pid_it3
echo -e "\e[39mWysłano \e[92m[OK!]\e[39m"
sleep 1s
