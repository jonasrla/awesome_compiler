CXX = g++ 
CFLAGS = -Wall -Iinclude  -std=c++11 
LFLAGS = -WALL

DEBUG = 0

SRC = $(wildcard src/*.cpp src/*/*.cpp)
OBJ = $(patsubst %.cpp, build/%.o, $(SRC))


ifeq ($(DEBUG), 1)
	CFLAGS += -g -O0
else
	CFLAGS += -O3
endif

.PHONY: all clean

# add learner later
all: awe_comp

clean:
	@rm -rf build/*
	@rm -f *.run


awe_comp: $(OBJ) build/src/libcsv.o
	$(CXX) $(LFLAGS) $(OBJ) build/src/libcsv.o -o $@

build/src/%.o: src/%.cpp
	@echo
	@echo $@
	@echo 
	mkdir -p $(@D)
	$(CXX) -c $(CFLAGS) $(patsubst build/%.o, %.cpp, $(@)) -o $(@)

build/src/libcsv.o: src/libcsv.c
	@echo
	@echo $@
	@echo 
	mkdir -p $(@D)
	gcc -c -Wall -Iinclude $(patsubst build/%.o, %.c, $(@)) -o $(@)

# Generated by makedepend:
# makedepend src/*/* src/*.cpp -Iinclude -pbuild/
# DO NOT DELETE
build/src/analisadores/analisador_lexico.o: include/analisador_lexico.h
build/src/analisadores/analisador_sintatico.o: include/analisador_sintatico.h
build/src/analisadores/analisador_sintatico.o: include/analisador_lexico.h
build/src/analisadores/analisador_sintatico.o: include/csv.h
build/src/main.o: include/analisador_lexico.h include/analisador_sintatico.h
build/src/main.o: include/analisador_de_escopo.h 
build/src/libcsv.o: include/csv.h