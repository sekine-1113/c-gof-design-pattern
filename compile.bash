#!/usr/bin/bash

mkdir -p bin
rm -f bin/*

for dir in behavioral creational structural; do
    for file in ${dir}/*.c; do
        filename=$(basename "${file}" .c)
        gcc "${file}" -o "bin/${filename}.exe"
    done
done
