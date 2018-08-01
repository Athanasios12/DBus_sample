
##${CMAKE_CURRENT_SOURCE_DIR}/) # can't use relative paths
file(GLOB SRCFILES *.cpp)
set(SRC
   ${SRC}
   ${SRCFILES}
   PARENT_SCOPE
)

