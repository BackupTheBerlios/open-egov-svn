# $Id$

SOURCES    := $(wildcard ../src/*.cpp)

MERGE      := $(BIN_DIR)/msgmerge $(MERGE_FLAGS)
FORMAT     := $(BIN_DIR)/msgfmt $(FORMAT_FLAGS)
# = and not := because we overwrite BASE_NAME for library po files.
EXTRACT     = $(BIN_DIR)/xgettext $(EXTRACT_FLAGS) --default-domain=$(BASE_NAME) \
	          --output-dir=$(TOP_DIR) --output=$(BASE_NAME).pot
MSGINIT     = $(BIN_DIR)/msginit $(MSGINIT_FLAGS) --input=$(BASE_NAME).pot
MSGCAT     := $(BIN_DIR)/msgcat $(MSGCAT_FLAGS)


new_all:

check:
	@echo TOP_DIR    = $(TOP_DIR)
	@echo BASE_DIR   = $(BASE_DIR)
	@echo BASE_NAME  = $(BASE_NAME)
	@echo BIN_DIR    = $(BIN_DIR)
	@echo LOCALE_DIR = $(LOCALE_DIR)
	@echo SOURCES    = $(SOURCES)
	@echo LANGS      = $(LANGS)
	$(foreach LANG,$(LANGS), \
		@echo LANG = $(notdir $(abspath $(LANG))) $(CMDSEP) )
	@echo LANG_CODES = $(LANG_CODES)

init:
	$(foreach L_CODE,$(LANG_CODES), \
		$(if $(wildcard $(join $(L_CODE),.po)), \
			@echo File already exists (skipped): $(L_CODE).po, \
			@echo Initializing file: $(L_CODE).po $(CMDSEP) \
			@$(MSGINIT) --output-file=$(L_CODE).po --locale=$(L_CODE) \
		) $(CMDSEP) \
	)

# --join-existing
extract:
	$(if $(wildcard $(BASE_NAME).pot), \
		$(EXTRACT) $(SOURCES), \
		$(EXTRACT) $(SOURCES))

compile:
	$(foreach L_CODE,$(LANG_CODES), \
		$(if $(wildcard $(join $(L_CODE),.po)), \
			@echo Compiling file: $(L_CODE).po $(CMDSEP) \
			@$(MSGCAT) $(L_CODE).po $(BASE_DIR)/src/libraries/OEG/Qt/locale/$(L_CODE).po --output-file=%TEMP%/compile.po $(CMDSEP) \
			@$(FORMAT) --output-file=$(LOCALE_DIR)/$(L_CODE)/LC_MESSAGES/$(BASE_NAME).mo %TEMP%/compile.po, \
			@echo File not found: $(L_CODE).po \
		) $(CMDSEP) \
	)

merge:
	$(foreach L_CODE,$(LANG_CODES), \
		$(if $(wildcard $(join $(L_CODE),.po)), \
			@echo Merging file: $(L_CODE).po $(CMDSEP) \
			@$(MERGE) $(L_CODE).po $(BASE_NAME).pot, \
			@echo File not found: $(L_CODE).po \
		) $(CMDSEP) \
	)

install:
	$(warning Install is not functional on Windows platforms. Use the WiX installer scripts.)

