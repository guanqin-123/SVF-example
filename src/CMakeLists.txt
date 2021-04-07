llvm_map_components_to_libnames(llvm_libs bitwriter core ipo irreader instcombine instrumentation target linker analysis scalaropts support )
file (GLOB SOURCES
   *.cpp
)
add_executable(svf-ex ${SOURCES} SSE.cpp SSE.h test.h)

target_link_libraries(svf-ex ${llvm_libs} Svf Cudd)
# briefly revised to add z3 lib, if failed please compile with -v para and request on issues
target_link_libraries(svf-ex z3 gtest gmock)
set_target_properties( svf-ex PROPERTIES
                       RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )
