find_package(Threads REQUIRED)

# Enable ExternalProject CMake module
include(ExternalProject)

# Download and install GoogleTest
ExternalProject_Add(
    googletest
    URL https://github.com/google/googletest/archive/release-1.10.0.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/googletest

	# cmake arguments
    CMAKE_ARGS -Dgtest_force_shared_crt=ON

    # Disable install step
    INSTALL_COMMAND ""

    # Wrap download, configure and build steps in a script to log output
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
)

ExternalProject_Get_Property(googletest source_dir binary_dir)

add_library(gtest IMPORTED STATIC GLOBAL)
add_dependencies(gtest googletest)
set(GTEST_INCLUDE_DIRECTORY "${source_dir}/googletest/include")
file(MAKE_DIRECTORY ${GTEST_INCLUDE_DIRECTORY})
target_include_directories(gtest
	INTERFACE
		${GTEST_INCLUDE_DIRECTORY}
)
set(GTEST_LIB_FILE_PATH "${binary_dir}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}")
set_target_properties(gtest PROPERTIES
	"IMPORTED_LOCATION" ${GTEST_LIB_FILE_PATH}
	"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

add_library(gmock IMPORTED STATIC GLOBAL)
add_dependencies(gmock googletest)
set(GMOCK_INCLUDE_DIRECTORY "${source_dir}/googlemock/include")
file(MAKE_DIRECTORY ${GMOCK_INCLUDE_DIRECTORY})
target_include_directories(gmock
	INTERFACE
		${GMOCK_INCLUDE_DIRECTORY}
)
set(GMOCK_LIB_FILE_PATH "${binary_dir}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gmock${CMAKE_STATIC_LIBRARY_SUFFIX}")
set_target_properties(gmock PROPERTIES
	"IMPORTED_LOCATION" ${GMOCK_LIB_FILE_PATH}
	"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)
