@echo off

clang -Wall -Wno-format -D_CRT_SECURE_NO_WARNINGS -O2 ^
    -o sm_hash_tool.exe src/main.c src/hash_lookup_table.c
