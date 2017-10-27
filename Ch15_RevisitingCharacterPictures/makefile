CFLAGS = -O2 -Wall -Wextra -pedantic -std=c++14 -IC:/msys64/mingw64/include \
-LC:/msys64/mingw64/lib
CXX = g++


SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))
BINS = main1.exe main2.exe
DEPS = $(wildcard *.hpp)


all: $(BINS)

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)


main1.exe: main1.o Picture.o
	$(CXX) -o $@ $^ $(CFLAGS)

main2.exe: main2.o Picture.o
	$(CXX) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(BINS) $(OBJ)


.PHONY: all, clean
