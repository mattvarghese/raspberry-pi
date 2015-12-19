
MAKE	= make
CD		= cd
RM		= rm
TOGGLELED		= 01-toggleLED/

all: 
	@echo 
	@echo Making $(TOGGLELED)
	$(CD) $(TOGGLELED); echo ; $(MAKE)
	@echo

distclean:
	@echo 
	@echo Cleaning $(TOGGLELED)
	$(CD) $(TOGGLELED); echo ; $(MAKE) distclean
	@echo 

