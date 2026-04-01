CXX = g++
NUMPY    = $(shell python3 -c "import numpy; print(numpy.get_include())")
PY_INC   = $(shell python3-config --includes)
PY_LIBS  = $(shell python3-config --libs)
PY_VER   = $(shell python3 -c "import sys; print(f'{sys.version_info.major}.{sys.version_info.minor}')")

CXXFLAGS = -std=c++17 -Wall -I include -I $(NUMPY) $(PY_INC)
LDFLAGS  = -lpython$(PY_VER)

SRC = src/signal.cpp src/export.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = simulador

$(TARGET): main.cpp $(OBJ)
		$(CXX) $(CXXFLAGS) main.cpp $(OBJ) -o $(TARGET) $(LDFLAGS)

src/%.o: src/%.cpp
		$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
		rm -f src/*.o $(TARGET)
