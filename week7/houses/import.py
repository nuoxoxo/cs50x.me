# TODO
from cs50 import SQL
import csv
import sys

try:
    if len(sys.argv) == 2:
        reader = csv.DictReader(open(sys.argv[1]), delimiter=',')
    else:
        print('Error 1: Usage: python import.py characters.csv')
        sys.exit(1)
except ValueError:
    print('Error 2: Usage: python import.py characters.csv')
    sys.exit(1)

db = SQL('sqlite:///students.db')

### 3 header-rows in csv: name,house,birth

for row in reader:
    name = row['name'].split()

    if len(name) == 2:
        firstname = name[0]
        lastname = name[1]
        db.execute('INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)', firstname, None, lastname, row['house'], row['birth'])
    elif len(name) == 3:
        firstname = name[0]
        middlename = name[1]
        lastname = name[2]
        db.execute('INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)', firstname, middlename, lastname, row['house'], row['birth'])
