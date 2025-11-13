# Program Variables
PROGNAME := ParticleLife
SOURCE_DIR := ./source
INCLUDE_DIR := ./include
BUILD_DIR := ./build

# Compilation Variables
CC := gcc
CFLAGS := -Wall -Wextra -Werror -Ivendor/raylib/include
LDFLAGS := -Lvendor/raylib/lib
LIBS := -lraylib -lm -lpthread -ldl

# Create all corresponding .o files from .c filenames
SOURCES := $(wildcard $(SOURCE_DIR)/*.c)
OBJECTS := $(patsubst $(SOURCE_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

.PHONY: all clean

all: $(PROGNAME)

# Link all the object files into the final program
$(PROGNAME): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS) $(LIBS)

# Compile each .c file to .o file
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if it does not exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	$(RM) -r $(BUILD_DIR)/*.o $(PROGNAME)