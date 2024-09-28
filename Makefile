EXECUTABLE = test

CC = clang

DEPENDENCIES = \
	luajit

SOURCE_DIR := src
SOURCES := $(shell find $(SOURCE_DIR) -name '*.c')

BUILD_DIR := build
$(shell mkdir -p $(BUILD_DIR))

.PHONY = default clean format

# ------------------------------------------------------------------------------
# Builds
# ------------------------------------------------------------------------------

default: $(BUILD_DIR)/$(EXECUTABLE)
	@$(BUILD_DIR)/$(EXECUTABLE)

# ------------------------------------------------------------------------------
# Objects
# ------------------------------------------------------------------------------

CFLAGS := \
	$(shell pkg-config --cflags $(DEPENDENCIES)) \
	-I$(SOURCE_DIR)

OBJECT_BUILD_DIR := $(BUILD_DIR)/objects
$(shell mkdir -p $(OBJECT_BUILD_DIR))

$(OBJECT_BUILD_DIR)/script.o: $(SOURCE_DIR)/script.lua
	@cat $< | \
	sed 's/"/\\"/g' | \
	awk '{ printf "%s%s", separator, $$0; separator = "\\n" }' - | \
	xargs -0  printf '#include "lua_script.h"\nconst char* test_lua_script = "%s";' | \
	$(CC) -c $(CFLAGS) -o $@ -xc -

$(OBJECT_BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	@-mkdir -p $(@D)
	$(CC) -c $(CFLAGS) -o $@ $<

# ------------------------------------------------------------------------------
# Executable
# ------------------------------------------------------------------------------

LIBS := \
	$(shell pkg-config --libs $(DEPENDENCIES))

OBJECTS := $(SOURCES:$(SOURCE_DIR)/%.c=$(OBJECT_BUILD_DIR)/%.o) $(OBJECT_BUILD_DIR)/script.o

$(BUILD_DIR)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LIBS) -o $@ $^

# ------------------------------------------------------------------------------
# Clean
# ------------------------------------------------------------------------------

clean:
	if [[ -d $(BUILD_DIR) ]]; then rm -r $(BUILD_DIR); fi

# ------------------------------------------------------------------------------
# Format
# ------------------------------------------------------------------------------

format:
	clang-format -i $(shell find $(SOURCE_DIR) -type f -regex .*\.[ch]$)
