# $Id$

SOURCES=$(wildcard *.xml)
TARGETS=$(SOURCES:%.xml=%.db)

CREATEDB=..\bin\createdatabase.exe

%.db: %.xml
	$(CREATEDB) $<

all: $(TARGETS)

clean:
	del $(TARGETS)
