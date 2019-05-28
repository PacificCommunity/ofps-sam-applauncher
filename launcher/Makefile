########################################################################
#  Copyright - Pacific Community                                       #
#  Droit de copie - Communauté du Pacifique                            #
#  http://www.spc.int/                                                 #
########################################################################
TARGET=launcher
CC=g++
CFLAGS=-c -I$(INCLUDES)
INCLUDES=
LIBS=

DEPS=main.o

all: $(TARGET)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 

$(TARGET): $(DEPS)
	$(CC) $(DEPS) -o $(TARGET)

clean:
	rm -rf $(DEPS)

clean-all: clean
	rm -rf $(TARGET)
