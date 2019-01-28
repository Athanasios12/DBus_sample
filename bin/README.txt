I. Static Analysis - clang-tidy(install clang compiler or build from source)

1. Run clang-tidy

    clang-tidy -checks=-*,clang-analyzer-*,cppcoreguidelines- SRC_DIR/*.cpp -- -std=c++17 -I../include $(pkg-config --cflags dbus-1)

2. Output to file with color script -q -c "clangAnalysisScript" file.txt



II. Compile unit tests with LCOV - GNU coverage analysis :

1. Compile  : g++ -o main.out --coverage main.cpp

2. Define variables for creating data files for function coverage analysis

export GCOV_PREFIX="/home/subho/work/lab/zzz/data"

export GCOV_PREFIX_STRIP=6      - defines number of slashes in GCOV_PREFIX path

3. Run main.out - produces main.gcda in GCOV_PREFIX dir

4. Copy main.gcno (compile output when  --coverage flag added) to GCOV_PREFIX dir

5.Run lcov in GCOV_PREFIX :

lcov -t "result" -o covTest.info -c -d .

-t     sets a test name

-o    to specify the output file

-c    to capture the coverage data

-d    to specify the directory where the data files needs to be searched

6. Generate html output :

genhtml -o res ex_test.info - res is dir where the html out will be put

7. cd res, open index.html in web-browser



III. Run unit tests
