# Program Variables
PROGNAME := ParticleLife
SOURCE_DIR := ./source
INCLUDE_DIR := ./include
BUILD_DIR := ./build

# Compilation Variables
CC := gcc
CFLAGS := -Wall -Wextra -Werror -Ivendor/SDL3/include
LDFLAGS := -lm -lSDL3 -Lvendor/SDL3/libraries
RPATH := -Wl,-rpath,'$$ORIGIN/vendor/SDL3/libraries'

# Create all corresponding .o files from .c filenames
SOURCES := $(wildcard $(SOURCE_DIR)/*.c)
OBJECTS := $(patsubst $(SOURCE_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

# Cleanup variables
RM := rm -rf

.PHONY: all clean

all: $(PROGNAME)

# link all the object files in the final program exe
$(PROGNAME): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS) $(RPATH)

# Compile each .c file into .o file
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create the build directory if it does not exist
$(BUILD_DIR):
	mkdir -p $@

# clean up .o files and exe
clean:
	$(RM) $(BUILD_DIR)/*.o $(PROGNAME)