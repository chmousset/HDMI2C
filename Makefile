#
# Copyright (c) 2014 Charles-Henri Mousset
# Distributed under the GNU GPL v2. For full terms see the file LICENSE
#


all: \
	edid \
	ee24c02w \
	ee24c02r \

	
clean:
	rm *.bin

edid:
	gcc -o edid.bin edid.c

ee24c02w:
	gcc -o ee24c02w.bin ee24c02w.c

ee24c02r:
	gcc -o ee24c02r.bin ee24c02r.c
