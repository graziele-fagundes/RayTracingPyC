# Nome do executável da DLL
DLL_NAME=C:/msys64/usr/bin/raytracing.dll

# Arquivos fonte
SOURCES=raytracing.c utils.c

# Comando Python
PYTHON=python

# Nome do script Python
PYTHON_SCRIPT=interface.py

# Compilador e flags
CC=gcc
CFLAGS=-shared -fPIC

# Alvo padrão
all: build run

# Alvo para compilar a DLL
build: $(SOURCES)
	$(CC) $(CFLAGS) -o $(DLL_NAME) $(SOURCES)

# Alvo para executar o script Python
run:
	$(PYTHON) $(PYTHON_SCRIPT)

# Alvo para limpar arquivos gerados
clean:
	rm -f $(DLL_NAME)