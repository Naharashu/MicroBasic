# MicroBasic

MicroBasic is a BASIC language implementation that compiles to its own VM bytecode. Its written in C++.

## Features

- 256 variables, all in global scope(compared to 26 in TinyBasic)
- 1024 max recursion depth
- consts
- string(indev)
- fast execution due to usage of register VM

## What it can execute(or will execute):

```js
LET X = 1
LET Y = X + 2
LET SUM = 0

add:
    SUM = X + Y
    RETURN

GOSUB add
PRINT SUM
END
```

it will compile to something like

```js
LOAD_VAR_VAR R1 VARS[x] // x
LOAD_VAR R2 VARS[y] // y
add R2 R1 // +x
LOAD_VAR R3 VARS[sum] // sum

_add:
    add R3 R1
    add R3 R2
    ret

call _add
print r3
hlt
``` 

## Usage

Direct run
```
microbasic hello.basic
```

Verbose mode

```
microbasic hello.basic -verbose
```
