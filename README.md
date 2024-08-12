# Ray Tracing Recursivo
Uma implementação gráfica de Ray Tracing Recursivo utilizando em conjunto Python e C. [Documentação](https://docs.google.com/document/d/1wjuW1kJKHCUQf5og_3ERMouvzWpndZdGRIGXOz40tPk/edit?usp=sharing)

Repositório composto pelos seguintes arquivos:
- interface.py: responsável pela interface e por gerar a imagem calculada
- raytracing.c: responsável pelo cálculo da cor do píxel da imagem gerada através de ray-tracing
- Arquivos extras: arquivos de utilidade para o projeto.
  - .gitignore: arquivo de configuração que especifica quais arquivos e diretórios devem ser ignorados pelo Git
  - makefile: arquivo de automação de compilação
  - scene.h: arquivo que especifica os objetos inclusos na cena renderizada
  - utils.h/utils.c: arquivo com funções úteis para a execução dos cálculos necessários

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

### Execução
Para compilar e executar o projeto, você pode usar o Makefile fornecido:
```
make
```
Alternativamente, você pode compilar e executar manualmente com os seguintes comandos:
```
gcc -fPIC -shared -o raytracing.so raytracing.c utils.c
python3 interface.py
```

## Windows

### Requisitos
Antes de executar o projeto, é essencial garantir que os seguintes pacotes estejam instalados:
- **gcc:**
Para instalar o pacote gcc no Windows, recomendamos seguir o seguinte tutorial: [Como Instalar GCC/G++ MinGW no Windows](https://terminalroot.com.br/2022/12/como-instalar-gcc-gpp-mingw-no-windows.html)
- **python:**
Para instalar Python no Windows, recomendamos a seguinte página: [Python](https://www.python.org/downloads/windows/)
- **tkinter:**
```
pip install tk
```
- **pillow:**
```
pip install pillow
```

### Execução
Para compilar e executar o projeto, você pode usar o Makefile fornecido:
```
mingw32-make
```
Alternativamente, você pode compilar e executar manualmente com os seguintes comandos:
```
gcc -fPIC -shared -o raytracing.so raytracing.c utils.c
python interface.py
```
