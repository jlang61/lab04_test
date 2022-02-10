CXX_FLAG = --std=c++11

all: intbst testbst

intbst.o: instbst.h intbst.cpp
  g++ ${CXX_FLAG} -Wall -c  instbst.h intbst.cpp

testbst.o:  testbst.cpp intbst.cpp  intbst.h  intbst.o
  g++ ${CXX_FLAG} -Wall -c  testbst.cpp intbst.cpp  intbst.h

testbst:  testbst.o
  g++ ${CSS_FLAG} -Wall testbst.o -o  testbsst

clean:
  rm  intbst testbst