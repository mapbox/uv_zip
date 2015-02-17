#include <uv_zip.h>
#include "assert.hpp"
#include <string>

void read_file() {
    START_TEST(read_file)
    static uv_loop_t *loop = uv_loop_new();

    uv_zip_t *zip = new uv_zip_t();
    uv_zip_init(zip);
    uv_zip_open(loop, zip, "test/content.zip", 0, [](uv_zip_t *zip1) {
        ASSERT(zip1, "Zip object is NULL");
        ASSERT(zip1->result == 0, "Opening the zip file failed");

        uv_zip_fopen(loop, zip1, "content.txt", 0, [](uv_zip_t *zip2) {
            ASSERT(zip2, "Zip object is NULL");
            ASSERT(zip2->result == 0, "Opening the zip file content failed");
            ASSERT(zip2->file != nullptr, "Does not have a zip file pointer");

            uv_buf_t *buf = new uv_buf_t;
            *buf = uv_buf_init(new char[128], 128);

            uv_zip_fread(loop, zip2, zip2->file, buf, [](uv_zip_t *zip3) {
                ASSERT(zip3, "Zip object is NULL");
                ASSERT(zip3->result == 13, "Incorrect amount of bytes read");
                ASSERT((std::string {"content here\n"} == std::string { zip3->buf->base, size_t(zip3->result) }), "Incorrect content read");

                uv_zip_fclose(loop, zip3, zip3->file, [](uv_zip_t *zip4) {
                    ASSERT(zip4, "Zip object is NULL");
                    ASSERT(zip4->result == 0, "Closing the zip file content failed");

                    uv_zip_discard(loop, zip4, [](uv_zip_t *zip5) {
                        ASSERT(zip5, "Zip object is NULL");
                        ASSERT(zip5->result == 0, "Closing the zip file failed");
                        uv_zip_cleanup(zip5);
                        delete zip5;
                        FINISH_TEST(read_file)
                    });
                });
            });
        });
    });

    uv_run(loop, UV_RUN_DEFAULT);
    uv_loop_delete(loop);

    FINISHED_TEST(read_file)
}
