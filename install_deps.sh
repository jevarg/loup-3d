#!/bin/bash

export CONAN_REVISIONS_ENABLED=1
export CONAN_USER_HOME="$PWD"

conan install --build missing conanfile.txt
