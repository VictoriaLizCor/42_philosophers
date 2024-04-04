#!/bin/bash

# Usage: 'bash custom.sh' from the Makefile file directory.

run()
{
	rule=$1
	echo "===[ $rule ]==="
	MAKE="make $rule"
	sleep 4

	arg="$p 401 200 200 $m"
	echo " > philo " $arg
	sleep 1
	echo ">>>$MAKE"
	$MAKE arg="$arg";
	sleep 1

	arg="$p 401 200 100 $m"
	echo " > philo " $arg
	sleep 1
	echo ">>>$MAKE"
	$MAKE arg="$arg";
	sleep 1

	arg="$p 401 200 150 $m"
	echo " > philo " $arg
	sleep 1
	echo ">>>$MAKE"
	$MAKE arg="$arg";
	sleep 1

	arg="$p 401 100 200 $m"
	echo " > philo " $arg
	sleep 1
	echo ">>>$MAKE"
	$MAKE arg="$arg";
	sleep 1

	arg="$p 401 100 150 $m"
	echo " > philo " $arg
	sleep 1
	echo ">>>$MAKE"
	$MAKE arg="$arg";
	sleep 1

	arg="$p 401 150 200 $m"
	echo " > philo " $arg
	sleep 1
	echo ">>>$MAKE"
	$MAKE arg="$arg";
	sleep 1
}

run "$c";
##with no debug and allocation sanitizers
# run "D=0 S=0 re start";
## with debug and no sanitizers
# run "D=2 S=0 re start";
## with debug and thread sanitizers
# run "D=2 S=0 re start";
## with no debug and thread sanitizers
# run "D=0 S=1 re start";
OS=$(uname)
if [[ "$OS" == 'Darwin' ]]; then
   run "re leaks";
elif [[ "$OS" == 'Linux' ]]; then
	run "re val";
	run "re hel";
fi