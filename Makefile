CC := gcc
LDLIBS := -Wall -Wextra -Werror -pthread -lcurl

SRC_DOWNLOADER = parallel_downloader.c
OBJS_PARALLEL_DOWNLOADER = $(SRC_DOWNLOADER:.c=.o)
TARGET_PARALELL_DOWNLOADER = parallel_downloader
TRASH_FILES = download_*

# Rule to build the parallel_downloader executable
$(TARGET_PARALLEL_DOWNLOADER): $(OBJS_PARALLEL_DOWNLOADER)
	$(CC) $(TARGET_PARALELL_DOWNLOADER) -o $(TARGET_PARALLEL_DOWNLOADER) $(LDLIBS)

# Clean up generated files
.PHONY: clean
clean:
	$(RM) $(TARGET_PARALELL_DOWNLOADER) $(OBJS_PARALLEL_DOWNLOADER) $(TRASH_FILES)