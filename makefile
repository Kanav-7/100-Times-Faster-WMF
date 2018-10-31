main: *.cpp
	 g++ *.cpp  -o output `pkg-config --cflags --libs opencv`