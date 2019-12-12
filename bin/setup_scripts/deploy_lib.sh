#!/bin/sh
sudo echo "DBus Cpp lib deployment..."
libCheck="$(ldconfig -p | grep libCppDBusLib)"
if [ ! -z "$libCheck" ]
then
	echo "Removing old lib"
	sudo rm /usr/lib/libCppDBusLib.so
fi
sudo cp libCppDBusLib.so /usr/lib
chmod 0755 /usr/lib/libCppDBusLib.so
cd /usr/lib/
ldconfig
libCheck="$(ldconfig -p | grep libCppDBusLib)"
if [ -z "$libCheck" ]
then
	echo "Library deployment failed!"
else
	echo "Library loaded successfully!"
fi
