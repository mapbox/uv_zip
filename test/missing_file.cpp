#include <uv_zip.h>
#include "assert.hpp"
#include <string>

void missing_file() {
    START_TEST(missing_file)
    static uv_loop_t *loop = uv_loop_new();

    uv_zip_t *zip = new uv_zip_t();
    uv_zip_init(zip);
    uv_zip_open(loop, zip, "test/content.zip", 0, [](uv_zip_t *zip1) {
        ASSERT(zip1->result == 0, "Opening the zip file failed");

        uv_zip_fopen(loop, zip1, "missing.txt", 0, [](uv_zip_t *zip2) {
            ASSERT(zip2->result == -ZIP_ER_NOENT, "Opening the zip file succeeded even though it should fail");
            ASSERT(zip2->file == nullptr, "Does not have a zip file pointer");
            ASSERT((std::string {"No such file"} == zip2->message), "Error message wrong");

            uv_zip_cleanup(zip2);
            delete zip2;
            FINISH_TEST(missing_file)
        });
    });

    uv_run(loop, UV_RUN_DEFAULT);
    uv_loop_delete(loop);

    FINISHED_TEST(missing_file)
}
