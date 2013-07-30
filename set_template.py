
import sys;

template = sys.argv[1];
source = sys.argv[2];

f1 = open(template, 'rb');
f2 = open(source, 'wt');

f2.write('const unsigned char Storage::page_template[] = {\n');

byte = f1.read(1)
if byte:
    f2.write(hex(ord(byte)))
    byte = f1.read(1)
count = 1
while byte:
    f2.write(','+hex(ord(byte)))
    count = count + 1
    if count%16 == 0:
        f2.write('\n')
    byte = f1.read(1)

f2.write('};')
f2.close();
f1.close();
