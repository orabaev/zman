project(
      'zman'
    , 'cpp'
    , default_options : ['cpp_std=c++2a']
)

test_sources = [
      'src/zman_time_line.t.cpp'
    , 'src/zman_id.t.cpp'
    , 'src/zman_temporal_id.t.cpp'
    , 'src/zman_temporal_entity.t.cpp'
]

exec = executable(
      'zman_test'
    , test_sources
)

test('test' , exec)
