# Tests
enable_testing()

add_executable(SparseSetTests
   SparseSetTests.cxx
)

target_compile_features(SparseSetTests PUBLIC cxx_std_26)
target_compile_options(SparseSetTests PRIVATE ${CXX_ALL_FLAGS})
target_link_libraries(SparseSetTests PUBLIC TinyEngine_SparseSet ${CXX_SANITIZERS_FLAGS})

add_test(
   NAME SparseSetTests
   COMMAND SparseSetTests
)
