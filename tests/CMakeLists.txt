add_executable(main.cpp main.cpp)
target_include_directories(main.cpp PRIVATE "." "include" $ENV{CADMIUM})
target_compile_options(main.cpp PUBLIC -std=gnu++2b)
