#Wei Luo
#YOU MUST HAVE YOUR NAME IN YOUR MAKEFILE!

#Makefile for lab 1-4.  You need to add you name to this file in the comments
# You will need to add a entry to create your zip file

#change the last dependency for each new lab
all:  tags headers lab4

#this entry has to change for lab 2 - 4
# NEVER compile .c files with this rule - it lacks needed compile time flags
# There is an entry below that turns .c files into .o files

lab4: lab4.o bits.o input.o memory.o output.o physics.o linkedlist.o sim.o n2.o reliable.o
	gcc -g -o $@ $^  -lm -L. -lpb -lncurses

lab4u: lab4.o bits.o input.o memory.o output.o physics.o linkedlist.o sim.o n2.o unreliable.o
	gcc -g -o $@ $^  -lm -L. -lpb -lncurses

#this is where you create an entry to build yuour zip file
#it will also update with new labs

lab4.zip: makefile *.c *.h n2.o reliable.o unreliable.o README_LAB4 libpb.a liblinkedlist.a
	zip $@ $^
	rm -rf install
	mkdir install
	unzip lab4.zip -d install
	make -C install lab4
	make -C install lab4u
	make -C install pins
	make -C install pdel
	make -C install pite
	make -C install psor
	rm -rf install

#Check if insert function in linkedlist.c works
pins: pins.o linkedlist.o reliable.o 
	gcc -g -o $@ $^

#Check if deleteSome function in linkedlist.c works
pdel: pdel.o linkedlist.o reliable.o
	gcc -g -o $@ $^

#Check if iterate function in linkedlist.c works
pite: pite.o linkedlist.o reliable.o
	gcc -g -o $@ $^

#Check if sort function in linkedlist.c works
psor: psor.o linkedlist.o reliable.o
	gcc -g -o $@ $^


#this entry stays for C code labs
tags: *.c
	ctags -R .

# this entry stays for C code labs
headers: *.c tags
	headers.sh


# this entry takes care of C files depending on header files
# It has the flags for compiling the c code
# It you don't like makefiles, consider typing the following line a few
# thousand times this semester and reconsider.
# Be sure that this one doesn't get an inserted line break anywhere
%.o:%.c *.h
	gcc -std=c99 -pedantic -Wformat -Wreturn-type -g -c $< -o $@


