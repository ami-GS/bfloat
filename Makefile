default:
	c++ -std=c++17 -c bfloat_py.cc -o bfloat_py.o
	c++ -shared -W1,-soname,libbfloat.so -o libbfloat.so bfloat_py.o
