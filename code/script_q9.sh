#/bin/bash

clear 
gcc client.c -o client
gcc  server_daemon.c -o  server

killall server
#netstat -npt | grep 54545 

./server
# netstat -t | grep 54545 

#On lance les 6 clients.
./client &
./client &
./client &
./client &
./client &
./client & 

ps -jH
# netstat -npt | grep 54545 

