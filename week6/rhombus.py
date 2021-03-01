h = 0
while True:
    try:
        h = int(input("Height: "))
    except ValueError:
        continue
    if int(h) < 1 or int(h) > 64:
        continue
    else:
        break
print("")
for x in range(1, h + 1):
    for y in range(h - 1, -1, -1):
        if x - y <= 0:
            print(" ", end="") ### Important: end=""
        else:
            print("#", end="")
    print(" ", end="")
    for z in range(x):
        print("#", end="")
    print("")
for x in range(1, h + 1):
    if x == h:
        print("")
        break
    for y in range(1, h + 1):
        if y <= x:
            print(" ", end="")
        else:
            print("#", end="")
    print(" ", end="");
    for z in range(0, h + 1):
        if z > x:
            print('#', end="")
    print("")
