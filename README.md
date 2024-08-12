# Ray Tracing Recursivo
Uma implementação gráfica de Ray Tracing Recursivo utilizando em conjunto Python e C.

Repositório composto pelos seguintes arquivos:
- interface.py: responsável pela interface e por gerar a imagem calculada
- raytracing.c: responsável pelo cálculo da cor do píxel da imagem gerada através de ray-tracing
- arquivos extras: arquivos de utilidade para o projeto.

## Linux

### Requisitos
Antes de executar o projeto, certifique-se de ter os seguintes pacotes instalados:
- **gcc**: Compilador C
```
sudo apt-get install gcc
```
- **make**: Utilitário de automação de compilação
```
sudo apt install make
```
- **python3**: Interpretador Python 3
```
sudo apt-get install python3.9
```
- **tkinter**: Toolkit para interfaces gráficas em Python
```
sudo apt install python3-tk
```
- **pillow**: Biblioteca de manipulação de imagens em Python
```
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
