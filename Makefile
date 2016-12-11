CC = gcc
CFLAGS = -lm -Wall -g -std=c99
OS = $(shell uname)
ifeq ($(OS), Darwin)
    LDFLAGS = -F/Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_mixer
    IFLAGS = -I/Library/Frameworks/SDL2.framework/Headers/ -I/Library/Frameworks/SDL2_image.framework/Headers/ -I/Library/Frameworks/SDL2_mixer.framework/Headers/
else
    LDFLAGS = -lSDL2-2.0 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
endif
SRC_DIR         = src
OBJ_DIR         = obj
BIN_DIR         = bin

PROG = $(OBJ_DIR)/MapObject.o $(OBJ_DIR)/GameSDL.o $(OBJ_DIR)/main.o $(OBJ_DIR)/module.o $(OBJ_DIR)/player.o $(OBJ_DIR)/GameState.o
PROG_OUT			= Numsefisk

all: $(BIN_DIR)/$(PROG_OUT)

$(BIN_DIR)/$(PROG_OUT): $(PROG)
	$(CC) $(CFLAGS) $(PROG) -o $@ $(LDFLAGS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS) $(IFLAGS)

clean:
	rm -Rf $(OBJ_DIR)/*.o
	rm -Rf $(BIN_DIR)/*
