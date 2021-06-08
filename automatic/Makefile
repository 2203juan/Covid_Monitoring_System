#
# Makefile for make
#
# Compiler: gcc
#

PROGS   =  covidFSMtrc
CFLAGST = -D_REENTRANT -Wall
LIBS    = pthread

all: $(PROGS)



covidFSMtrc : phtrdsMsgLyr.o covidTrc.o
	$(CC) $(CFLAGST) -o covidFSMtrc covidTrc.o phtrdsMsgLyr.o -l $(LIBS)

phtrdsMsgLyr.o : phtrdsMsgLyr.c phtrdsMsgLyr.h pMLusrConf.h
	$(CC) $(CFLAGST) -g -c phtrdsMsgLyr.c


covidTrc.o : covidTrc.c pMLusrConf.h
	$(CC) $(CFLAGST) -g -c covidTrc.c

clean:
	rm -f $(PROGS) *~ *.o