import ctypes
from tkinter import Tk, Label
from PIL import Image, ImageTk


PATH = 'C:\\msys64\\usr\\bin\\raytracing.dll'
raytracing = ctypes.CDLL(PATH)
raytracing.PerPixel.argtypes = [ctypes.c_float, ctypes.c_float]
raytracing.PerPixel.restype = ctypes.c_int

def unpack_rgb_color(color):
    red = (color >> 16) & 0xFF
    green = (color >> 8) & 0xFF
    blue = color & 0xFF
    return red, green, blue

def render(width, height, scale):
    img = Image.new('RGB', (width, height))
    pixels = img.load()
    for x in range(width):
        for y in range(height):
            coord_x = scale * (x - width / 2) / width
            coord_y = scale * (y - height / 2) / height
            color = raytracing.PerPixel(coord_x, coord_y)
            r, g, b = unpack_rgb_color(color)
            pixels[x, y] = (r, g, b)
    return img

root = Tk()
root.title("Imagem gerada por ray tracing")
root.geometry("1280x960")  

scale = 2.0
width, height = 1280, 960

image = render(width, height, scale)
image_tk = ImageTk.PhotoImage(image)

label = Label(root, image=image_tk)
label.pack()

root.mainloop()
