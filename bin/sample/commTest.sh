#!/bin/bash
echo "Launch server client test"
#launch server app
./DBusServer &
# $! correcponds to last job pid that was launched from this script
server_pid=$!
#create pipe for sending client input
mkfifo clientServer.pipe
#start client process and bind it with created pipe
./DBusClient -i < clientServer.pipe &
client_pid=$!
#keep pipe alive after terminal echo's the pipe - otherwise DBusClient is 
#terminated on it's own
sleep infinity > clientServer.pipe &
sleep_pid=$!
#test input to client
echo "20 30" > clientServer.pipe
sleep 1 
echo "80 30" > clientServer.pipe
sleep 1 
kill $server_pid
kill $client_pid
kill $sleep_pid
#do it again 
./DBusServer &
# $! correcponds to last job pid that was launched from this script
server_pid=$!
#start client process and bind it with created pipe
./DBusClient -i < clientServer.pipe &
client_pid=$!
#keep pipe alive after terminal echo's the pipe - otherwise DBusClient is 
#terminated on it's own
sleep infinity > clientServer.pipe &
sleep_pid=$!
#test input to client
sleep 0.5
echo "20 30" > clientServer.pipe
sleep 1 
echo "80 30" > clientServer.pipe
sleep 1 
kill $server_pid
kill $client_pid
kill $sleep_pid
rm clientServer.pipe
