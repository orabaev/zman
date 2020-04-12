project(
      'zman'
    , 'cpp'
    , default_options : ['cpp_std=c++2a']
)

#lib = library(
#    'zmanlib'
#    , 'todo.cpp'
#)


test_sources = [
    'src/zman_time_line.t.cpp'
]

exec = executable(
      'zman_test'
    , test_sources
#    , link_with : lib
)

test('test' , exec)
