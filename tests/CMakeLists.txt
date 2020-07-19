FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.10.0
)
FetchContent_MakeAvailable(googletest)

add_executable(TestTriangulateLib test_half_edge.cc 
                                  test_mesh.cc
                                  test_vector.cc
                                  test_vertex.cc)

target_compile_features(TestTriangulateLib PRIVATE cxx_std_11)
target_link_libraries(TestTriangulateLib PRIVATE TriangulateLib gtest
    gtest_main)

add_test(NAME TestTriangulateLib COMMAND TestTriangulateLib)
