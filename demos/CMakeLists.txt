add_executable(hello_world hello_world.cpp)

target_include_directories(hello_world PUBLIC ../include)
target_link_libraries(hello_world PRIVATE lefaye)
target_compile_features(hello_world PRIVATE cxx_std_17)

set_target_properties(hello_world
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lefaye/demos"
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR}/lefaye/demos)