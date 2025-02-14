#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

typedef char * caddr_t;
extern char _end;

caddr_t _sbrk(int incr) {
    static char *heap_end = 0;
    char *prev_heap_end;

    if (heap_end == 0) {
        heap_end = &_end;
    }
    prev_heap_end = heap_end;
    heap_end += incr;
    return (caddr_t) prev_heap_end;
}

int _write(int file, char *ptr, int len) {
    return len;
}

int _read(int file, char *ptr, int len) {
    return 0;
}

int _close(int file) {
    return -1;
}

int _lseek(int file, int ptr, int dir) {
    return 0;
}

int _fstat(int file, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

void _exit(int status) {
    while (1);
}
