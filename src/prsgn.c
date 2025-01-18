#include "parse_tree_type.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

void print_usage()
{
	printf("Usage: %s file\n", TARGET);
	printf("parser generator\n");
	printf("\n");
	printf("JD297 %s source code <https://github.com/jd297/prsgn>\n", TARGET);
}

#define HANDLE_ERROR(object, error) fprintf(stderr, "%s: %s: %s\n", TARGET, object, strerror(error)); \
                                    exit(EXIT_FAILURE);

int main(int argc, char **argv)
{
    (void)argv;

    if (argc != 2) {
        print_usage();
		exit(EXIT_FAILURE);
    }
    
    struct stat sb;

	if (stat(argv[optind], &sb) == -1) {
		HANDLE_ERROR(argv[optind], errno);
	}

	if ((sb.st_mode & S_IFMT) == S_IFDIR) {
		HANDLE_ERROR(argv[optind], EISDIR);
	}

	int fd;

	if ((fd = open(argv[optind], O_RDONLY)) == -1) {
		HANDLE_ERROR(argv[optind], errno);
	}

	char *buf = (char *)mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

	if (buf == MAP_FAILED) {
		HANDLE_ERROR("mmap", errno);
	}

    parse_tree_type_generate(buf, "C");

	if (munmap(buf, sb.st_size) == -1) {
		HANDLE_ERROR("munmap", errno);
	}

	if (close(fd) == -1) {
		HANDLE_ERROR(argv[optind], errno);
	}

	return 0;
}
