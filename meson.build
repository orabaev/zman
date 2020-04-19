project(
      'zman'
    , 'cpp'
    , default_options : ['cpp_std=c++2a']
)

test_sources = [
       'src/zman_main.t.cpp' 
     , 'src/zman_temporal_value.t.cpp'
     , 'src/zman_time_line.t.cpp'
     , 'src/zman_temporal_attributes.t.cpp'
]

exec = executable(
      'zman_test'
    , test_sources
)

test('test' , exec)
