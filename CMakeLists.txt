cmake_minimum_required(VERSION 3.10)
project(ModernOpenGL)

set(CMAKE_CXX_STANDARD 14)

#SET(VCPKG_ROOT "/Users/always/dev/vcpkg")
if (NOT EXISTS ${VCPKG_ROOT})
    MESSAGE(FATAL_ERROR "Cannot proceed without VCPKG_ROOT being defined. Please correct your settings.
You can get vcpkg from https://github.com/Microsoft/vcpkg")
endif ()
MESSAGE("VCPKG_ROOT          = " ${VCPKG_ROOT})
MESSAGE("Installing dependencies using VCPKG")
if (WIN32)
    execute_process(
            COMMAND cmd /c "${VCPKG_ROOT}/vcpkg.exe install opengl:x64-windows glew:x64-windows glm:x64-windows freetype:x64-windows sdl2-image[libjpeg-turbo]:x64-windows"
            OUTPUT_VARIABLE outVar
    )
elseif (UNIX)
    # If it gives error such that not finding these add this line at next to the
    # vcpkg/ports/sdl/portfile.cmake next to SYSTEM_LIBRARIES dbus-1 glib-2.0 gobject-2.0 gio-2.0 ibus-1.0 z
    execute_process(
            COMMAND bash -c "${VCPKG_ROOT}/vcpkg install opengl glew glm freetype sdl2-image[libjpeg-turbo]"
            OUTPUT_VARIABLE outVar
    )
endif ()
MESSAGE(${outVar})

find_package(GLEW REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)
find_package(freetype CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

set(PROJECT_NAME_LIBRARY ${PROJECT_NAME}Lib)

set(SOURCE_FILES sandbox/main.cpp
        src/components/Texture.cpp src/components/Texture.h
        src/sdl/SDLWindow.cpp src/sdl/SDLWindow.h
        src/mesh/TextureVertex.h
        src/components/Shader.cpp src/components/Shader.h
        src/components/Camera.cpp src/components/Camera.h
        src/sdl/SDL.cpp src/sdl/SDL.h src/sdl/SDLContext.cpp src/sdl/SDLContext.h
        src/ResourceManager.cpp src/ResourceManager.h src/util/Rect.h src/util/Glyph.h src/util/Font.h
        src/util/RenderQueue.h
        src/batch/TextureBatch.cpp src/batch/TextureBatch.h
        src/components/Window.cpp src/components/Window.h src/render/Renderer.cpp src/render/Renderer.h
        src/util/Types.h sandbox/Game.cpp sandbox/Game.h src/mesh/TextureMesh.cpp src/mesh/TextureMesh.h
        src/batch/BatchInterface.h src/render/RenderData.h sandbox/GameObject.h src/mesh/ConvexMesh.h
        src/mesh/ConvexVertex.h src/batch/ConvexBatch.cpp src/batch/ConvexBatch.h
        vendor/enum.h
        src/mesh/CircleMesh.h src/mesh/RectangleMesh.h src/mesh/TextMesh.cpp src/mesh/TextMesh.h sandbox/Resources.h)

add_library(${PROJECT_NAME_LIBRARY} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME_LIBRARY} GLEW::GLEW glm
        SDL2::SDL2main SDL2::SDL2-static SDL2::SDL2_image freetype z)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME_LIBRARY})

set(PROJECT_NAME_LIBRARY ${PROJECT_NAME_LIBRARY} CACHE STRING "" FORCE)
mark_as_advanced(PROJECT_NAME_LIBRARY)
