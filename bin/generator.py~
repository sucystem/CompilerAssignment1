import string
import random
import sys

f = open('testcase', mode='wt')

id_length = 11

state = ["label", "integer"]

length = 1000;

if len(sys.argv) == 2:
    length = int(sys.argv[1])

for i in range(length):
    f.write(random.choice(state));
    f.write(" ");
    str_id = random.choice(string.ascii_letters)
    for s in range(0, id_length - 1):
        str_id += random.choice(string.ascii_letters)
    for j in range(random.randint(0, 9)):
        str_id += "," + random.choice(string.ascii_letters)
        for s in range(random.randint(0, id_length - 1)):
            str_id += random.choice(string.ascii_letters + string.digits)
    f.write(str_id)
    f.write(";\n")

f.close()


