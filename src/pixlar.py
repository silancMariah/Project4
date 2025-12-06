from PIL import Image
import sys
import os
print("CWD:", os.getcwd())

# ---- Ladda bilden ----
img = Image.open("/Users/silancetinkaya/Project4/src/bilder/pig.png").convert("RGB")

# ---- Välj storlek om du vill skala (t.ex. 16x16) ----
img = img.resize((16,16), Image.NEAREST)

pixels = img.load()

# ---- Samla färger och ge dem index (0,1,2...) ----
color_map = {}
array = []
next_index = 1   # reserv: 0 = transparent

for y in range(img.height):
    row = []
    for x in range(img.width):
        color = pixels[x,y]
        if color not in color_map:
            color_map[color] = next_index
            next_index += 1
        row.append(color_map[color])
    array.append(row)

# ---- Skriv ut sprite-array som C-kod ----
print("static const unsigned char PIG[16][16] = {")
for row in array:
    print("    {" + ",".join(str(v) for v in row) + "},")
print("};")

# ---- Visa färgtabellen ----
print("\n// Färgindex (RGB):")
for color, idx in color_map.items():

    print(f"// {idx} -> {color}")
