#!/usr/bin/bash
#!/bin/bash


CC="clang++"
CLFLAGS=" -Wall -Wextra -Werror -g3 -fsanitize=address"
CLFLAGSSTD=" -Wall -Wextra -Werror -g3 -fsanitize=address"
CONTAINERS_DIR="../../../../"
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )" 
cd $SCRIPT_DIR # Doing this to avoid having to append the path to each source file

function run_single
{
  # std
  $CC $CLFLAGSSTD $1 -D NAMESPACE=std -D HEADER_FILE="<type_traits>" -o std.out
  $CC $CLFLAGS -I $CONTAINERS_DIR $1 -D NAMESPACE=ft -D HEADER_FILE='"utils.hpp"' -o ft.out
  diff -y <(./ft.out) <(./std.out)
  rm ft.out std.out
}

run_single ./is_integral.cpp
run_single ./is_same.cpp
run_single ./iterators_traits.cpp
run_single ./pair.cpp

