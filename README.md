# Ray Tracing Recursivo
Uma implementação gráfica de Ray Tracing Recursivo utilizando em conjunto Python e C.

Repositório composto pelos seguintes arquivos:
- interface.py: responsável pela interface e por gerar a imagem calculada
- raytracing.c: responsável pelo cálculo da cor do píxel da imagem gerada através de ray-tracing
- arquivos extras: arquivos de utilidade para o projeto.

## Linux

### Requisitos
Antes de executar o projeto, é essencial garantir que os seguintes pacotes estejam instalados: gcc, make, python3, tkinter e pillow. Se algum desses pacotes ainda não estiver instalado, siga os comandos abaixo para realizá-lo:
```
sudo apt-get install gcc
sudo apt install make
sudo apt-get install python3.9
sudo apt install python3-tk
sudo apt install python3-pil
sudo apt install python3-pil.imagetk
```

### Executar
Para compilar e executar o projeto, você pode usar o Makefile fornecido:
```
make
```
Alternativamente, você pode compilar e executar manualmente com os seguintes comandos:
```
gcc -fPIC -shared -o raytracing.so raytracing.c utils.c
python3 interface.py
```
