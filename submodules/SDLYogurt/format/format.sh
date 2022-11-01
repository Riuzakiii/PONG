#!/bin/bash
####FORMAT SCRIPT ####

LIB_DIR="../src"

find $LIB_DIR -name *.cpp -exec clang-format -i --verbose {} \;
find $LIB_DIR -name *.h -exec clang-format -i --verbose {} \;
