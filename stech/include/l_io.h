#include <sys/stat.h>
#include <stdbool.h>

bool FileExists(const char *filename)
{
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}