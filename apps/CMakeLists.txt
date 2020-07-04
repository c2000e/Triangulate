FetchContent_Declare(
    SDL2
    GIT_REPOSITORY "https://github.com/SDL-mirror/SDL.git"
    GIT_TAG release-2.0.10
)
FetchContent_MakeAvailable(SDL2)

set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)

add_executable(Triangulate main.cc)
target_compile_features(Triangulate PRIVATE cxx_std_11)
target_link_libraries(Triangulate PRIVATE SDL2main SDL2-static)
