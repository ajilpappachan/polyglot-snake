# Polyglot-Snake

This is an exercise on architecture of polyglot projects, and understanding communication between binaries through `Application Binary Interfaces (ABI)`.

The objective is to make the core of a snake game in `C++` and render the game on desktop using `C#` and `python`, and on the web with `Typescript`.

The core carries the full game: movement, direction changes, wrap-around at the grid edges, self-collision and the fail state, fruit spawning and growth. All three clients (`C#`, `python`, and `TypeScript`) are fully implemented, and each pins the ABI version it was built against.

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
