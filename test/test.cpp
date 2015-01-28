#include <uv_zip.h>
#include "assert.hpp"
#include <string>

void open_failure();
void open_from_fd();
void missing_file();
void read_file();

int main() {
    open_failure();
    open_from_fd();
    missing_file();
    read_file();
    return 0;
}
