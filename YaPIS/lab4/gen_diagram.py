import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle, FancyArrowPatch

def add_block(ax, text, x, y, width=2, height=1):
    ax.add_patch(Rectangle((x, y), width, height, fill=True, edgecolor='black', facecolor='white'))
    ax.text(x + width / 2, y + height / 2, text, ha='center', va='center', fontsize=10, color='black')

def add_arrow(ax, x1, y1, x2, y2):
    arrow = FancyArrowPatch((x1, y1), (x2, y2), connectionstyle="arc3,rad=.5", arrowstyle='->', mutation_scale=15, color='black')
    ax.add_patch(arrow)

fig, ax = plt.subplots(figsize=(10, 8))
ax.set_xlim(0, 10)
ax.set_ylim(0, 12)
ax.axis('off')

add_block(ax, 'START', 4, 10)
add_block(ax, 'MOV AX, 0x1F', 4, 8)
add_block(ax, 'ADD BX, 10', 4, 6)
add_block(ax, 'LOOP', 4, 4)
add_block(ax, 'SUB CX, BX', 4, 2)
add_block(ax, 'JMP LOOP', 4, 0)

add_arrow(ax, 5, 10, 5, 9)
add_arrow(ax, 5, 8, 5, 7)
add_arrow(ax, 5, 6, 5, 5)
add_arrow(ax, 5, 4, 5, 3)
add_arrow(ax, 5, 2, 5, 1)

plt.show()