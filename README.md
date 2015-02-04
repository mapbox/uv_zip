Makes [`libzip`](http://www.nih.at/libzip/) asynchronous by mimicing the `uv_fs_*` APIs.

# Usage

See [`test/test.cpp`](test/test.cpp)

# Testing

```bash
$ ./configure
[...]
$ make test
[...]
* open_failure (0.9ms)
* open_from_fd (0.9ms)
* missing_file (0.2ms)
* read_file (0.2ms)
```

**Note: This binding is not complete and only provides read-only support.**
