from cs50 import get_float 

c = 0

while True:
    try:
        c = float(get_float("Change owed: "))
    except ValueError:
        continue
    if c < 0:
        continue
    else:
        break
# cents
c = int(c * 100)
# dimes
q = int(c / 25)
c = c % 25
if c == 0:
    print(q)
else:
    # dimes
    d = int(c / 10)
    c = c % 10
    if c == 0:
        print(q + d)
    else:
        # nickels
        n = int(c / 5)
        c = c % 5
        print(q + d + n + c)
        