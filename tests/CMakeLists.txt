include(GoogleTest)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.10.0
)

FetchContent_GetProperties(googletest)

if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

mark_as_advanced(
  BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
  gmock_build_tests gtest_build_samples gtest_build_tests
  gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

function(vkp_add_test TESTDIR TESTNAME)
  add_executable(${TESTNAME} "${TESTDIR}/${TESTNAME}.cpp" ${ARGN})
  target_link_libraries(${TESTNAME} lefaye gtest gmock gtest_main)
  target_include_directories(${TESTNAME} PUBLIC ${PROJECT_SOURCE_DIR}/include gtest gmock)
  target_compile_features(${TESTNAME} PRIVATE cxx_std_17)
  gtest_discover_tests(${TESTNAME}
    WORKING_DIRECTORY ${PROJECT_DIR}
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
  )

  set_target_properties(${TESTNAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lefaye/tests"
  )
endfunction()

vkp_add_test(os file-test)
