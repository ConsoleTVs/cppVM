all:
	g++ main.cpp -o main
release:
	g++ -Ofast main.cpp -o main.exe
