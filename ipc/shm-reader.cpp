#include <iostream>
#include <fcntl.h>           // For shm_open
#include <sys/mman.h>        // For mmap
#include <unistd.h>
#include <cerrno>
#include <cstring>

#define SHM_SIZE 10
const char* SHM_NAME = "/my_shm";  // POSIX shared memory name

int main() {

    return 0;
}