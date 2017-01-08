#!/bin/sh

TEST=1
PASSED=0
FAILED=0

test () {
  gcc -Wall -Wextra -Werror -std=gnu99 -I./.. ../*.c src/$1 -o $2
  ./$2 > .tmp_$2
  diff .tmp_$2 res/$2
  return $?
}
getResult() {
  if [ $1 -eq 0 ]
  then
    PASSED=`expr $PASSED + 1`
    echo "\t\033[0;32msuccess\033[0;0m"
  else
    FAILED=`expr $FAILED + 1`
    echo "\t\033[0;36mfailed\033[0;0m"
  fi
}
clear() {
  wait
  rm .tmp_$2
  rm $2
}

showScore() {
  echo
  echo "\033[0;32m$PASSED test(s) PASSED\033[0;0m"
  echo "\033[0;36m$FAILED test(s) FAILED\033[0;0m"
  MISSING=`expr 9 - $TEST`
  echo "$MISSING test(s) MISSING"
  echo
}

echo "Ouailecome in sisse niou poule deï"
echo

echo "\033[0;1m\033[0;34mTest "$TEST":\033[0;0m isDirectory"
test main_isDirectory.c $TEST
getResult $?
clear main_isDirectory.c $TEST
showScore
TEST=`expr $TEST + 1`

echo "\033[0;1m\033[0;34mTest "$TEST":\033[0;0m access"
test main_access.c $TEST
getResult $?
clear main_access.c $TEST
showScore
TEST=`expr $TEST + 1`

echo "\033[0;1m\033[0;34mTest "$TEST":\033[0;0m appendFile"
test main_appendFile.c $TEST
getResult $?
clear main_appendFile.c $TEST
showScore
TEST=`expr $TEST + 1`

echo "\033[0;1m\033[0;34mTest "$TEST":\033[0;0m getFileSize"
test main_getFileSize.c $TEST
getResult $?
clear main_getFileSize.c $TEST
showScore
TEST=`expr $TEST + 1`

echo "\033[0;1m\033[0;34mTest "$TEST":\033[0;0m read"
test main_read.c $TEST
getResult $?
clear main_read.c $TEST
showScore
TEST=`expr $TEST + 1`

echo "\033[0;1m\033[0;34mTest "$TEST":\033[0;0m realPath"
test main_realPath.c $TEST
getResult $?
clear main_realPath.c $TEST
showScore
TEST=`expr $TEST + 1`

echo "\033[0;1m\033[0;34mTest "$TEST":\033[0;0m truncate"
test main_truncate.c $TEST
getResult $?
clear main_truncate.c $TEST
showScore
TEST=`expr $TEST + 1`

echo "\033[0;1m\033[0;34mTest "$TEST":\033[0;0m rename"
test main_rename.c $TEST
getResult $?
clear main_rename.c $TEST
showScore
TEST=`expr $TEST + 1`

echo "\033[0;1m\033[0;34mTest "$TEST":\033[0;0m write"
test main_write.c $TEST
getResult $?
clear main_write.c $TEST
showScore
TEST=`expr $TEST + 1`
