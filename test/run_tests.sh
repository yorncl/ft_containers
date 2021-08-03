#!/usr/bin/bash

CC="clang++"
CLFLAGS="-Wall -Wextra -Werror"
CONTAINERS_DIR="../"
TEST_SRC="main.cpp"
NAME=ft_containers_tester

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

function compile_tests
{
    echo "Compiling tests"
    $CC $CLFAGS $TEST_SRC -o $NAME
}

function launch_tests
{
    echo "Launching tests"
    printf "$RED BONJOUR A TOUS $NC C'est le moment de faire qqchose de ta vie boloss\n"
    ./$NAME
}

function compare_diff
{
    echo "Comparing outputs"
}

hello
compile_tests
launch_tests
compare_diff
