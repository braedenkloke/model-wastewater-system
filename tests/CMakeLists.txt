set(TESTS
plc_test
tamper_attacker_test
)

foreach(test IN LISTS TESTS)
    add_executable(${test} ${test}.cpp)
    target_include_directories(${test} PRIVATE "." "include" $ENV{CADMIUM})
    target_compile_options(${test} PUBLIC -std=gnu++2b)
endforeach()
