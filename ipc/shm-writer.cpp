#include <iostream>
#include <fcntl.h>      // shm_open
#include <sys/mman.h>   // mmap, PROT_*, MAP_*
#include <sys/stat.h>   // mode constants
#include <unistd.h>     // ftruncate, close
#include <cstring>      // memset

#define SHM_SIZE 10
const char* SHM_NAME = "/my_shm";

int main() {
    
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd == -1) { perror("shm_open"); return 1; }

    if (ftruncate(fd, SHM_SIZE) == -1) { perror("ftruncate"); return 1; }

    char* buf = static_cast<char*>(mmap(nullptr, SHM_SIZE,
                                        PROT_READ | PROT_WRITE,
                                        MAP_SHARED, fd, 0));
    if (buf == MAP_FAILED) { perror("mmap"); return 1; }

    static bool first = true;
    if (first) { memset(buf, '\0', SHM_SIZE); first = false; }

    std::cout << "Enter text (max 10 chars shown circularly):\n";
    size_t head = 0;
    std::string line;
    while (std::getline(std::cin, line)) {
        for (char c : line) {
            buf[head] = c;
            head = (head + 1) % SHM_SIZE;
        }
    }

    munmap(buf, SHM_SIZE);
    close(fd);  
    return 0;
}
