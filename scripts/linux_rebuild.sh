#!/bin/bash

CMAKE_BUILD_TYPE='Debug'

if [ "$1" = "r" ]; then
	CMAKE_BUILD_TYPE='Release'
fi

pwd
cd ./build/
bash ./linclean.sh
cd ../scripts/
bash ./linux_build.sh "$CMAKE_BUILD_TYPE"
