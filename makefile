G++_FLAGS= 

# can 'make scheduler' to only compile the schedular, can 'make tree' to only compile the RB tree or just 'make' to compile both
all: scheduler tree
scheduler:
	g++ ${G++_FLAGS} VTwo.cpp  -o bin/VTwo.out
tree:
	g++ ${G++_FLAGS} RBTree.cpp -o bin/RBTree.out


clean:
	if [ -f bin/VTwo.out ]; then rm bin/VTwo.out; fi
	if [ -f bin/RBTree.out ]; then rm bin/RBTree.out; fi

# create a zip file by using 'make archive' for the project, removing the old one if it exists
archive:
	if [ -f kruegena_kromreve_webrjr.zip ]; then rm kruegena_kromreve_webrjr.zip; fi
	zip kruegena_kromreve_webrjr.zip *.cpp *.h makefile *.txt
