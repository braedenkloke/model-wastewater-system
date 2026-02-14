set(EXPERIMENTS
wastewater_system_no_attacks
)

foreach(experiment IN LISTS EXPERIMENTS)
    add_executable(${experiment} ${experiment}.cpp)
    target_include_directories(${experiment} PRIVATE "." "include" $ENV{CADMIUM})
    target_compile_options(${experiment} PUBLIC -std=gnu++2b)
endforeach()
