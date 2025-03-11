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

TARGETS = $(TARGET_PARALLEL_DOWNLOADER) $(TARGET_MATRIX_MULT) $(TARGET_IMAGE)
OBJS = $(OBJS_PARALLEL_DOWNLOADER) $(OBJS_MATRIX_MULT) $(OBJS_IMAGE)

############
### RULE ###
############

# Rule to build the parallel_downloader executable
$(TARGET_PARALLEL_DOWNLOADER): $(OBJS_PARALLEL_DOWNLOADER)

# Rule to build the matrix_mult executable
$(TARGET_MATRIX_MULT): $(OBJS_MATRIX_MULT)

# Rule to build the parallel_image_processing_sdl executable
$(TARGET_IMAGE): $(OBJS_IMAGE)

.PHONY: all
all: $(TARGETS)

# Clean up generated files
.PHONY: clean
clean:
	$(RM) $(TARGETS) $(OBJS) $(TRASH_FILES)