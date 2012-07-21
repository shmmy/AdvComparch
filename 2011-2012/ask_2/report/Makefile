TARGET = adv-comparch-ask2
CC = xelatex
CCFLAGS = -shell-escape

all: $(TARGET).pdf

%.pdf:	%.tex title/* files/*
	$(CC) $(CCFLAGS) $<


.PHONY:	clean all spell
clean:
	rm -f $(TARGET).{pdf,log,aux,pyg}

spell:
	aspell -l el_gr --ignore-case=true -c $(TARGET).tex
