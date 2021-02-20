from cs50 import get_int
import re

# prompt for input, check value type

while True:
    try:
        x = int(get_int("Number: "))
    except ValueError:
        continue
    if x < 0:
        continue
    else:
        break

# make a copy
copy = x

# find length
le = len(str(x))

# floor division: //
if le == 13 or le == 15 or le == 16:
    sum1 = 0
    sum2 = 0
    mod1 = 0
    mod2 = 0
    while x != 0:
        mod1 = int(x % 10)
        sum1 += mod1
        x //= 10
        mod2 = x % 10
        if mod2 * 2 > 9:
            sum2 += int(mod2 * 2 / 10 + mod2 * 2 % 10)
            x //= 10
        else:
            sum2 += mod2 * 2
            x //= 10
    
    # retrieve input
    x = str(copy)
    checksum = str(sum1 + sum2)

    if re.findall("0$", checksum):
        if le == 15:
            if re.findall("^34", x) or re.findall("^37", x):
                print("AMEX")
            else:
                print("INVAL6D")
        elif le == 13:
            if re.finall("^4", x):
                print("VISA")
            else:
                print("INVAL5D")
        elif le == 16:
            if re.findall("^4", x):
                print("VISA")
            elif re.findall("^51|52|53|54|55", x):
                # ^51|52|53|54|55 works
                # ^51|52|53|54|55 won't work
                print("MASTERCARD")
            else:
                print("INVALID")
        else:
            print("INVALID")
    else:
        print("INVALID")
else:
    print("INVALID")
