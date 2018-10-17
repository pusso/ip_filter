cmake_minimum_required(VERSION 3.2)

project( ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER} )

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file( version.h.in ${PROJECT_SOURCE_DIR}/version.h )

add_library( ip_filter_lib lib.cpp )
add_executable( ip_filter main.cpp )
add_executable( test_main_cli test_main.cpp )

set_target_properties(
    ip_filter
    ip_filter_lib
    test_main_cli
  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

set_target_properties(
    test_main_cli 
  PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries( ip_filter ip_filter_lib)

target_link_libraries(test_main_cli
  ${Boost_LIBRARIES}
  ip_filter_lib
)

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT andreipuskin@gmail.com)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include (CPack)

enable_testing()

add_test(ip_filter_test test_main_cli)