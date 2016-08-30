
all:
	g++ main.cpp window.cpp window.h  sens.cpp sens.h  -o amihot -lsensors -lncurses -w
	

install:
	cp ${PWD}/amihot /usr/bin/

uninstall:
	rm /usr/bin/amihot

clean:
	rm ./amihot

reinstall: uninstall install
