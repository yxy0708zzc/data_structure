CC = g++
CXXFLAGS = -Wall -Wextra -O2

SRCS = $(wildcard *.cpp)
NAMES = $(SRCS:.cpp=)

all: $(NAMES)

$(NAMES): %: %.cpp
	@mkdir -p bin
	$(CC) $(CXXFLAGS) $< -o bin/$@

clean:
	rm -rf bin

.PHONY: all clean $(NAMES)
