#all:
	#cd ../iptools; make
#	g++ -o bin/test test.cpp  -L ../lib -l iptools 
#	g++ -o bin/test2 test2.cpp  -L ../lib -l iptools -l mpeg 

	# source files.

BIN_DIR=bin/

EXEC = iptool


all: $(EXEC) batch_tool

iptools:
	(cd ../iptools; make)

clean:
	$(RM) $(BIN_DIR)$(EXEC); make all

DO_EXEC = g++ `pkg-config --cflags opencv` $@.cpp `pkg-config --libs opencv` -o $(BIN_DIR)$@ -L ../lib -l iptools

#------ now compile
$(EXEC):   		iptools
				$(DO_EXEC)
batch_tool: batch.cpp
	g++ -o $(BIN_DIR)$@ batch.cpp
