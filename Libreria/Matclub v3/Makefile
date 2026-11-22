# ============================================================================
# Makefile de MATCLUB-CPP (modulos independientes)
#   make comprobar  -> comprueba que cada modulo compila SOLO (sin los demas)
#   make ejemplo    -> compila y deja listo Ejemplos/ejemplo_uso.cpp
#   make clean      -> borra lo generado
# En Windows con MinGW:  mingw32-make
# ============================================================================
CXX      = g++
CXXFLAGS = -std=c++98

comprobar:
	@for f in Bloque_*/*.cpp Complementos/*.cpp; do \
	  $(CXX) $(CXXFLAGS) -fsyntax-only $$f || exit 1; echo "OK  $$f"; \
	done

ejemplo: Ejemplos/ejemplo_uso.cpp
	$(CXX) $(CXXFLAGS) $< -o ejemplo

clean:
	rm -f ejemplo ejemplo.exe

.PHONY: comprobar ejemplo clean
