#!/usr/bin/env bash

export STOP=1
. test/assert.sh
. test/helper.sh

if which gmake 1>/dev/null 2>/dev/null;
    then export MAKE=gmake;
    else export MAKE=make;
fi

function setup {
  rm -rf test/tmp
  mkdir test/tmp
  cd test/tmp
  ln -s ../../Makefile .
  if ! [ -z "$CC" ];  then echo "CC  := ${CC}"  >> .compiler.mk; fi
  if ! [ -z "$FC"  ]; then echo "FC  := ${FC}"  >> .compiler.mk; fi
  if ! [ -z "$CXX" ]; then echo "CXX := ${CXX}" >> .compiler.mk; fi
}

function teardown {
  cd ../..
  rm -rf test/tmp
}

echo "Using program \"$MAKE\""
if ! [ -z "$CC" ];  then echo "CC  = \"$CC\" "; fi
if ! [ -z "$FC"  ]; then echo "FC  = \"$FC\" "; fi
if ! [ -z "$CXX" ]; then echo "CXX = \"$CXX\""; fi
echo

# Targets
echo -n "Testing Targets "
. test/targets/test_init.sh
. test/targets/test_standard.sh
echo
assert_end Targets
echo

for LANG in C C++ Fortran;
do
    lang=`echo $LANG | tr '[:upper:]' '[:lower:]'`

    echo -n "Testing $LANG "
    . test/$lang/test_single-file.sh
    . test/$lang/test_multiple-file.sh
    . test/$lang/test_static-lib.sh
    . test/$lang/test_shared-lib.sh
    . test/$lang/test_shared-file.sh
    echo
    assert_end "$LANG"
    echo
done
