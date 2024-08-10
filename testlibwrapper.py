import ctypes
from tkinter import Tk, Label, Button
from PIL import Image, ImageTk
import time

# Carregar a biblioteca C
testlib = ctypes.CDLL('C:\\msys64\\usr\\bin\\teste.dll')
testlib.PerPixel.argtypes = [ctypes.c_float, ctypes.c_float]
testlib.PerPixel.restype = ctypes.c_int

# Função para extrair componentes RGB
def unpack_rgb_color(color):
    red = (color >> 16) & 0xFF
    green = (color >> 8) & 0xFF
    blue = color & 0xFF
    return red, green, blue

# Função para criar a imagem da esfera
def create_high_res_sphere_image(width, height, scale):
    img = Image.new('RGB', (width, height))
    pixels = img.load()
    for x in range(width):
        for y in range(height):
            coord_x = scale * (x - width / 2) / width
            coord_y = scale * (y - height / 2) / height
            color = testlib.PerPixel(coord_x, coord_y)
            r, g, b = unpack_rgb_color(color)
            pixels[x, y] = (r, g, b)
    return img

# Configuração da janela principal
root = Tk()
root.title("Imagem gerada por ray tracing com esfera de alta resolução")
root.geometry("1280x960")  # Define o tamanho da janela

# Defina o fator de escala para aumentar a resolução da esfera
scale = 2.0
width, height = 1280, 960

# Cria a imagem inicial
image = create_high_res_sphere_image(width, height, scale)
image_tk = ImageTk.PhotoImage(image)

# Label para exibir a imagem
label = Label(root, image=image_tk)
label.pack()

# Executa a interface gráfica
root.mainloop()
