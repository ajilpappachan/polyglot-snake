# Polyglot-Snake

This is an excercise on architecture of polyglot projects, and understanding communication between binaries through `Application Binary Interfaces (ABI)`.

The objective is to make the core of a snake game in `C++` and render the game on desktop using `C#` and `python`, and on the web with `Typescript`.

The core is set-up with a partial implementation of the snake game, with all three clients (`C#`, `python`, and `TypeScript`) clients fully implemented.

## Setup

Run `BuildCore.bat` to build the dll and wasm files and copy them to client projects.

Requires `cmake`, `emsdk`, and `emscripten` installed. Core tests run automatically.

## Py-client

Run the `python client` with:

```shell
python clients/py/main.py
```

## Cs-Client

Open the visual studio `.sln` file to run the `C# client`.

## Ts-Client

```shell
cd ./clients/ts/
```

Run the `vite` application with

```shell
npm install
npm run dev
```

or build release build with

```shell
npm install
npm run build
```

## License

MIT — see [LICENSE](LICENSE).
