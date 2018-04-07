#Makefile for pthread_pi Monte Carlo Program
#
#Maria Bamundo Siena College 10/25/17
#

CFILES = pthread_pi.c
OFILES=$(CFILES:.c=.o)

CC=gcc

pthread_pi:	$(OFILES)
	$(CC) -o pthread_pi $(OFILES) -lpthread -lm

clean::
	/bin/rm -f pthreadhello $(OFILES)
