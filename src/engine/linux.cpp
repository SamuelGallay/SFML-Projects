#include "engine.h"
#include <unistd.h>

std::string getExecutablePath(){
    char buf[1024];
    ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf)-1);

    if (len != -1) {
        buf[len] = '\0';
        std::string s(buf);
        return s;
    }
    else {
        return "";
    }
}
