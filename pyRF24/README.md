# Individual python wrapper

> [!warning]
> This python wrapper for the RF24 C++ library was not intended
> for distribution on pypi.org. Any such attempts to publish this package
> is unauthorized and unofficial.

## Use pyRF24 instead

We recommend using the newer [pyRF24](https://github.com/nRF24/pyRF24) package
[available from pypi](https://pypi.org/project/pyrf24/) because

1. it is [practically drop-in compatible](https://nrf24.github.io/pyRF24/#migrating-to-pyrf24)
2. easier to install or get updates with popular package managers like pip
3. does not require the C++ libraries to be installed -- it uses its own isolated binaries
4. includes wrappers for RF24, RF24Network, RF24Mesh libraries
5. includes a new [fake BLE implementation](https://nrf24.github.io/pyRF24/ble_api.html)
6. has its own [dedicated documentation](https://nRF24.github.io/pyRF24)
7. is compatible with python's builtin `help()`
8. includes typing stub files for type checking tools like mypy

The only reason that you should need to keep using these older individual python
wrappers is if you must use python v3.6 or older.

You **cannot** use these individual wrappers in combination with the pyRF24 package.
