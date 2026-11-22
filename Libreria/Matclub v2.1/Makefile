# ============================================================================
# Makefile de MATCLUB-CPP
#   make            -> compila la libreria (libmatclub.a) y el ejemplo
#   make ejemplo    -> solo el ejemplo (Ejemplos/ejemplo_uso.cpp)
#   make clean      -> borra los archivos generados
# En Windows con MinGW:  mingw32-make
# ============================================================================
CXX      = g++
CXXFLAGS = -O2 -std=c++98

FUENTES  = $(wildcard Bloque_*/*.cpp Complementos/*.cpp)
OBJETOS  = $(FUENTES:.cpp=.o)

all: libmatclub.a ejemplo

libmatclub.a: $(OBJETOS)
	ar rcs $@ $^

ejemplo: Ejemplos/ejemplo_uso.cpp libmatclub.a
	$(CXX) $(CXXFLAGS) $< -L. -lmatclub -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJETOS) libmatclub.a ejemplo ejemplo.exe

.PHONY: all clean
