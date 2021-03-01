# TODO
from cs50 import SQL
import csv
import sys

if len(sys.argv) != 2:
    if sys.argv[1].lower() != 'slytherin' or sys.argv[1].lower() != 'ravenclaw' or sys.argv[1].lower() != 'hufflepuff' or sys.argv[1].lower() != 'gryffindor':
        print('Usage: python roster.py Gryffindor')

db = SQL('sqlite:///students.db')

house = db.execute('select first, middle, last, birth from students where house = (?) order by last, first', sys.argv[1])

for row in house:
    if row['middle'] == None:
        print(row['first'] + ' ' + row['last'] + ', born ' + str(row['birth']))
    else:
        print(row['first'] + ' ' + row['middle'] + ' ' + row['last'] + ', born ' + str(row['birth']))
