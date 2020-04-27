project(
      'zman'
    , 'cpp'
    , default_options : ['cpp_std=c++2a']
)

test_sources = [
       'src/zman_main.t.cpp' 
     , 'src/zman_temporal_value.t.cpp'
     , 'src/zman_time_line.t.cpp'
     , 'src/zman_entity.t.cpp'
     , 'src/zman_attribute.t.cpp'
     , 'src/zman_attribute_map.t.cpp'
     , 'src/zman_temporal_convert.t.cpp'
     , 'src/zman_test_util.t.cpp'
]

exec = executable(
      'zman_test'
    , test_sources
)

test('test' , exec)
