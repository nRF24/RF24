# AGENTS

Project type: Arduino library that can be compiled for Linux and the Pico SDK.

## Building docs

requires: [doxygen]

steps:

- `cd docs`
- `doxygen` (generates `docs/html`)
- optional: open `docs/html/index.html`

## Build library

requires: `cmake`, build tools

steps:

- `cmake -B build -S . [...cmake options]`
- `cmake --build build`
- `sudo cmake --install build` (required for building examples)

## Examples (Linux)

requires: `cmake`, build tools

steps:

- `cmake -B examples_linux/build examples_linux [...cmake options]`
- `cmake --build examples_linux/build`

## Pico examples

requires: `cmake`, [PicoSDK] (Windows: `ninja` may be required)

steps:

- `cmake -B examples_pico/build examples_pico [...cmake opts]`
- `cmake --build examples_pico/build`

## Install Python wrapper

requires:

- `python`, `pip`, and Python C API headers
- `boost.python` (typically provided via `apt-get install`)

steps:

- Create a venv (can be done with various tools). Need only be done once.
- Activate the venv (depends on method used in previous step), if not already in
  active venv.
- `pip install -v ./pyRF24`

Notes about dependencies:

Most dependencies can be installed via
`apt-get install python3-dev libboost-python-dev`.

## Format sources

requires: `clang-format` v14.x

steps:

- `clang-format-14 -i --style=file <file>`
- On Windows (powershell does not expand globs):
  `clang-format -i --style=file <file>`

## Clang-tidy / static analysis

Note: clang-tidy can only be used when targeting Linux builds.
Prefer WSL when build on a Windows host machine.

- To generate a compilation database required by `clang-tidy`:
  - `cmake -B build -S . -DCMAKE_EXPORT_COMPILE_COMMANDS=ON`
- Run `clang-tidy` with the `-p` option pointing to the build directory:
  - `clang-tidy -p build <files>`

[PicoSDK]: https://github.com/raspberrypi/pico-sdk
[doxygen]: https://github.com/doxygen/doxygen
