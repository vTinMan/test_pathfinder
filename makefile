CXX=g++
AR=ar cr
CFLAGS=-c -std=c++0x -fPIC
# LFLAGS=-shared

pf_app: main.o pathfinder.o search_field.o
	$(CXX) -o pathfinder main.o pathfinder.o search_field.o

pf_app2: pf_lib main_so.o
	$(CXX) -o pf_main_so main_so.o libpathfinder.a

pf_lib: pathfinder.o search_field.o
	$(AR) libpathfinder.a pathfinder.o search_field.o

main.o:
	$(CXX) $(CFLAGS) main.cpp

main_so.o:
	$(CXX) $(CFLAGS) main_so.cpp

pathfinder.o:
	$(CXX) $(CFLAGS) pathfinder.cpp

search_field.o:
	$(CXX) $(CFLAGS) search_field.cpp

clean:
	rm -f pathfinder libpathfinder.a pf_main_so main.o main_so.o pathfinder.o search_field.o
