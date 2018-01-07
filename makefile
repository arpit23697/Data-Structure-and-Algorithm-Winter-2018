CC = g++
OBJS = main.o Graph.o vector.o stack.o

a.out : ${OBJS}
	${CC} ${OBJS} -g

main.o: main.cpp
	${CC} -c -std=c++11 main.cpp -g

Graph.o : Graph.cpp
	${CC} -c -std=c++11 Graph.cpp -g

vector.o : vector.cpp
	${CC} -c -std=c++11 vector.cpp -g

stack.o : stack.cpp
	${CC} -c -std=c++11 stack.cpp -g

clean:
	\rm a.out *.o *.dot