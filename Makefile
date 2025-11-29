CXX = g++
CXXFLAGS = -I /opt/homebrew/include/SDL2 -std=c++17
LDFLAGS = -L /opt/homebrew/lib -lSDL2

SRC = $(wildcard src/engine/*.cpp src/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = game

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)