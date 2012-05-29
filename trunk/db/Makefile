# $Id$

SOURCES=$(wildcard *.xml)
TARGETS=$(SOURCES:%.xml=%.db)

CREATEDB=..\bin\createdatabase.exe

%.db: %.xml
	del $@
	$(CREATEDB) --verbose $<

all: $(TARGETS)

clean:
	del $(TARGETS)
