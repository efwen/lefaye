add_library(lefaye core.cpp gfx.cpp platform/platform_win32.cpp)

target_include_directories(lefaye PUBLIC fmt::fmt ../include)
target_link_libraries(lefaye PRIVATE Vulkan::Vulkan fmt::fmt)
target_compile_features(lefaye PUBLIC cxx_std_17)

set_target_properties(lefaye
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lefaye/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lefaye/lib"
)
