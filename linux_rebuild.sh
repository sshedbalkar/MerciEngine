#!/bin/bash

CMAKE_BUILD_TYPE='Debug'

if [ "$1" = "r" ]; then
	CMAKE_BUILD_TYPE='Release'
fi

cd ./build
bash ./linclean.sh
cd ..
bash ./linux_build.sh
