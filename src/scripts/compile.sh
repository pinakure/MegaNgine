#!/bin/bash
echo Compiling...
rm -rf out/src/*
make -f $SGDK/makefile.gen
