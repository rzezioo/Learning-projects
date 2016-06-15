#!/bin/bash
mydir="$PWD"
target_dir="target"
output_dir="tmp_results"
problem_set_dir=""
problem_id=""
test_id=""

function cleanup_dir {
  if [ -d "$target_dir" ]
  then
    rm -Rf $target_dir
  fi
  if [ -d "$output_dir" ]
  then
    rm -Rf $output_dir
  fi
}

function init_dir {
  cleanup_dir
  mkdir $target_dir
  mkdir $output_dir
}

function compile {
  if [ -f "$problem_id.cpp" ]
  then
    echo "Compiling"
    g++ -O2 -static $problem_id.cpp -lm -o $target_dir/$problem_id
    if [ -f "$target_dir/$problem_id" ]
    then
      echo "Compilation successful"
      return 0
    else
      return 1
    fi
  else
    echo "File not found: $problem_id.cpp"
    return 1
  fi
}

function run_test {
  local ex_time=`TIMEFORMAT="%R";time ($target_dir/$problem_id < test/$1.in > $output_dir/$1.out 2> $output_dir/$1.err) 2>&1 1>/dev/null`
  local err=`cat $output_dir/$1.err`
  if [ "$err" ]
  then
    echo "ERR $ex_time $1"
    return 0
  fi
  local comp_tool="diff"
  if [ -f compare.sh ]
  then
    comp_tool="./compare.sh"
  fi
  local comp_result=`$comp_tool test/$1.out $output_dir/$1.out`
  if [ "$comp_result" ]
  then
    echo "WA  $ex_time $1"
  else
    echo "OK  $ex_time $1"
  fi
}

function run_single_test {
  $target_dir/$problem_id < test/$1.in
}

function run_tests {
  for f in test/*.in
  do
    local file_name=$(basename $f)
    run_test ${file_name%.*}
  done
}

function run_dir {
  compile
  if [ "$?" -eq 0 ]
  then
    if [ $test_id ]
    then
      run_single_test $test_id
    else
      run_tests
    fi
  else
    echo "Compilation failed"
    return 1
  fi
}

if [ "$#" -lt 2 ]
then
  echo "Usage: run_tests.sh <problem_set_dir> <problem_id>"
  exit 1
fi

if [ "$#" -ge 3 ]
then
  test_id=$3
  echo "Running single test: $test_id"
fi

if [ ! -d "$1" ]
then
  echo "Problem set directory not found: $1"
  exit 1
fi

problem_set_dir=$1

cd $problem_set_dir

if [ ! -d "$2" ]
then
  echo "Problem directory not found: $2"
  exit 1
fi

problem_id=$2
cd $problem_id
init_dir
run_dir
cleanup_dir
cd "$mydir"
exit 0;
