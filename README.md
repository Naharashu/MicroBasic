# MicroBasic

MicroBasic is a BASIC language implementation that compiles to its own VM bytecode. Its written in C++.

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
load R1 1 // x
load R2 2 // y
add R2 R1 // +x
load R3 0 // sum

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
