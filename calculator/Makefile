CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET = calculator.out
SRCS = main.cpp

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)

.PHONY: clean
