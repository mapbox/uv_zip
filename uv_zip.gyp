{
  'target_defaults': {
    'default_configuration': 'Release',
    'cflags_cc': [ '-std=c++11', '-Wall', '-Wextra', '-Wshadow', '-frtti', '-fexceptions' ],
    'xcode_settings': {
      'OTHER_CPLUSPLUSFLAGS': [ '-std=c++11', '-Wall', '-Wextra', '-Wshadow', '-frtti', '-fexceptions' ],
    },
    'configurations': {
      'Debug': {
        'cflags_cc': [ '-g', '-O0', '-fno-omit-frame-pointer','-fwrapv', '-fstack-protector-all', '-fno-common' ],
        'defines': [ 'DEBUG' ],
        'xcode_settings': {
          'CLANG_CXX_LIBRARY': 'libc++',
          'CLANG_CXX_LANGUAGE_STANDARD':'c++11',
          'MACOSX_DEPLOYMENT_TARGET': '10.7',
          'GCC_OPTIMIZATION_LEVEL': '0',
          'GCC_GENERATE_DEBUGGING_SYMBOLS': 'YES',
          'DEAD_CODE_STRIPPING': 'NO',
          'GCC_INLINES_ARE_PRIVATE_EXTERN': 'NO',
          'OTHER_CPLUSPLUSFLAGS': [ '-fno-omit-frame-pointer','-fwrapv', '-fstack-protector-all', '-fno-common']
        }
      },
      'Release': {
        'cflags_cc': [ '-g', '-O3' ],
        'defines': [ 'NDEBUG' ],
        'xcode_settings': {
          'CLANG_CXX_LIBRARY': 'libc++',
          'CLANG_CXX_LANGUAGE_STANDARD':'c++11',
          'MACOSX_DEPLOYMENT_TARGET': '10.7',
          'GCC_OPTIMIZATION_LEVEL': '3',
          'GCC_GENERATE_DEBUGGING_SYMBOLS': 'YES',
          'DEAD_CODE_STRIPPING': 'YES',
          'GCC_INLINES_ARE_PRIVATE_EXTERN': 'NO'
        }
      },
    },
  },
  'targets': [
    { 'target_name': 'uv_zip',
      'product_name': 'uv_zip',
      'type': 'static_library',
      'include_dirs': [
        'include',
      ],
      'sources': [
        'src/uv_zip.c',
        'include/uv_zip.h',
      ],
      'variables': {
        'cflags': [
          '<@(uv_cflags)',
          '<@(zip_cflags)',
        ],
        'ldflags': [
          '<@(uv_ldflags)',
          '<@(zip_ldflags)',
        ],
        'libraries': [
          '<@(uv_static_libs)',
          '<@(zip_static_libs)',
        ],
      },
      'xcode_settings': {
        'OTHER_CFLAGS': [ '<@(cflags)' ],
      },
      'cflags': [ '<@(cflags)' ],
      'link_settings': {
        'libraries': [ '<@(libraries)' ],
        'xcode_settings': {
          'OTHER_LDFLAGS': [ '<@(ldflags)' ],
        },
        'ldflags': [ '<@(ldflags)' ],
      },
      'direct_dependent_settings': {
        'include_dirs': [ 'include' ],
        'xcode_settings': {
          'OTHER_CFLAGS': [ '<@(cflags)' ],
          'OTHER_CPLUSPLUSFLAGS': [ '<@(cflags)' ],
        },
        'cflags': [ '<@(cflags)' ],
      },
    },

    { 'target_name': 'test',
      'product_name': 'test',
      'type': 'executable',
      'sources': [
        'test/assert.hpp',
        'test/missing_file.cpp',
        'test/missing_file_stat.cpp',
        'test/open_failure.cpp',
        'test/open_from_fd.cpp',
        'test/read_file.cpp',
        'test/stat_file.cpp',
        'test/reuse_handle.cpp',
        'test/test.cpp',
      ],
      'dependencies': [ 'uv_zip' ],
    },
  ],
}
