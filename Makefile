all: main

main: main.cpp Timer.cpp SessionLog.cpp User.cpp ConfigManager.cpp
	g++ -o main main.cpp Timer.cpp SessionLog.cpp User.cpp ConfigManager.cpp -lnlohmann_json

clean:
	rm -f main
