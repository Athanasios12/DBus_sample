#!/bin/sh
TARGET_DIR="."
COVERAGE_OUTPUT_DIR=$TARGET_DIR/coverage
if [ "$1" != "" ]; then
   TARGET_DIR=$1 
fi
if [ "$2" != "" ]; then
   COVERAGE_OUTPUT_DIR=$2
fi
#generate unfiltered coverage report
lcov -c -d $TARGET_DIR -o $TARGET_DIR/coverage.info
lcov -r $TARGET_DIR/coverage.info '/usr/include*' '*googletest*' '*Tests.cpp' '*.h' -o $TARGET_DIR/coverage_output.info
#generate html report
rm $TARGET_DIR/coverage.info
genhtml coverage_output.info -o $TARGET_DIR/$COVERAGE_OUTPUT_DIR

