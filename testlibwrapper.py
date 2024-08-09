import ctypes
from tkinter import Tk, Label, Button
from PIL import Image, ImageTk

# Carregar a biblioteca C
testlib = ctypes.CDLL('C:\\msys64\\usr\\bin\\teste.dll')
testlib.rayTracing.argtypes = [ctypes.c_float, ctypes.c_float, ctypes.c_float]
testlib.rayTracing.restype = ctypes.c_int

# Função para extrair componentes RGB
def unpack_rgb_color(color):
    red = (color >> 16) & 0xFF
    green = (color >> 8) & 0xFF
    blue = color & 0xFF
    return red, green, blue

# Função para criar a imagem da esfera
def create_high_res_sphere_image(width, height, scale, button_value):
    img = Image.new('RGB', (width, height))
    pixels = img.load()
    for x in range(width):
        for y in range(height):
            coord_x = scale * (x - width / 2) / width
            coord_y = scale * (y - height / 2) / height
            color = testlib.rayTracing(coord_x, coord_y, button_value)
            r, g, b = unpack_rgb_color(color)
            pixels[x, y] = (r, g, b)
    return img

# Função para atualizar a imagem com base no valor do botão
def update_image(button_value):
    global image_tk, label
    image = create_high_res_sphere_image(width, height, scale, button_value)
    image_tk = ImageTk.PhotoImage(image)
    label.config(image=image_tk)
    label.image = image_tk  # Atualiza a referência para evitar que o Python faça garbage collection

# Configuração da janela principal
root = Tk()
root.title("Imagem gerada por ray tracing com esfera de alta resolução")
root.geometry("1280x960")  # Define o tamanho da janela

# Defina o fator de escala para aumentar a resolução da esfera
scale = 2.0
width, height = 1280, 960

# Cria a imagem inicial
image = create_high_res_sphere_image(width, height, scale, 0.0)
image_tk = ImageTk.PhotoImage(image)

# Label para exibir a imagem
label = Label(root, image=image_tk)
label.pack()

# Funções para cada botão
def set_value_to_minus_one():
    update_image(-1)

def set_value_to_zero():
    update_image(0)

def set_value_to_one():
    update_image(1)

# Cria os botões e posiciona-os no canto superior direito
button_minus_one = Button(root, text="-1", command=set_value_to_minus_one)
button_minus_one.place(relx=0.9, rely=0.05, anchor="ne")

button_zero = Button(root, text="0", command=set_value_to_zero)
button_zero.place(relx=0.9, rely=0.1, anchor="ne")

button_one = Button(root, text="1", command=set_value_to_one)
button_one.place(relx=0.9, rely=0.15, anchor="ne")

# Executa a interface gráfica
root.mainloop()
