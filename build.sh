#!/bin/bash

options=`getopt -o bcghil --long clean,local,global,build,help,install -- "$@"`
if [ $? != 0 ] ; then echo "Failed parsing options." >&2 ; exit 1 ; fi
eval set -- "$options"

PREFIX=$HOME/.local
CLEAN=0
BUILD=0
INSTALL=0

while true; do
    case "$1" in
	-b | --build)
        BUILD=1
        ;;
    -c | --clean)
        CLEAN=1
        ;;
	-l | --local)
        PREFIX=$HOME/.local
        ;;
	-g | --global)
        PREFIX=/
        ;;
	-i | --install)
        INSTALL=1
        ;;
	-h | --help)
        echo "build.sh [-b] [-c] [-i] [-g|-l]"
		exit;
        ;;
    --)
        shift
        break
        ;;
    esac
    shift
done


if [ $CLEAN == 1 ]; then
	rm -rf build && mkdir build;
fi

cd build/ && cmake .. -DCMAKE_INSTALL_PREFIX=$PREFIX

if [ $BUILD == 1 ]; then
	make
fi

if [ $INSTALL == 1 ]; then
	make install
fi

