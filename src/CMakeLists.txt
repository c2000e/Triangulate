add_library(TriangulateLib STATIC face.cc
                                  half_edge.cc
                                  half_edge_iterator.cc
                                  mesh.cc
                                  triangulate.cc
                                  vector.cc
                                  vertex.cc)

target_compile_features(TriangulateLib PUBLIC cxx_std_11)
target_include_directories(TriangulateLib PUBLIC ../include)
