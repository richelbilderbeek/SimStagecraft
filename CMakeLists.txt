cmake_minimum_required(VERSION 3.16)

project(SimStagecraft VERSION 1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

file(GLOB SIMSTAGECRAFT_SOURCES CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/code/Unit*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/code/Unit*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/code/ui/*.h
)

# The images and texts, converted from the original VCL .dfm files
qt_add_resources(SIMSTAGECRAFT_RESOURCES code/resources/resources.qrc)

# All game code, shared by the game and its tests
add_library(simstagecraft_lib STATIC ${SIMSTAGECRAFT_SOURCES} ${SIMSTAGECRAFT_RESOURCES})
target_include_directories(simstagecraft_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/code)
target_link_libraries(simstagecraft_lib PUBLIC Qt6::Widgets)
# M_PI on MSVC
target_compile_definitions(simstagecraft_lib PUBLIC _USE_MATH_DEFINES)

qt_add_executable(SimStagecraft WIN32 MACOSX_BUNDLE
  code/ProjectSimStagecraft.cpp
)
target_link_libraries(SimStagecraft PRIVATE simstagecraft_lib)

include(CTest)
if(BUILD_TESTING)
  add_executable(test_simstagecraft code/tests/TestSimStagecraft.cpp)
  target_link_libraries(test_simstagecraft PRIVATE simstagecraft_lib)
  add_test(NAME test_simstagecraft COMMAND test_simstagecraft)
  set_tests_properties(test_simstagecraft PROPERTIES
    ENVIRONMENT "QT_QPA_PLATFORM=offscreen")
endif()
