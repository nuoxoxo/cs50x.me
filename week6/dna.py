import csv
import sys
import re

# Check correct usage
if len(sys.argv) != 3:
    sys.exit("Usage: python dna.py data.csv sequence.txt")


def count_repeats(sequence, pattern):
    # Algr for counting consecutive substring 
    repeats = 0
    copy_pattern = pattern
    while pattern in sequence:
        repeats += 1
        pattern += copy_pattern
    return repeats

    
# List of standard STR types
strs = []
# Database of suspects
susp = []

# Load STR types
with open(sys.argv[1]) as file1:
    reader = csv.reader(file1)
    strs = next(reader)
    strs.pop(0)
    file1.close()

# Load suspects and evidence 
# Impossible to merge both times
with open(sys.argv[1]) as file1, open(sys.argv[2]) as file2:
    reader = csv.DictReader(file1)
    susp = list(reader)
    evid = file2.readline()

match1 = []

for x in range(len(strs)):
    repeats = count_repeats(evid, strs[x])
    match1.append(repeats)

for x in range(len(susp)):
    match2 = []
    for y in range(len(strs)):
        match2.append(int(susp[x][strs[y]]))
    if match1 == match2:
        print(susp[x]['name'])
        break
    elif x == len(susp) - 1 and y == len(strs) - 1 and match1 != match2:
        print("No match")
        

"""Testing (for open and load files)"""
# print(strs)
# print(evid)
# print(susp)
# for name in susp:
#     print(name)