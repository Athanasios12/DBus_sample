
##${CMAKE_CURRENT_SOURCE_DIR}/) # can't use relative paths
file(GLOB INCLUDES *.h)
set(HEADERS
   ${HEADERS}
   ${INCLUDES}
   PARENT_SCOPE
)

