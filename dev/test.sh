#!/bin/bash

sys= uname -s
test $sys "Darwin"
if [ $? != 0 ]
then
  slow=0
  L="\""
else
  slow=1
  L="'"
fi

# color
RED=\\x1B[31m
GRN=\\x1B[32m
YEL=\\x1B[33m
BLU=\\x1B[34m
MAG=\\x1B[35m
CYN=\\x1B[36m
WHT=\\x1B[37m
RESET=\\x1B[0m

# -- -- -- var
outfileval="$PWD/out/val.log"
val="valgrind --trace-children=yes --track-fds=yes --suppressions=/tmp/supp.txt --log-file=$outfileval"

## test

heredock=(
  "$"
)

testlist=(
  'ls'
  'echo'
  'echo -n'
  'echo $PWD'
  '""'
  "''"
  "ls -la"
  "|"
  "hello\"\"gorge"
  "echo hello\"\"gorge"
  "echo '\"    	  \"'"
  "				"
  "		  			''"
  "''			"
  "echo a | echo"
  "echo   | echo"
  "echo a | echo a"
  "echo   | echo a"
  "ms -i"
  "echo a a a | cat | wc"
  "env | grep 'LOGNAME'"
  "pwd | cut -c5- | wc "
  "$ $\?"
  "\""
  "'"
  "ls < a"
  "echo < a"
  "echo > a"
  "ls > a"
  "cat < a"
  "< b cat -e"
  "< a cat -e"
  "< b < a cat"
  "?"
  "<"
  "< <"
  "<<"
  "<< <"
  "<<<"
  "<<< <"
  ">"
  "> >"
  ">>"
  ">> >"
  ">>>"
  ">>> >"
  "<>"
  "< >"
  "<|>"
  "><"
  "> <"
  ">|<"
  "pwd |  echo b"
  "ls | ls |ls| ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls |ls | echo"
  "echo \"\" ' ' \"\""
  "exit 1"
  "exit 0"
  "exit 42"
  "exit 123"
  "exit 321"
  "exit a"
  "exit 1a"
  "exit a1"
  "\$a"
)

i=${#testlist[@]}
j=0
di=0

function runTest() {
  printf "$YEL --- --- ---$RESET\n"
  rm -fr a b
  bash -c "${testlist[$j]}" > out/out_ba
  bacode=$?
  rm -fr a b
  $val ../minishell -c "${testlist[$j]}" > out/out_ms
  mscode=$?
  err=0
  if [ $bacode != $mscode ];
  then
    printf \%s\ "Error: return value\n shell give $GRN$bacode$RESET ms give $RED$mscode$RESET \n"
  fi
  rm -f out/val.log
  diff  out/out_ba out/out_ms >> diff.txt
}

# start of scrip
rm -r diff.txt
make -C .. re
echo "making dir"
mkdir -p out

while [ $j -lt $i ]
do
  runTest
  di=$?
  if [ $di != 0 ]
  then
    printf \%s\ "❌$RED ${testlist[$j]} $RESET\n"
    printf \%s\ "❌${testlist[$j]}\n" >> diff.txt
    echo 'ms >'
    cat -be out/out_ms
    echo 'ms <'
    echo 'ba >'
    cat -be out/out_ba
    echo 'ba <'
  else
    printf \%s\ "✅$GRN ${testlist[$j]} $RESET\n"
  fi
  j=$((j + 1))
  if [ $slow == 1 ]
  then
    echo '- - - - -'
  fi
  sleep 0.1
done
read -p "clean project? (Y/N): " confirm && [[ $confirm == [yY] || $confirm == [yY][eE][sS] ]] || exit 0
make -C .. fclean