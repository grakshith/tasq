CXX=g++
CXXFLAGS=-std=c++11 -I. -L /usr/lib/x86-64-linux-gnu/boost/
BIN_DIR=bin
OBJ_DIR=build

LIBS=-lboost_system -lboost_filesystem -lboost_thread

SRC_DIR=src
_DEPS = daemon.h worker.h shell.h
DEPS = $(patsubst %,$(SRC_DIR)/%,$(_DEPS))

# _OBJ = daemon.o
# OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))


all: $(BIN_DIR)/daemon $(BIN_DIR)/worker $(BIN_DIR)/shell

$(BIN_DIR)/daemon: build/daemon.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

$(BIN_DIR)/worker: build/worker.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

$(BIN_DIR)/shell: build/shell.o
	$(CXX) -o $@ $^ $(CXXFLAGS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)


.PHONY: clean

clean:
	rm -f $(BIN_DIR)/* $(OBJ_DIR)/*.o
