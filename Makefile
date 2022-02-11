CXX_FLAG	=	--std=c++11

all: testbst

testbst: testbst.o intbst.o 
  g++ ${CXX_FLAG} -o testbst testbst.o intbst.o

testbst.o: testbst.cpp
  g++ -c D${CXX_FLAG} testbst.cpp

intbst.o: intbst.cpp
  g++ -c ${CXX_FLAG} intbst.cpp

clean:
	rm	intbst.o testbst.o
