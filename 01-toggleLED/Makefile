
CC		= gcc
RM		= rm
LIBS	= -lwiringPi

all: toggleLED

toggleLED: toggleLED.c
	$(CC) toggleLED.c -o toggleLED $(LIBS)

distclean:
	$(RM) toggleLED

