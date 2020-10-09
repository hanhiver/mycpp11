add_library(timer SHARED timer.cpp)
target_include_directories(timer 
    PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(timer
    PUBLIC Threads::Threads)