# Polyglot-Snake

This is an excercise on architecture of polyglot projects, and understanding communication between binaries through `Application Binary Interfaces (ABI)`.

The objective is to make the core of a snake game in `C++` and render the game on desktop using `C#` and `python`, and on the web with `Typescript`.

## Setup

Build `core` first:

```shell
cmake -S core -B core/build
cmake --build core/build
```

Building `core` will also copy library files to clients.

Optional: Run smoke test to verify `core` built succesfully:

```shell
ctest --test-dir core/build -C Debug smoke
```

## Py-client

Run the `python client` with:

```shell
python clients/py/main.py
```
