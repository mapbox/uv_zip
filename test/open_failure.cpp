#include <uv_zip.h>
#include "assert.hpp"
#include <string>

void open_failure() {
    START_TEST(open_failure)
    static uv_loop_t *loop = uv_loop_new();

    uv_zip_t *zip = new uv_zip_t();
    uv_zip_init(zip);
    uv_zip_open(loop, zip, "test/doesnotexist.zip", 0, [](uv_zip_t *zip) {
        ASSERT(zip->result == -ZIP_ER_OPEN, "Opening the zip file failed");
        ASSERT(std::string {"Can't open file: No such file or directory"} == zip->message, "Error message wrong");
        uv_zip_cleanup(zip);
        delete zip;
        FINISH_TEST(open_failure)
    });

    uv_run(loop, UV_RUN_DEFAULT);
    uv_loop_delete(loop);

    FINISHED_TEST(open_failure)
}
