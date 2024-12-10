CXX = g++
CXXFLAGS = -std=c++17 -O2
LDFLAGS = -lpthread

SOURCES = main.cpp timer.cpp session_log.cpp notification.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = server

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
