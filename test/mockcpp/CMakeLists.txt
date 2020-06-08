find_package(Threads REQUIRED)

include(ExternalProject)

ExternalProject_Add(
    mockcpp_external
    # URL https://bitbucket.org/godsme/mockcpp/get/06ad37ddc45c.zip
    URL ftp://192.168.1.8/mockcpp/06ad37ddc45c.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/mockcpp

    CMAKE_ARGS "-DMOCKCPP_XUNIT=gtest" "-DMOCKCPP_XUNIT_HOME=${GTEST_HOME}" "-DPython_ADDITIONAL_VERSIONS=2.7"

    # build as debug for Unix Makefiles
    CMAKE_BUILD_TYPE "Debug"

    # build as debug for visual studio 
    BUILD_COMMAND "${CMAKE_COMMAND}" "--build" "${CMAKE_CURRENT_BINARY_DIR}/mockcpp/src/mockcpp_external-build" "--config" "Debug"

    # Disable install step
    INSTALL_COMMAND ""

    # Wrap download, configure and build steps in a script to log output
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
)

ExternalProject_Get_Property(mockcpp_external source_dir binary_dir)

if(MSVC)
    Set(OUTPUT_DIR "${binary_dir}/src/Debug")
else()
    Set(OUTPUT_DIR "${binary_dir}/src")
endif()

add_library(mockcpp IMPORTED STATIC GLOBAL)
add_dependencies(mockcpp mockcpp_external)
set(MOCKCPP_INCLUDE_DIRECTORY "${source_dir}/include")
file(MAKE_DIRECTORY ${MOCKCPP_INCLUDE_DIRECTORY})
target_include_directories(mockcpp
	INTERFACE
		${MOCKCPP_INCLUDE_DIRECTORY}
)
set(MOCKCPP_LIB_FILE_NAME "${CMAKE_STATIC_LIBRARY_PREFIX}mockcpp${CMAKE_STATIC_LIBRARY_SUFFIX}")
set_target_properties(mockcpp PROPERTIES
	"IMPORTED_LOCATION" "${OUTPUT_DIR}/${MOCKCPP_LIB_FILE_NAME}"
	"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)
