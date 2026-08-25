CXX = g++
NUMPY    = $(shell python3 -c "import numpy; print(numpy.get_include())")
PY_INC   = $(shell python3-config --includes)
PY_LIBS  = $(shell python3-config --libs)
PY_VER   = $(shell python3 -c "import sys; print(f'{sys.version_info.major}.{sys.version_info.minor}')")

CXXFLAGS = -std=c++17 -Wall -I include -I $(NUMPY) $(PY_INC)
LDFLAGS  = -lpython$(PY_VER)

SRC = src/sinal.cpp src/variaveis_aleatorias.cpp src/autocorrelacao.cpp 
OBJ = $(SRC:src/%.cpp=build/%.o)
TARGET = main

$(TARGET): main.cpp $(OBJ)
		$(CXX) $(CXXFLAGS) main.cpp $(OBJ) -o $(TARGET) $(LDFLAGS)

build/%.o: src/%.cpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

#src/%.o: src/%.cpp
#		$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
		rm -f src/*.o $(TARGET) build/*.o
