CC := gcc
CFLAGS := -Wall -Wextra -Werror
LDLIBS := -pthread -lSDL2 -lSDL2_image -lcurl

SRC_DOWNLOADER = parallel_downloader.c
OBJS_PARALLEL_DOWNLOADER = $(SRC_DOWNLOADER:.c=.o)
TARGET_PARALLEL_DOWNLOADER = parallel_downloader
TRASH_FILES = download_* resources/grayscale_image.bmp

SRC_MATRIX_MULT = matrix_mult.c
OBJS_MATRIX_MULT = $(SRC_MATRIX_MULT:.c=.o)
TARGET_MATRIX_MULT = matrix_mult

SRC_IMAGE = parallel_image_processing_sdl.c
OBJS_IMAGE = $(SRC_IMAGE:.c=.o)
TARGET_IMAGE = parallel_image_processing_sdl

SRC_SERVER = server_reservation.c
OBJS_SERVER = $(SRC_SERVER:.c=.o)
TARGET_SERVER = server

SRC_CLIENT = client_reservation.c
OBJS_CLIENT = $(SRC_CLIENT:.c=.o)
TARGET_CLIENT = client

TARGETS = $(TARGET_PARALLEL_DOWNLOADER) $(TARGET_MATRIX_MULT) $(TARGET_IMAGE) $(TARGET_SERVER) $(TARGET_CLIENT)
OBJS = $(OBJS_PARALLEL_DOWNLOADER) $(OBJS_MATRIX_MULT) $(OBJS_IMAGE) $(OBJS_SERVER) $(OBJS_CLIENT)

############
### RULE ###
############

# Rule to build the parallel_downloader executable
$(TARGET_PARALLEL_DOWNLOADER): $(OBJS_PARALLEL_DOWNLOADER)

# Rule to build the matrix_mult executable
$(TARGET_MATRIX_MULT): $(OBJS_MATRIX_MULT)

# Rule to build the parallel_image_processing_sdl executable
$(TARGET_IMAGE): $(OBJS_IMAGE)

# Rule to build the server (Should be complete first)
$(TARGET_SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) -o $@ $(LDLIBS)
# Rule to build the client
$(TARGET_CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -o $@ $(LDLIBS)
.PHONY: all
all: $(TARGETS)

# Clean up generated files
.PHONY: clean
clean:
	$(RM) $(TARGETS) $(OBJS) $(TRASH_FILES)