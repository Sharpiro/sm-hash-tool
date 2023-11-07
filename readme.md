# SM-Hash-Tool

## Description

Reverse-engineering of the original `SMPS4HashTool.exe`, a tool used for hashing asset names for the Marvel SpiderMan games.

## Build

### Linux

- pre-reqs
  - gcc
  - make

```sh
make
```

### Windows

- pre-reqs
  - clang

```sh
build-win.bat
```

## Usage

```sh
echo 'a\\b/c' | ./sm_hash_tool
```

```sh
./sm_hash_tool lines_of_text.txt
```

## Test

```sh
python test/smps_exe_test.py
```
