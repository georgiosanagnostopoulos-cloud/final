CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
TARGET = PomodoroTimer

SRCS = main.cpp timer.cpp session_log.cpp user_manager.cpp
OBJS = $(SRCS:.cpp=.o)

INCLUDE_PATH = /path/to/crow/include
LIBS = -pthread

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_PATH) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_PATH) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean
