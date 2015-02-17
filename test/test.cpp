#include <uv_zip.h>
#include "assert.hpp"
#include <string>

void open_failure();
void open_from_fd();
void missing_file();
void missing_file_stat();
void read_file();
void stat_file();
void reuse_handle();

int main() {
    open_failure();
    open_from_fd();
    missing_file();
    missing_file_stat();
    read_file();
    stat_file();
    reuse_handle();
    return 0;
}
