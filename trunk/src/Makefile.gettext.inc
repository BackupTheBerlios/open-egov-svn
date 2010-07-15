# $Id$

# All messages in the sources are english messages. If gettext asks
# to include a --from-code=iso-8859-1 or so it means there is still
# an untranslated german text. This is a bug.

THISDIR := $(notdir $(shell pwd))
SOURCES := $(shell ls -1 ../src/*.cpp | grep -v moc_ | grep -v SMTP | xargs)
#$(wildcard ../src/*.cpp)

EXTRACT := xgettext --add-location --no-wrap --sort-by-file --foreign-user --force-po \
           --trigraphs --default-domain=$(BASENAME) --add-comments --strict --language=C++ \
	   --msgid-bugs-address="mail@gerrit-albrecht.de" --keyword=_
#--extract-all
MERGE   := msgmerge --update --force-po --no-wrap --quiet
#--compendium=test.po
FORMAT  := msgfmt --check --use-fuzzy --statistics --strict
MSGINIT := msginit
#--verbose

LANGS   := $(shell find . -maxdepth 1 -type d -name "[a-zA-Z0-9]*" | sed 's/\.\///' | grep -v CVS | xargs)

.PHONY: $(DIRS)

%.mo: %.po
	rm -f $@.mo; msgfmt -o $@.mo $@.po
	test ! -f $@.mo || touch $@.mo

all:
	@echo "Parameters: init extract compile merge"

init:
	@for lang in $(LANGS); do \
		if ! test -e $$lang/$(BASENAME).po ; then \
			echo "Initializing $$lang/$(BASENAME).po ..." ;\
			$(MSGINIT) --input=$(BASENAME).pot --output-file=$$lang/$(BASENAME).po --no-wrap --locale=$$lang ;\
		fi;\
	done

extract:
	$(EXTRACT) -d $(BASENAME) -o $(BASENAME).pot --language=C++ --copyright-holder="Gerrit M. Albrecht" \
		   --msgid-bugs-address="mail@gerrit-albrecht.de" \
		   $(SOURCES)

merge:
	@for lang in $(LANGS); do \
		if test -w $$lang/$(BASENAME).po ; then \
			echo "Merging $$lang/$(BASENAME).po ..."; \
			$(MERGE) $$lang/$(BASENAME).po $(BASENAME).pot ; \
		fi; \
	done

compile:
	@for lang in $(LANGS); do \
		if test -e $$lang/$(BASENAME).po ; then \
			echo "Compiling $$lang/$(BASENAME).po ..."; \
			$(FORMAT) --output-file=$$lang/LC_MESSAGES/$(BASENAME).mo $$lang/$(BASENAME).po ; \
		fi; \
	done

install:
	sudo cp de_DE/LC_MESSAGES/$(BASENAME).mo /usr/share/locale/de/LC_MESSAGES/$(BASENAME).mo


