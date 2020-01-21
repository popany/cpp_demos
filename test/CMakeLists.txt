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

# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(googletest source_dir binary_dir)

if(UNIX)
	# Create a libgtest target to be used as a dependency by test programs
	add_library(gtest IMPORTED STATIC GLOBAL)
	add_dependencies(gtest googletest)

	# Set libgtest properties
	set_target_properties(gtest PROPERTIES
		"IMPORTED_LOCATION" "${binary_dir}/lib/libgtest.a"
		"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
	)

	# Create a libgmock target to be used as a dependency by test programs
	add_library(gmock IMPORTED STATIC GLOBAL)
	add_dependencies(gmock googletest)

	# Set libgmock properties
	set_target_properties(gmock PROPERTIES
		"IMPORTED_LOCATION" "${binary_dir}/lib/libgmock.a"
		"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
	)
endif()

if(WIN32)
	# Create a libgtest target to be used as a dependency by test programs
	add_library(gtest IMPORTED STATIC GLOBAL)
	add_dependencies(gtest googletest)

	# Set libgtest properties
	set_target_properties(gtest PROPERTIES
		"IMPORTED_LOCATION" "${binary_dir}/lib/gtest.lib"
		"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
	)

	# Create a libgmock target to be used as a dependency by test programs
	add_library(gmock IMPORTED STATIC GLOBAL)
	add_dependencies(gmock googletest)

	# Set libgmock properties
	set_target_properties(gmock PROPERTIES
		"IMPORTED_LOCATION" "${binary_dir}/lib/gmock.lib"
		"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
	)
endif()

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/googletest/include"
					"${source_dir}/googlemock/include"
)

add_subdirectory(testfoo)
add_subdirectory(testbar)
