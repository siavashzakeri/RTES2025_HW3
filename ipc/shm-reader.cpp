#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cctype>

#define SHM_SIZE 10
const char* SHM_NAME = "/my_shm";

int main() {
    int fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    if (fd == -1) { perror("shm_open"); return 1; }

    const char* buf = static_cast<const char*>(mmap(nullptr, SHM_SIZE,
                              PROT_READ, MAP_SHARED, fd, 0));
    if (buf == MAP_FAILED) { perror("mmap"); return 1; }

    std::string out;
    for (int i = 0; i < SHM_SIZE; ++i)
        if (std::isprint(static_cast<unsigned char>(buf[i])))
            out.push_back(buf[i]);

    std::cout << "SHM Content: \"" << out << "\"\n";

    munmap(const_cast<char*>(buf), SHM_SIZE);
    close(fd);
    return 0;
}
