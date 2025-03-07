CC := gcc
LDLIBS := -Wall -Wextra -Werror -pthread -lcurl

SRC_DOWNLOADER = parallel_downloader.c
OBJS_PARALLEL_DOWNLOADER = $(SRC_DOWNLOADER:.c=.o)
TARGET_PARALELL_DOWNLOADER = parallel_downloader
TRASH_FILES = download_*

SRC_MATRIX_MULT = matrix_mult.c
OBJS_MATRIX_MULT = $(SRC_MATRIX_MULT:.c=.o)
TARGET_MATRIX_MULT = matrix_mult

TARGETS = $(TARGET_PARALLEL_DOWNLOADER) $(TARGET_MATRIX_MULT)
OBJS = $(OBJS_PARALLEL_DOWNLOADER) $(OBJS_MATRIX_MULT)

# Rule to build the parallel_downloader executable
$(TARGET_PARALLEL_DOWNLOADER): $(OBJS_PARALLEL_DOWNLOADER)
	$(CC) $(TARGET_PARALELL_DOWNLOADER) -o $(TARGET_PARALLEL_DOWNLOADER) $(LDLIBS)

# Rule to build the matrix_mult executable
$(TARGET_MATRIX_MULT): $(OBJS_MATRIX_MULT)
	$(CC) $(OBJS_MATRIX_MULT) -o $(TARGET_MATRIX_MULT) $(LDLIBS)

.PHONY: all
all: $(TARGETS)

# Clean up generated files
.PHONY: clean
clean:
	$(RM) $(TARGETS) $(OBJS) $(TRASH_FILES)