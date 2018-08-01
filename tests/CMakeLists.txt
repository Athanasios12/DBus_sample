
##${CMAKE_CURRENT_SOURCE_DIR}/) # can't use relative paths
file(GLOB TEST_SRCFILES *.cpp)
set(TESTS_SRC
   ${TESTS_SRC}
   ${TEST_SRCFILES}
   PARENT_SCOPE
)

