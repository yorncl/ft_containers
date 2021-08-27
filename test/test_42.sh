
CC="clang++"
CLFLAGS=" -Wall -Wextra -Werror -std=c++98 -ferror-limit=5"
CONTAINERS_DIR="../"

# https://stackoverflow.com/questions/59895/how-can-i-get-the-source-directory-of-a-bash-script-from-within-the-script-itsel
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )" 
cd $SCRIPT_DIR # Doing this to avoid having to append the path to each source file

$CC $CLFLAGS -I ../ ./test42.cpp -D ENABLE_STD=1 -o std.out
$CC $CLFLAGS -I ../ ./test42.cpp -D ENABLE_STD=0 -o ft.out

SEED=$1
if [[ $SEED == '' ]]
then
  SEED="qwerty"
fi

time ./std.out $SEED > std.output
time ./ft.out $SEED > ft.output

diff -y std.output ft.output

rm ft.out std.out ft.output std.output
