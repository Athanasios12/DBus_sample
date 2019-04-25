#!/bin/sh
sudo echo "DBus Cpp lib deployment..."
libCheck="$(ldconfig -p | grep libCppDBusLib)"
if [ -z "$libCheck" ]
then
	echo "Library not loaded, performing deployment..."
	sudo cp libCppDBusLib.so /usr/lib
	chmod 0755 /usr/lib/libCppDBusLib.so
	ldconfig
	libCheck="$(ldconfig -p | grep libCppDBusLib)"
	if [ -z "$libCheck" ]
	then
		echo "Library deployment failed!"
	else
		echo "Library loaded successfully!"
	fi
else
	echo "Library already loaded!"
fi	
