CFLAGS = -O2 -Wall -Wextra -pedantic -std=c++14 -IC:/msys64/mingw64/include \
-LC:/msys64/mingw64/lib
CXX = g++


SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))
BINS = main.exe
DEPS = $(wildcard *.hpp)


all: $(BINS)

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

main.exe: $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(BINS) $(OBJ)


.PHONY: all, clean
