#include <uv_zip.h>
#include "assert.hpp"
#include <string>

void stat_file() {
    START_TEST(stat_file)
    static uv_loop_t *loop = uv_loop_new();

    uv_zip_t *zip = new uv_zip_t();
    uv_zip_init(zip);
    uv_zip_open(loop, zip, "test/content.zip", 0, [](uv_zip_t *zip1) {
        ASSERT(zip1, "Zip object is NULL");
        ASSERT(zip1->result == 0, "Opening the zip file failed");

        uv_zip_stat(loop, zip1, "content.txt", 0, [](uv_zip_t *zip2) {
            ASSERT(zip2, "Zip object is NULL");
            ASSERT(zip2->result == 0, "Stating the zip file failed");
            ASSERT(zip2->stat->valid & ZIP_STAT_SIZE, "No file size");
            ASSERT(zip2->stat->size == 13, "Incorrect file size");
            ASSERT(zip2->stat->valid & ZIP_STAT_MTIME, "No modification time");
            ASSERT(zip2->stat->mtime > 1420000000L, "Incorrect modification time")

            uv_zip_discard(loop, zip2, [](uv_zip_t *zip3) {
                ASSERT(zip3, "Zip object is NULL");
                ASSERT(zip3->result == 0, "Closing the zip file failed");
                uv_zip_cleanup(zip3);
                delete zip3;
                FINISH_TEST(stat_file)
            });
        });
    });

    uv_run(loop, UV_RUN_DEFAULT);
    uv_loop_delete(loop);

    FINISHED_TEST(stat_file)
}
