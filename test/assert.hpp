#pragma once

#include <cstdio>
#include <cstdlib>

#define ASSERT(result, message) \
    if (!(result)) { \
        fprintf(stderr, "\033[31;1mASSERTION FAILED in %s:%d: %s\033[0m\n", __FILE__, __LINE__, message); \
        fprintf(stderr, "Comparison was: " #result "\n"); \
        abort(); \
    }

#define START_TEST(name) \
    static bool TEST_ ## name ## _completed = ([]() { \
        atexit([]() { \
            ASSERT(TEST_ ## name ## _completed, "Test \"" #name "\" did not complete"); \
        }); \
        return false; \
    })(); \
    static uint64_t TEST_ ## name ## _started = uv_hrtime();

#define FINISH_TEST(name) \
    do { \
        ASSERT(!TEST_ ## name ## _completed, "Test \"" #name "\" has already been completed"); \
        fprintf(stderr, "\033[32;1m* %s (%.1fms)\033[0m\n", #name, double(uv_hrtime() - TEST_ ## name ## _started) / 1e6); \
        TEST_ ## name ## _completed = true; \
    } while (false);

#define FINISHED_TEST(name) \
    do { \
        ASSERT(TEST_ ## name ## _completed, "Test \"" #name "\" did not complete"); \
    } while (false);
