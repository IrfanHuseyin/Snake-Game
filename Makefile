# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2 -Iinclude

# The name of the output executable
TARGET = snake

# List of source files (.cpp files)
SRCS = src/main.cpp src/game.cpp src/snake.cpp src/food.cpp

# Object files, derived from source files
OBJS = $(SRCS:.cpp=.o)

# The default target
all: $(TARGET)

# Rule to link the object files into an executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Rule to compile the source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(OBJS) $(TARGET)
