
CC		= gcc
RM		= rm
LIBS		= -lwiringPi

all: 01toggleLED

01toggleLED: 01toggleLED.c
	$(CC) 01toggleLED.c -o 01toggleLED $(LIBS)

distclean:
	$(RM) 01toggleLED

