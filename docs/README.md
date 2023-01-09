# Please browse the docs from either http://nrf24.github.io/RF24 or https://rf24.rtfd.io

## Intended for use in Doxygen

The markdown files (\*.md) in this docs folder contain relative hyperlinks. Any relative hyperlinks will not work when viewing these markdown files in github.

----

## Building the docs

Navigate to the repo's docs folder:

```shell
cd docs
```

Install Doxygen (v1.9.5 or newer) and run the following command from the repo's docs folder:

```shell
doxygen
```

The Doxygen HTML output is now in docs/html. The Doxygen XML output in docs/sphinx/xml can be optionally used to generate Sphinx output.

### Generating Sphinx docs (optional)

To build the Sphinx docs based on Doxygen's XML output, first install the necessary python dependencies.

``` shell
python -m pip install docs/sphinx/requirements.txt
```

Now build the Sphinx docs (after building the Doxygen output) from the repo's docs folder:

```shell
sphinx-build sphinx _build/html
```

The Sphinx HTML output now exists in docs/_build/html.
