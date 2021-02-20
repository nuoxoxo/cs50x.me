from cs50 import get_string
import re

str = get_string("Text: ")
words = 1
letters = 0
sentences = str.count(".") + str.count("!") + str.count("?")

# of what use are ord and chr
for i in range(len(str)):
    if str[i].isspace():
        words += 1
    if str[i].isalnum():
        letters += 1

# calculate letters / sentences per 100 words
L = letters / words * 100
S = sentences / words * 100

# Coleman-Liau index = 0.0588 * L - 0.296 * S - 15.8
index = round(0.0588 * L - 0.296 * S - 15.8)

print(index)

if index > 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {index}")