# Uma implementação gráfica de Ray Tracing Recursivo utilizando em conjunto Python e C.
Repositório composto pelos seguintes arquivos:
- interface.py: responsável pela interface e por gerar a imagem calculada
- raytracing.c: responsável pelo cálculo da cor do píxel da imagem gerada através de ray-tracing
- raytracing.so: biblioteca compilada do raytracing.c que será usada pelo programa python
- arquivos extras: arquivos de utilidade para o projeto.

# Requerimentos
Python e pillow

# Rodando o projeto
Para rodar o projeto verfique que você possui a biblioteca necessária rodando o comando:
```
pip install pillow
```
Após instalada só resta rodar o código python:
```
python ./interface.py
```
