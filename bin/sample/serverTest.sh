#!/bin/bash
echo "Launch first server"
#launch server app
./DBusServer -i < pipe &
# $! correcponds to last job pid that was launched from this script
server_pid=$!
echo -e "\nLaunched server pid = $server_pid\n"
#sleep infinity > pipe &
#sleep_pid=$!
#test input to client
echo "20 30" > pipe
sleep 3 
echo "80 30" > pipe
sleep 3
echo -e "\nList the processes:\n"
ps
echo -e "\n-------\n"
echo "Killing first server"
kill $server_pid
sleep 6
echo "Creating new server"
./DBusServer -i < pipe &
server_pid=$!
echo -e "\nLaunched new server pid = $server_pid\n"
echo -e "\nList the processes:\n"
ps
sleep 6
echo "20 50" > pipe
sleep 6
echo "killing new server"
kill $server_pid

#kill $sleep_pid
