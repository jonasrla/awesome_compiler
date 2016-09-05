CXX = g++
CFLAGS = -Wall -Iinclude -std=c++11
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
build/src/analisadores/analisador_lexico.o: /usr/include/stdlib.h
build/src/analisadores/analisador_lexico.o: /usr/include/Availability.h
build/src/analisadores/analisador_lexico.o: /usr/include/AvailabilityInternal.h
build/src/analisadores/analisador_lexico.o: /usr/include/_types.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/_types.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/cdefs.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/_symbol_aliasing.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/_posix_availability.h
build/src/analisadores/analisador_lexico.o: /usr/include/machine/_types.h
build/src/analisadores/analisador_lexico.o: /usr/include/i386/_types.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/_pthread/_pthread_types.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/wait.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/_types/_pid_t.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/_types/_id_t.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/signal.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/appleapiopts.h
build/src/analisadores/analisador_lexico.o: /usr/include/machine/signal.h
build/src/analisadores/analisador_lexico.o: /usr/include/i386/signal.h
build/src/analisadores/analisador_lexico.o: /usr/include/machine/_mcontext.h
build/src/analisadores/analisador_lexico.o: /usr/include/i386/_mcontext.h
build/src/analisadores/analisador_lexico.o: /usr/include/mach/i386/_structs.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/_pthread/_pthread_attr_t.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/_types/_sigaltstack.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/_types/_ucontext.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/_types/_sigset_t.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/_types/_size_t.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/_types/_uid_t.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/resource.h
build/src/analisadores/analisador_lexico.o: /usr/include/stdint.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/_types/_int8_t.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/_types/_int16_t.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/_types/_int32_t.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/_types/_int64_t.h
build/src/analisadores/analisador_lexico.o: /usr/include/_types/_uint8_t.h
build/src/analisadores/analisador_lexico.o: /usr/include/_types/_uint16_t.h
build/src/analisadores/analisador_lexico.o: /usr/include/_types/_uint32_t.h
build/src/analisadores/analisador_lexico.o: /usr/include/_types/_uint64_t.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/_types/_intptr_t.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/_types/_uintptr_t.h
build/src/analisadores/analisador_lexico.o: /usr/include/_types/_intmax_t.h
build/src/analisadores/analisador_lexico.o: /usr/include/_types/_uintmax_t.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/_types/_timeval.h
build/src/analisadores/analisador_lexico.o: /usr/include/machine/endian.h
build/src/analisadores/analisador_lexico.o: /usr/include/i386/endian.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/_endian.h
build/src/analisadores/analisador_lexico.o: /usr/include/libkern/_OSByteOrder.h
build/src/analisadores/analisador_lexico.o: /usr/include/libkern/i386/_OSByteOrder.h
build/src/analisadores/analisador_lexico.o: /usr/include/alloca.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/_types/_ct_rune_t.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/_types/_rune_t.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/_types/_wchar_t.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/_types/_null.h
build/src/analisadores/analisador_lexico.o: /usr/include/machine/types.h
build/src/analisadores/analisador_lexico.o: /usr/include/i386/types.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/_types/_dev_t.h
build/src/analisadores/analisador_lexico.o: /usr/include/sys/_types/_mode_t.h
build/src/analisadores/analisador_sintatico.o: include/analisador_sintatico.h
build/src/analisadores/analisador_sintatico.o: include/analisador_lexico.h
build/src/analisadores/analisador_sintatico.o: include/csv.h
build/src/analisadores/analisador_sintatico.o: /usr/include/stdlib.h
build/src/analisadores/analisador_sintatico.o: /usr/include/Availability.h
build/src/analisadores/analisador_sintatico.o: /usr/include/AvailabilityInternal.h
build/src/analisadores/analisador_sintatico.o: /usr/include/_types.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_types.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/cdefs.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_symbol_aliasing.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_posix_availability.h
build/src/analisadores/analisador_sintatico.o: /usr/include/machine/_types.h
build/src/analisadores/analisador_sintatico.o: /usr/include/i386/_types.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_pthread/_pthread_types.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/wait.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_types/_pid_t.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_types/_id_t.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/signal.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/appleapiopts.h
build/src/analisadores/analisador_sintatico.o: /usr/include/machine/signal.h
build/src/analisadores/analisador_sintatico.o: /usr/include/i386/signal.h
build/src/analisadores/analisador_sintatico.o: /usr/include/machine/_mcontext.h
build/src/analisadores/analisador_sintatico.o: /usr/include/i386/_mcontext.h
build/src/analisadores/analisador_sintatico.o: /usr/include/mach/i386/_structs.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_pthread/_pthread_attr_t.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_types/_sigaltstack.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_types/_ucontext.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_types/_sigset_t.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_types/_size_t.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_types/_uid_t.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/resource.h
build/src/analisadores/analisador_sintatico.o: /usr/include/stdint.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_types/_int8_t.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_types/_int16_t.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_types/_int32_t.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_types/_int64_t.h
build/src/analisadores/analisador_sintatico.o: /usr/include/_types/_uint8_t.h
build/src/analisadores/analisador_sintatico.o: /usr/include/_types/_uint16_t.h
build/src/analisadores/analisador_sintatico.o: /usr/include/_types/_uint32_t.h
build/src/analisadores/analisador_sintatico.o: /usr/include/_types/_uint64_t.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_types/_intptr_t.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_types/_uintptr_t.h
build/src/analisadores/analisador_sintatico.o: /usr/include/_types/_intmax_t.h
build/src/analisadores/analisador_sintatico.o: /usr/include/_types/_uintmax_t.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_types/_timeval.h
build/src/analisadores/analisador_sintatico.o: /usr/include/machine/endian.h
build/src/analisadores/analisador_sintatico.o: /usr/include/i386/endian.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_endian.h
build/src/analisadores/analisador_sintatico.o: /usr/include/libkern/_OSByteOrder.h
build/src/analisadores/analisador_sintatico.o: /usr/include/libkern/i386/_OSByteOrder.h
build/src/analisadores/analisador_sintatico.o: /usr/include/alloca.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_types/_ct_rune_t.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_types/_rune_t.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_types/_wchar_t.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_types/_null.h
build/src/analisadores/analisador_sintatico.o: /usr/include/machine/types.h
build/src/analisadores/analisador_sintatico.o: /usr/include/i386/types.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_types/_dev_t.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_types/_mode_t.h
build/src/analisadores/analisador_sintatico.o: /usr/include/stdio.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_types/_va_list.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/stdio.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_types/_off_t.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_types/_ssize_t.h
build/src/analisadores/analisador_sintatico.o: /usr/include/secure/_stdio.h
build/src/analisadores/analisador_sintatico.o: /usr/include/secure/_common.h
build/src/analisadores/analisador_sintatico.o: /usr/include/errno.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/errno.h
build/src/analisadores/analisador_sintatico.o: /usr/include/sys/_types/_errno_t.h
build/src/main.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
build/src/main.o: /usr/include/sys/_symbol_aliasing.h
build/src/main.o: /usr/include/sys/_posix_availability.h
build/src/main.o: /usr/include/Availability.h
build/src/main.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
build/src/main.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
build/src/main.o: /usr/include/i386/_types.h
build/src/main.o: /usr/include/sys/_pthread/_pthread_types.h
build/src/main.o: /usr/include/sys/_types/_va_list.h
build/src/main.o: /usr/include/sys/_types/_size_t.h
build/src/main.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
build/src/main.o: /usr/include/sys/_types/_off_t.h
build/src/main.o: /usr/include/sys/_types/_ssize_t.h
build/src/main.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
build/src/main.o: /usr/include/stdlib.h /usr/include/sys/wait.h
build/src/main.o: /usr/include/sys/_types/_pid_t.h
build/src/main.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
build/src/main.o: /usr/include/sys/appleapiopts.h
build/src/main.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
build/src/main.o: /usr/include/machine/_mcontext.h
build/src/main.o: /usr/include/i386/_mcontext.h
build/src/main.o: /usr/include/mach/i386/_structs.h
build/src/main.o: /usr/include/sys/_pthread/_pthread_attr_t.h
build/src/main.o: /usr/include/sys/_types/_sigaltstack.h
build/src/main.o: /usr/include/sys/_types/_ucontext.h
build/src/main.o: /usr/include/sys/_types/_sigset_t.h
build/src/main.o: /usr/include/sys/_types/_uid_t.h
build/src/main.o: /usr/include/sys/resource.h /usr/include/stdint.h
build/src/main.o: /usr/include/sys/_types/_int8_t.h
build/src/main.o: /usr/include/sys/_types/_int16_t.h
build/src/main.o: /usr/include/sys/_types/_int32_t.h
build/src/main.o: /usr/include/sys/_types/_int64_t.h
build/src/main.o: /usr/include/_types/_uint8_t.h
build/src/main.o: /usr/include/_types/_uint16_t.h
build/src/main.o: /usr/include/_types/_uint32_t.h
build/src/main.o: /usr/include/_types/_uint64_t.h
build/src/main.o: /usr/include/sys/_types/_intptr_t.h
build/src/main.o: /usr/include/sys/_types/_uintptr_t.h
build/src/main.o: /usr/include/_types/_intmax_t.h
build/src/main.o: /usr/include/_types/_uintmax_t.h
build/src/main.o: /usr/include/sys/_types/_timeval.h
build/src/main.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
build/src/main.o: /usr/include/sys/_endian.h
build/src/main.o: /usr/include/libkern/_OSByteOrder.h
build/src/main.o: /usr/include/libkern/i386/_OSByteOrder.h
build/src/main.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
build/src/main.o: /usr/include/sys/_types/_rune_t.h
build/src/main.o: /usr/include/sys/_types/_wchar_t.h
build/src/main.o: /usr/include/machine/types.h /usr/include/i386/types.h
build/src/main.o: /usr/include/sys/_types/_dev_t.h
build/src/main.o: /usr/include/sys/_types/_mode_t.h
build/src/main.o: include/analisador_lexico.h include/analisador_sintatico.h
build/src/main.o: include/analisador_de_escopo.h /usr/include/errno.h
build/src/main.o: /usr/include/sys/errno.h /usr/include/sys/_types/_errno_t.h
