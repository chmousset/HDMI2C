#
# Copyright (c) 2014 Charles-Henri Mousset
# Distributed under the GNU GPL v2. For full terms see the file LICENSE
#


all: \
	edid \

	
clean:
	rm *.bin

edid:
	gcc -o edid.bin edid.c
