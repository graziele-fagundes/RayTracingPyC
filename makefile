# Nome do executável da DLL
SO_NAME=raytracing.so

# Arquivos fonte
SOURCES=raytracing.c utils.c

# Comando Python
PYTHON=python

# Nome do script Python
PYTHON_SCRIPT=interface.py

# Compilador e flags
CC=gcc
CFLAGS=-fPIC -shared -o

# Alvo padrão
all: build run

# Alvo para compilar a DLL
build:
	$(CC) $(CFLAGS) $(SO_NAME) $(SOURCES)

# Alvo para executar o script Python
run:
	$(PYTHON) $(PYTHON_SCRIPT)