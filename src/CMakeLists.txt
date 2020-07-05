add_library(TriangulateLib STATIC vector.cc)
target_compile_features(TriangulateLib PUBLIC cxx_std_11)
target_include_directories(TriangulateLib PUBLIC ../include)
