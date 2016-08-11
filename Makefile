
all:
	g++ main.cpp window.cpp window.h  sens.cpp sens.h  -o amihot -lsensors -lncurses -w
	

install:
	ln -s ${PWD}/amihot /usr/bin/amihot

uninstall:
	rm /usr/bin/amihot

clean:
	rm ./amihot
