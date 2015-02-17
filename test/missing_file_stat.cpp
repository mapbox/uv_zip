#include <uv_zip.h>
#include "assert.hpp"
#include <string>

void missing_file_stat() {
    START_TEST(missing_file_stat)
    static uv_loop_t *loop = uv_loop_new();

    uv_zip_t *zip = new uv_zip_t();
    uv_zip_init(zip);
    uv_zip_open(loop, zip, "test/content.zip", 0, [](uv_zip_t *zip2) {
        ASSERT(zip2, "Zip object is NULL");
        ASSERT(zip2->result == 0, "Opening the zip file failed");

        uv_zip_stat(loop, zip2, "missing.txt", 0, [](uv_zip_t *zip3) {
            ASSERT(zip3, "Zip object is NULL");
            ASSERT(zip3->result == -ZIP_ER_NOENT, "Stating the zip file succeeded even though it should fail");
            ASSERT(zip3->file == nullptr, "Does not have a zip file pointer");
            ASSERT((std::string {"No such file"} == zip3->message), "Error message wrong");

            uv_zip_discard(loop, zip3, [](uv_zip_t *zip4) {
                ASSERT(zip4, "Zip object is NULL");
                ASSERT(zip4->result == 0, "Closing the zip file failed");
                uv_zip_cleanup(zip4);
                delete zip4;
                FINISH_TEST(missing_file_stat)
            });
        });
    });

    uv_run(loop, UV_RUN_DEFAULT);
    uv_loop_delete(loop);

    FINISHED_TEST(missing_file_stat)
}
