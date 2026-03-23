CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -O2 -Iinclude
SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c,build/%.o,$(SRC))
TARGET := build/sysmate
USER_INSTALL_PATH := $(HOME)/.local/bin

.PHONY: all clean run install-user uninstall-user help

all: $(TARGET)

build:
	mkdir -p build

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf build

install-user: $(TARGET)
	mkdir -p $(USER_INSTALL_PATH)
	cp $(TARGET) $(USER_INSTALL_PATH)/sysmate
	chmod +x $(USER_INSTALL_PATH)/sysmate
	@echo "Installed to $(USER_INSTALL_PATH)/sysmate"
	@echo "If sysmate is not found, add this to your shell:"
	@echo "export PATH=\"$$HOME/.local/bin:$$PATH\""
	@echo "Then run:"
	@echo "source ~/.bashrc"

uninstall-user:
	rm -f $(USER_INSTALL_PATH)/sysmate
	@echo "Removed from $(USER_INSTALL_PATH)"

help:
	@echo "Available targets:"
	@echo "  make               Build the project"
	@echo "  make run           Run sysmate from build/"
	@echo "  make clean         Remove build files"
	@echo "  make install-user  Install sysmate for current user"
	@echo "  make uninstall-user Remove user installation"
	rm -f build
 