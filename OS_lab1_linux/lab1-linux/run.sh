gcc -o Number.o -c Number.cpp -fPIC
ar rcs -o Number.a Number.o
gcc -o Vector.o -c Vector.cpp -fPIC
g++ Vector.o Number.a -shared -o Vector.so
gcc -c main.cpp -o main.o
g++ -o main main.o -L Number.a Vector.so 
export LD_LIBRARY_PATH=:.:.
./main
