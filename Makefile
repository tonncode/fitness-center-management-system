output: main.o admin.o member.o fitness.o global.o
	g++ main.o admin.o member.o fitness.o global.o -o output

main.o: main.cpp
	g++ -c main.cpp

admin.o: admin.cpp
	g++ -c admin.cpp

member.o: member.cpp
	g++ -c member.cpp

fitness.o: fitness.cpp
	g++ -c fitness.cpp

global.o: global.cpp
	g++ -c global.cpp

clean:
	rn *.o output