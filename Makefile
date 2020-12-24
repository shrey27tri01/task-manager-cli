app: 
	g++ -c -std=c++11 -Wall todo.cpp -o todo.o
	g++ todo.o -o todo.out

test: app
	npm run test

clean:
	rm -f todo.o todo.out

install:
	npm install
