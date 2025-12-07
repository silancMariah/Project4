from PIL import Image
import os

print("CWD:", os.getcwd())

# ---- Sökväg till bilden ----
path = "/Users/silancetinkaya/Project4/src/bilder/game_over.png"

# ---- Skapa sprite-namn från filnamn ----
filename = os.path.basename(path).split(".")[0]  # "heart"
SPRITE_NAME = filename.upper()                   # "HEART"

# ---- Ladda, skala, reducera färger ----
img = Image.open(path).convert("RGB")
img = img.resize((16, 16), Image.NEAREST)

MAX_COLORS = 8
img = img.quantize(colors=MAX_COLORS, method=0).convert("RGB")  # behåll den här!
pixels = img.load()

# ---- Bygg färg-index ----
color_map = {}         # vi låter 0 vara transparent senare
array = []
next_index = 1         # starta på 1, 0 = bakgrund

for y in range(img.height):
    row = []
    for x in range(img.width):
        color = pixels[x, y]

        if color not in color_map:
            color_map[color] = next_index
            next_index += 1

        row.append(color_map[color])
    array.append(row)

# ---- Skriv ut sprite-array som C-kod ----
print(f"static const unsigned char {SPRITE_NAME}[16][16] = {{")
for row in array:
    fixed = []
    for v in row:
        # Gör alla pixlar som har samma index som svart till 0
        if v == color_map.get((0, 0, 0)):
            fixed.append("0")
        else:
            fixed.append(str(v))
    print("    {" + ",".join(fixed) + "},")
print("};")

# ---- Visa färgtabellen ----
print("\n// Färgindex (RGB):")
for color, idx in color_map.items():
    # Hoppa över svart om du vill, eftersom du ändå använder 0 för den
    print(f"// {idx} -> {color}")
