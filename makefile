CC=gcc
CXX=g++
AR=ar cr
BDIR=build
ODIR=out
SDIR=src
CXXFLAGS=-c -std=c++0x -fPIC
CCFLAGS=-c -Wall -Werror -fPIC
DLFLAGS=-L./$(ODIR) -lpathfinder
LFLAGS=-fPIC
RBHDR:=$(shell ruby -rmkmf -e 'print RbConfig::CONFIG["rubyhdrdir"]')
RBARCH:=$(shell ruby -rmkmf -e 'print RbConfig::CONFIG["arch"]')

main: out_dir main_out

pf2: out_dir pf_so pf2_out

rb_ext: out_dir pf_so rb_ext_out

pf_so: out_dir pf_so_out

pf_a: out_dir pf_a_out

main_out: $(BDIR)/main.o $(BDIR)/pathfinder.o $(BDIR)/search_field.o $(BDIR)/findpath.o
	$(CXX) -o $(ODIR)/pathfinder $?

pf2_out: $(BDIR)/main_c.o
	$(CC) -o $(ODIR)/pf2 $? $(DLFLAGS)

pf_so_out: $(BDIR)/search_field.o $(BDIR)/pathfinder.o $(BDIR)/findpath.o
	$(CXX) -shared $(LFLAGS) -o $(ODIR)/libpathfinder.so $?

rb_ext_out: $(BDIR)/pathfinder_rbext.o
	$(CC) -shared $(LFLAGS) -o $(ODIR)/pathfinder_ext.so $? $(DLFLAGS)

pf_a_out: $(BDIR)/search_field.o $(BDIR)/pathfinder.o
	$(AR) $(ODIR)/libpathfinder.a $?

$(BDIR)/main.o: build_dir
	$(CXX) $(CXXFLAGS) $(SDIR)/main.cpp -o $@

$(BDIR)/main_c.o: build_dir
	$(CC) $(CCFLAGS) -o main_c.o $(SDIR)/main.c $(DLFLAGS) -o $@

$(BDIR)/pathfinder.o: build_dir
	$(CXX) $(CXXFLAGS) $(SDIR)/pathfinder.cpp -o $@

$(BDIR)/search_field.o: build_dir
	$(CXX) $(CXXFLAGS) $(SDIR)/search_field.cpp -o $@

$(BDIR)/findpath.o: build_dir
	$(CXX) $(CXXFLAGS) $(SDIR)/findpath.cpp -o $@

$(BDIR)/pathfinder_rbext.o: build_dir
	$(CC) $(CCFLAGS) -I$(RBHDR) -I$(RBHDR)/$(RBARCH) $(SDIR)/pathfinder_rbext.c $(DLFLAGS) -o $@

build_dir:
	mkdir $(BDIR)

out_dir:
	mkdir $(ODIR)

clean:
	rm -rf $(ODIR) $(BDIR)
