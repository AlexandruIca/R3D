find_package(spdlog REQUIRED)

set(RENDERER_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/renderer.cpp)

add_library(renderer STATIC ${RENDERER_SOURCE_FILES})
add_library(renderer_shared SHARED ${RENDERER_SOURCE_FILES})

add_library(renderer::renderer ALIAS renderer)
add_library(renderer::renderer_shared ALIAS renderer_shared)

target_include_directories(renderer PUBLIC ${RENDERER_INCLUDE_DIR})
target_include_directories(renderer_shared PUBLIC ${RENDERER_INCLUDE_DIR})

target_link_libraries(renderer PRIVATE project::options project::warnings spdlog::spdlog)
target_link_libraries(renderer_shared PRIVATE project::options project::warnings spdlog::spdlog)
