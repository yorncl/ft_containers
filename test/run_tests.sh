#!/usr/bin/bash

CC="clang++"
CLFLAGS="-g -Wall -Wextra -Werror -std=c++98"
CONTAINERS_DIR="../"

# https://stackoverflow.com/questions/59895/how-can-i-get-the-source-directory-of-a-bash-script-from-within-the-script-itsel
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )" 
cd $SCRIPT_DIR # Doing this to avoid having to append the path to each source file


RED="\033[0;31m"
GREEN="\033[0;32m"
NC="\033[0m"


if [[ $? != 0 ]]
then
    echo "Aborting script"
    exit 1
fi

function hello
{
    echo '  ______    __                                           __                __                                         '
    echo ' /      \  /  |                                         /  |              /  |                                        '
    echo '/$$$$$$  |_$$ |_          _______   ______   _______   _$$ |_     ______  $$/  _______    ______    ______    _______ '
    echo '$$ |_ $$// $$   |        /       | /      \ /       \ / $$   |   /      \ /  |/       \  /      \  /      \  /       |'
    echo '$$   |   $$$$$$/        /$$$$$$$/ /$$$$$$  |$$$$$$$  |$$$$$$/    $$$$$$  |$$ |$$$$$$$  |/$$$$$$  |/$$$$$$  |/$$$$$$$/ '
    echo '$$$$/      $$ | __      $$ |      $$ |  $$ |$$ |  $$ |  $$ | __  /    $$ |$$ |$$ |  $$ |$$    $$ |$$ |  $$/ $$      \ '
    echo '$$ |       $$ |/  |     $$ \_____ $$ \__$$ |$$ |  $$ |  $$ |/  |/$$$$$$$ |$$ |$$ |  $$ |$$$$$$$$/ $$ |       $$$$$$  |'
    echo '$$ |       $$  $$/______$$       |$$    $$/ $$ |  $$ |  $$  $$/ $$    $$ |$$ |$$ |  $$ |$$       |$$ |      /     $$/ '
    echo '$$/         $$$$//      |$$$$$$$/  $$$$$$/  $$/   $$/    $$$$/   $$$$$$$/ $$/ $$/   $$/  $$$$$$$/ $$/       $$$$$$$/  '
    echo '                 $$$$$$/                                                                                              '
    echo '                                                                                                           by mclaudel'
}


function compilation_fail
{
  printf "$RED%-30s compilation failed$NC\n" $1
}

function success
{
  printf "$GREEN%-30s Success!$NC\n" $1
}

function launch_tests
{


    echo "Launching tests"
    for dir in tests/*
    do
      echo $dir
      for file in $dir/src/*
      do
        # Creating dirs to store output
        mkdir -p $dir/compilation
        mkdir -p $dir/out
        mkdir -p $dir/ft_out
        mkdir -p $dir/diff
        out=normal.out
        ft_out=ft.out
        testname=$(basename $file | cut -f 1 -d '.')
        $CC $CLFLAGS $file -o $out -D NAMESPACE=std
        $CC $CLFLAGS -I $CONTAINERS_DIR $file -o $ft_out -D NAMESPACE=ft 2> $dir/compilation/$testname
        if [[ $? != 0 ]]
        then
          compilation_fail $testname
        else
          echo $file 
          echo $testname $out $ft_out
          success $testname
        fi
       rm $out $ft_out 
      done
    done
    #Deleting empty files
 }

function single_test
{
  file=tests/$1/src/$2.cpp
  out=normal.out
  ft_out=ft.out
  $CC $CLFLAGS $file -o $out -D NAMESPACE=std -D HEADER_FILE="<$1>"
  sleep 2
  $CC $CLFLAGS -I $CONTAINERS_DIR $file -o $ft_out -D NAMESPACE=ft -D HEADER_FILE="\"$1.hpp\""
  if [[ $? != 0 ]]
  then
    exit 1
  else
    success
  fi
}


hello

if [[ $# != 0 ]]
then
  if [[ $1 == "single" && $# == 3 && -f "tests/$2/src/$3.cpp" ]]
  then
    single_test $2 $3
  fi
else
  launch_tests
fi
