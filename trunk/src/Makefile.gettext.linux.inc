# $Id$

SOURCES := $(shell ls -1 ../src/*.cpp | grep -v moc_ | grep -v SMTP | xargs)

EXTRACT := xgettext $(EXTRACT_FLAGS) --default-domain=$(BASE_NAME)
MERGE   := msgmerge $(MERGE_FLAGS)
FORMAT  := msgfmt $(FORMAT_FLAGS)
MSGINIT := msginit $(MSGINIT_FLAGS)

LANGS   := $(shell find . -maxdepth 1 -type d -name "[a-zA-Z0-9]*" | sed 's/\.\///' | grep -v CVS | grep -v .svn | xargs)

.PHONY: $(DIRS)

%.mo: %.po
	rm -f $@.mo; msgfmt -o $@.mo $@.po
	test ! -f $@.mo || touch $@.mo

init:
	@for lang in $(LANGS); do \
		if ! test -e $$lang/$(BASE_NAME).po ; then \
			echo "Initializing $$lang/$(BASE_NAME).po ..." ;\
			$(MSGINIT) --input=$(BASE_NAME).pot --output-file=$$lang/$(BASE_NAME).po --locale=$$lang ;\
		fi;\
	done

extract:
	$(EXTRACT) -d $(BASE_NAME) -o $(BASE_NAME).pot --language=C++ --copyright-holder="Gerrit M. Albrecht" \
		   --msgid-bugs-address="mail@gerrit-albrecht.de" \
		   $(SOURCES)

merge:
	@for lang in $(LANGS); do \
		if test -w $$lang/$(BASE_NAME).po ; then \
			echo "Merging $$lang/$(BASE_NAME).po ..."; \
			$(MERGE) $$lang/$(BASE_NAME).po $(BASE_NAME).pot ; \
		fi; \
	done

compile:
	@for lang in $(LANGS); do \
		if test -e $$lang/$(BASE_NAME).po ; then \
			echo "Compiling $$lang/$(BASE_NAME).po ..."; \
			$(FORMAT) --output-file=$$lang/LC_MESSAGES/$(BASE_NAME).mo $$lang/$(BASE_NAME).po ; \
		fi; \
	done

install:
	sudo cp de_DE/LC_MESSAGES/$(BASE_NAME).mo /usr/share/locale/de/LC_MESSAGES/$(BASE_NAME).mo


