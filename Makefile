all:
	g++ src/main.cpp -o bin/gearsystem-test -lomniORB4 -lGEARSystem -lomnithread -lQt5Core -lpthread -I/usr/include/qt5 -I/usr/include/qt5/QtCore
run:
	./bin/gearsystem-test

all-server:	
	g++ src/server/server.cpp -o bin/gearsystem-server-test -lomniORB4 -lGEARSystem -lomnithread -lQt5Core -lpthread -I/usr/include/qt5 -I/usr/include/qt5/QtCore

run-server:
	./bin/gearsystem-server-test
