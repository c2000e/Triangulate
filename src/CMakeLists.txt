add_library(TriangulateLib STATIC face.cc
                                  half_edge.cc
                                  mesh.cc
                                  vector.cc
                                  vertex.cc)

target_compile_features(TriangulateLib PUBLIC cxx_std_11)
target_include_directories(TriangulateLib PUBLIC ../include)
