CC=gcc
CXX=g++
AR=ar cr
CXXFLAGS=-c -std=c++0x -fPIC
CCFLAGS=-c -Wall -Werror -fPIC
DLFLAGS=-L. -lpathfinder
LFLAGS=-fPIC
RBHEADERS=-I/home/usr/.rvm/rubies/ruby-2.1.5/include/ruby-2.1.0 -I/home/usr/.rvm/rubies/ruby-2.1.5/include/ruby-2.1.0/x86_64-linux

main: main.o pathfinder.o search_field.o findpath.o
	$(CXX) -o pathfinder main.o pathfinder.o search_field.o findpath.o

pf2: pf_so main_c.o
	$(CC) -o pf2 main_c.o $(DLFLAGS)

rb_ext: pathfinder_rbext.o pf_so
	$(CC) -shared $(LFLAGS) -o pathfinder_ext.so pathfinder_rbext.o $(DLFLAGS)

pf_so: search_field.o pathfinder.o findpath.o
	$(CXX) -shared $(LFLAGS) -o libpathfinder.so pathfinder.o search_field.o findpath.o

pf_a: search_field.o pathfinder.o
	$(AR) libpathfinder.a pathfinder.o search_field.o

main.o:
	$(CXX) $(CXXFLAGS) main.cpp

main_c.o:
	$(CC) $(CCFLAGS) -o main_c.o main.c $(DLFLAGS)

pathfinder.o:
	$(CXX) $(CXXFLAGS) pathfinder.cpp

search_field.o:
	$(CXX) $(CXXFLAGS) search_field.cpp

findpath.o:
	$(CXX) $(CXXFLAGS) findpath.cpp

pathfinder_rbext.o:
	$(CC) $(CCFLAGS) $(RBHEADERS) pathfinder_rbext.c $(DLFLAGS)

clean:
	rm -f pathfinder pf2 libpathfinder.so libpathfinder.a pathfinder_ext.so main.o main_c.o pathfinder.o pathfinder_rbext.o search_field.o findpath.o
