cmake_minimum_required(VERSION "3.20")

project("pitdie")

#------------Basic-----------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_FIND_USE_PACKAGE_REGISTRY FALSE)
set(CMAKE_FIND_USE_SYSTEM_PACKAGE_REGISTRY FALSE)
set(CMAKE_SUPPRESS_REGENERATION ON CACHE BOOL "" FORCE)
#----------------------------------

#------------MSVC------------------
if(MSVC)
    add_link_options(/INCREMENTAL)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus /Zc:preprocessor /utf-8")
    #Some C deps use `/source-charset:utf-8` and some use `/utf-8`, so we're not going to bother with it.
    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /utf-8")
    cmake_policy(SET CMP0091 NEW)
    add_compile_definitions(
        WIN32_LEAN_AND_MEAN
        NOMINMAX
    )
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    foreach(flag_var
        CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE)
        if(${flag_var} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endif()
    endforeach()
endif()
#----------------------------------

#------------Clangd----------------
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
#----------------------------------

#------------Files-----------------
file(GLOB_RECURSE PITDIE_SOURCES CMAKE_CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")
#----------------------------------

#------------CherryGrove-----------
add_executable(${PROJECT_NAME} ${PITDIE_SOURCES})
#----------------------------------

#------------Build:Marco-----------
target_compile_definitions(${PROJECT_NAME} PRIVATE $<IF:$<CONFIG:Debug>,DEBUG,NDEBUG>)
#----------------------------------

#------------Inclusions------------
target_include_directories(${PROJECT_NAME} PRIVATE
)
#----------------------------------

#------------Link------------------
target_link_libraries(${PROJECT_NAME} PRIVATE
)
#----------------------------------

#------------Link:System-----------
if(WIN32)
    target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:CONSOLE")
endif()
#----------------------------------