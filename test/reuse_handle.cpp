#include <uv_zip.h>
#include "assert.hpp"
#include <string>

void reuse_handle() {
    START_TEST(reuse_handle_after_error)
    static uv_loop_t *loop = uv_loop_new();

    uv_zip_t *zip = new uv_zip_t();
    uv_zip_init(zip);
    uv_zip_open(loop, zip, "test/content.zip", 0, [](uv_zip_t *zip1) {
        ASSERT(zip1, "Zip object is NULL");
        ASSERT(zip1->result == 0, "Opening the zip file failed");

        uv_zip_fopen(loop, zip1, "empty_dir", 0, [](uv_zip_t *zip2) {
            ASSERT(zip2, "Zip object is NULL");
            ASSERT(zip2->result == -ZIP_ER_NOENT, "Opening the zip file failed");

            uv_zip_fopen(loop, zip2, "content.txt", 0, [](uv_zip_t *zip4) {
                ASSERT(zip4, "Zip object is NULL");
                ASSERT(zip4->result == 0, "Opening the zip file failed");

                uv_zip_fclose(loop, zip4, zip4->file, [](uv_zip_t *zip5) {
                    ASSERT(zip5, "Zip object is NULL");
                    ASSERT(zip5->result == 0, "Stating the zip file failed");

                    uv_zip_discard(loop, zip5, [](uv_zip_t *zip6) {
                        ASSERT(zip6, "Zip object is NULL");
                        ASSERT(zip6->result == 0, "Closing the zip file failed");
                        uv_zip_cleanup(zip6);
                        delete zip6;
                        FINISH_TEST(reuse_handle_after_error)
                    });
                });
            });
        });
    });

    uv_run(loop, UV_RUN_DEFAULT);
    uv_loop_delete(loop);

    FINISHED_TEST(reuse_handle_after_error)
}
