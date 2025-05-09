#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>

#define SHM_SIZE 10
const char* SHM_NAME = "/my_shm";

int main() {
    
}