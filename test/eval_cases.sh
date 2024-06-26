#!/bin/bash

# Usage: 'bash custom.sh' from the Makefile file directory.

run()
{
	rule=$1
	echo "===[ $rule ]==="
	MAKE="make $rule"
	sleep 4

	arg="1 800 200 200"
	echo " > philo " $arg
	sleep 1
	echo ">>>$MAKE"
	$MAKE arg="$arg";
	echo "  >>> died <<<"
	sleep 1

	arg="5 800 200 200 2"
	echo " > philo " $arg
	sleep 1
	$MAKE arg="$arg";

	arg="4 410 200 200 7"
	echo " > philo " $arg
	sleep 1
	$MAKE arg="$arg";

	arg="4 310 200 100"
	echo " > philo " $arg
	sleep 1
	$MAKE arg="$arg";
	echo "  >>> died <<<"
	sleep 1

	arg="2 410 200 200 7"
	echo " > philo " $arg
	sleep 1
	$MAKE arg="$arg";

	arg="2 310 200 200"
	echo " > philo " $arg
	$MAKE arg="$arg";
	echo "  >>> Invalid input <<<"
	sleep 2
}

run "re start";
#with no debug and allocation sanitizers
run "D=0 S=0 re start";
# with no debug and thread sanitizers
run "D=0 S=1 re start";
OS=$(uname)
if [[ "$OS" == 'Darwin' ]]; then
   run "re leaks";
elif [[ "$OS" == 'Linux' ]]; then
	run "re val";
	run "re hel";
fi