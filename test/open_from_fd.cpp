#include <uv_zip.h>
#include "assert.hpp"
#include <string>

void open_from_fd() {
    START_TEST(open_from_fd)
    static uv_loop_t *loop = uv_loop_new();

    uv_fs_open(loop, new uv_fs_t(), "test/empty.zip", O_RDONLY, S_IRUSR, [](uv_fs_t *req) {
        ASSERT(req->result > 0, "Opening the file failed");

        uv_file fd = uv_file(req->result);
        uv_fs_req_cleanup(req);

        uv_zip_t *zip = new uv_zip_t();
        uv_zip_init(zip);
        uv_zip_fdopen(loop, zip, fd, 0, [](uv_zip_t *zip1) {
            ASSERT(zip1, "Zip object is NULL");
            ASSERT(zip1->result == 0, "Opening the zip file failed");

            uv_zip_discard(loop, zip1, [](uv_zip_t *zip2) {
                ASSERT(zip2, "Zip object is NULL");
                ASSERT(zip2->result == 0, "Closing the zip file failed");
                uv_zip_cleanup(zip2);
                delete zip2;
                FINISH_TEST(open_from_fd)
            });
        });
    });

    uv_run(loop, UV_RUN_DEFAULT);
    uv_loop_delete(loop);

    FINISHED_TEST(open_from_fd)
}
