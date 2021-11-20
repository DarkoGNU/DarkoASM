# CMakeList.txt : CMake project for DarkoASM, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (DarkoASM "DarkoASM.cpp"  "Parser.cpp" "Parser.h" "Code.cpp" "Code.h" "SymbolTable.cpp" "SymbolTable.h" "SpecialMap.cpp" "SpecialMap.h")

# TODO: Add tests and install targets if needed.
set_target_properties(
    DarkoASM PROPERTIES
    CXX_STANDARD 20)