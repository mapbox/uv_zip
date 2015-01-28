#include <uv_zip.h>
#include "assert.hpp"
#include <string>

void read_file() {
    START_TEST(read_file)
    static uv_loop_t *loop = uv_loop_new();

    uv_zip_t *zip = new uv_zip_t();
    uv_zip_init(zip);
    uv_zip_open(loop, zip, "test/content.zip", 0, [](uv_zip_t *zip) {
        ASSERT(zip->result == 0, "Opening the zip file failed");

        uv_zip_fopen(loop, zip, "content.txt", 0, [](uv_zip_t *zip) {
            ASSERT(zip->result == 0, "Opening the zip file content failed");
            ASSERT(zip->file != nullptr, "Does not have a zip file pointer");

            uv_buf_t *buf = new uv_buf_t;
            *buf = uv_buf_init(new char[128], 128);

            uv_zip_fread(loop, zip, zip->file, buf, [](uv_zip_t *zip) {
                ASSERT(zip->result == 13, "Incorrect amount of bytes read");
                ASSERT((std::string {"content here\n"} == std::string { zip->buf->base, size_t(zip->result) }), "Incorrect content read");

                uv_zip_cleanup(zip);
                delete zip;
                FINISH_TEST(read_file)
            });
        });
    });

    uv_run(loop, UV_RUN_DEFAULT);
    uv_loop_delete(loop);

    FINISHED_TEST(read_file)
}
