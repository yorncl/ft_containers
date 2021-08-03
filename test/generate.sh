#/bin/bash


echo $1
# Python version
PYTHON=python3

# Check if python is installed
$PYTHON -V > /dev/null 2> /dev/null
if [[ $? == 127 ]]
then
  echo "python3 not found"
  exit 1 
fi

# Scap all of the documentation necessary
function scrap
{
  echo "Scrapping the documentation from the web"
  python3 ./scrapper.py
}

# generate the headers from the documentation
function headers
{
  echo "Generating headers from the documentation"
  python3 ./generate_headers.py
}

# generate tests from the documentation
function tests
{
  echo "Generating test from the documentation"
  python3 ./generate_tests.py
}

function usage
{
  echo "Usage : ./generate.sh [all|scrap|headers|tests]"
}

if [[ $# != 1 ]]
then
  usage
  exit 1 
fi

if [[ $1 == "all" ]]
then
  scrap
  headers
  tests
else
  if [[ $1 == "scrap" || $1 == "headers" || $1 == "tests" ]]
  then
    $1
  else
    usage
    exit 1 
  fi
fi

