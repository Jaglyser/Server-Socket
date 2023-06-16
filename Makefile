server : 
	clang++ src/main.cpp src/server.cpp src/runner.cpp -std=c++20 -o server

clean :
	rm server

