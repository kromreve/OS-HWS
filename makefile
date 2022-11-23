G++_FLAGS= 


scheduler:
	g++ ${G++_FLAGS} main.cpp Queue.cpp -o bin/main.out

clean:
	if [ -f bin/main.out ]; then rm bin/main.out; fi

# create a zip file by using 'make archive' for the project, removing the old one if it exists
archive:
	if [ -f kruegena_kromreve_webrjr.zip ]; then rm kruegena_kromreve_webrjr.zip; fi
	zip kruegena_kromreve_webrjr.zip *.cpp *.h makefile *.txt
