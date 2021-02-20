# mario more
#                       y   x
# _ _ _ _ _ _ _ # _ _ # 7 + 1 (+ 2) +1
# _ _ _ _ _ _ ## _ _ ## 6 + 2 
# _ _ _ _ _ ### _ _ ### 5 + 3	
# _ _ _ _ #### _ _ #### 4 + 4
# _ _ _ ##### _ _ ##### 3 + 5
# _ _ ###### _ _ ######
# _ ####### _ _ #######
# ######## _ _ ######## 0 + 8 (+ 2) +i

h = 0

# while int(h) < 2
while True:
    try:
        h = int(input("Height: "))
    except ValueError:
        continue
    if int(h) < 1 or int(h) > 8:
        continue
    else:
        break

for x in range(1, h + 1, 1):
    for y in range(h - 1, -1, -1):
        if x - y <= 0:
            print(" ", end="")
        else:
            print("#", end="")
    print("  ", end="")
    for z in range(x):
        print("#", end="")
    print("")