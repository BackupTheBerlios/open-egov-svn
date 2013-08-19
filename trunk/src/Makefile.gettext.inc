# $Id$

# All messages in the sources are english messages. If gettext asks
# to include a --from-code=iso-8859-1 or so it means there is still
# an untranslated german text. This would be a bug.

TOP_DIR    ?= $(abspath $(CURDIR))
MF_DIR     ?= $(dir $(lastword $(MAKEFILE_LIST)))
BASE_DIR   ?= $(abspath $(join $(dir $(lastword $(MAKEFILE_LIST))),/..))
BASE_NAME  := $(notdir $(abspath $(join $(TOP_DIR),/..)))
BIN_DIR    ?= $(abspath $(join $(BASE_DIR),/bin))
LOCALE_DIR ?= $(abspath $(join $(BASE_DIR),/locale))

LANGS      := $(sort $(dir $(wildcard $(LOCALE_DIR)/*_*/)))
LANG_CODES := $(sort $(notdir $(abspath $(LANGS))))


MERGE_FLAGS   := --update --force-po --no-wrap --quiet
#--compendium=test.po

FORMAT_FLAGS  := --check --use-fuzzy --statistics --strict

EXTRACT_FLAGS := --add-location --no-wrap --foreign-user --force-po \
                 --trigraphs --add-comments --strict --indent --sort-output --width=76 \
                 --copyright-holder="Open E-Government Project" --keyword=_ \
                 --msgid-bugs-address="msgid-bugs@open-egov.de" --language=C++
#--extract-all --omit-header  --sort-by-file statt --sort-output

MSGINIT_FLAGS := --no-wrap
#--color --style=$(join $(BASE_DIR),\share\gettext\styles\po-default.css)
#don't use --no-translator

MSGCAT_FLAGS := --no-location --use-first --unique --no-wrap --strict --to-code=UTF-8


#$(info $(OS))
#$(info $(PROCESSOR_ARCHITECTURE))

ifeq ($(OS),Windows_NT)
  CMDSEP = &

  #CCFLAGS += -D WIN32
  ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
    #CCFLAGS += -D AMD64
  endif
  ifeq ($(PROCESSOR_ARCHITECTURE),x86)
    #CCFLAGS += -D IA32
  endif

  include $(MF_DIR)/Makefile.gettext.windows.inc
else
  CMDSEP = ;

  UNAME_S := $(shell uname -s)
  UNAME_P := $(shell uname -p)

  ifeq ($(UNAME_S),Linux)
    #CCFLAGS += -D LINUX
  endif
  ifeq ($(UNAME_S),Darwin)
    #CCFLAGS += -D OSX
  endif

  ifeq ($(UNAME_P),x86_64)
    #CCFLAGS += -D AMD64
  endif
  ifneq ($(filter %86,$(UNAME_P)),)
    #CCFLAGS += -D IA32
  endif
  ifneq ($(filter arm%,$(UNAME_P)),)
    #CCFLAGS += -D ARM
  endif

  include Makefile.gettext.linux.inc
endif

all:
	@echo Parameters: check init extract compile merge install

