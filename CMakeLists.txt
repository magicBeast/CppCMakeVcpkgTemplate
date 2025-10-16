cmake_minimum_required(VERSION 3.21)
project(cpp_template)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)

# --- Find Dependencies from vcpkg ---
find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

set(
    CPP_TEMPLATE_SOURCES
    src/main.cpp
)

set(
    CPP_TEMPLATE_TEST_SOURCES
    src/test.cpp
)

# --- Main Target ---
add_executable(main ${CPP_TEMPLATE_SOURCES})
target_link_libraries(main PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
    imgui::imgui
)
set_property(TARGET main PROPERTY CXX_STANDARD 23)

# --- macOS App Bundle Configuration ---
if(APPLE)
  set_target_properties(main PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.yourname.pong"
        MACOSX_BUNDLE_BUNDLE_NAME "Pong Game"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0"
        MACOSX_BUNDLE_BUNDLE_VERSION "1.0.0"
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/Info.plist.in"
  )
  # Copy assets folder into the app bundle's Resources directory
  add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_BUNDLE_CONTENT_DIR:main>/Resources/assets
        COMMENT "Copying assets into app bundle..."
  )
endif()

# --- Tests Target ---
# add_executable(tests ${CPP_TEMPLATE_TEST_SOURCES})
# target_link_libraries(tests PRIVATE
#     SDL3::SDL3
#     SDL3_image::SDL3_image
#     SDL3_ttf::SDL3_ttf
#     imgui::imgui
# )
# set_property(TARGET tests PROPERTY CXX_STANDARD 23)
#
# enable_testing()
# add_test(tests tests)

# --- Formatting Targets ---
add_custom_target(
    check-format
    COMMAND clang-format --dry-run ${CPP_TEMPLATE_SOURCES} ${CPP_TEMPLATE_TEST_SOURCES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "checking format in src..."
)

add_custom_target(
    format
    COMMAND clang-format -i ${CPP_TEMPLATE_SOURCES} ${CPP_TEMPLATE_TEST_SOURCES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "checking format in src..."
)
