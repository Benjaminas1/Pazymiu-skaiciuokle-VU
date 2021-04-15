main: includes/functions.o includes/students.o
	g++ -o main main.cpp includes/functions.o includes/students.o
functions:
	g++ -c includes/functions.cpp
students:
	g++ -c includes/students.cpp
clean:
	rm *.o main