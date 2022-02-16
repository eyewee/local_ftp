#/bin/bash

clear 
gcc client.c -o client
gcc  server_parallele.c -o  server

# kill -9 $(lsof -t -i tcp:54545)
killall server
#netstat -npt | grep 54545 

./server
#netstat -t | grep 54545 

#On lance les 3 clients.
./client &
./client & 
./client & 

ps -jH
# netstat -npt | grep 54545 
