import ctypes
from tkinter import Tk, Label
from PIL import Image, ImageTk
import time


PATH = './raytracing.so'
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
    numSamples = 5
    for x in range(width):
        for y in range(height):
            colorAcumulated = [0, 0, 0]
            for i in range(numSamples):
                coord_x = scale * (x - width / 2) / width
                coord_y = scale * (y - height / 2) / height
                color = raytracing.PerPixel(coord_x, coord_y)
                r, g, b = unpack_rgb_color(color)
                colorAcumulated[0] += r
                colorAcumulated[1] += g
                colorAcumulated[2] += b

            avg_r = int(colorAcumulated[0] / numSamples)
            avg_g = int(colorAcumulated[1] / numSamples)
            avg_b = int(colorAcumulated[2] / numSamples)
            pixels[x, y] = (avg_r, avg_g, avg_b)
    return img

root = Tk()
root.title("Imagem gerada por ray tracing")
root.geometry("1280x960")  

scale = 2.0
width, height = 1280, 960

print("Rendering image...")
start_time = time.time()
image = render(width, height, scale)
end_time = time.time()
render_time = end_time - start_time
print("Image rendered in", render_time, "seconds")


image_tk = ImageTk.PhotoImage(image)

label = Label(root, image=image_tk)
label.pack()
    
root.mainloop()