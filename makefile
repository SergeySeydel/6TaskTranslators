#
 # @file	makefile
 # @data	00-JAN-22
 # @author	Mineev S. A.
 # @email	mineeff20@yandex.ru
 # @version	v1.0
 # @license	FS(FreeSoft)
 # @brief	-
 # @detail	-
 # 
#
 # COMPILATOR: 
CC=cc 
GCC=gcc 
CXX=g++ 
CLANG=clang
 # FLAGS: 
CFLAGS=-o 
CXXFLAGS=- 
LIBFLAGS=-pthread 
GDBFLAG=-g3 -O0
 # SRC + OBJ + TAG: 
SRC = main.c 
OBJ = - 
TAG = PROG
 
.PHONY: all clean install uninstall
 
all: ${TAG}
 
${TAG}: ${SRC} 
	${CXX} $^ ${GDBFLAG} ${CFLAGS} $@
 
clean: ${TAG} 
	rm $^
# 
