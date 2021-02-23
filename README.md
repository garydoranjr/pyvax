PyVAX
=====

By [Gary Doran](mailto:garydoranjr@gmail.com)

## About

This Python package wraps the `libvaxdata` library written by Lawrence M.
Baker. The purpose of the library is to convert the binary representation of
data stored in [VAX](https://en.wikipedia.org/wiki/VAX) format to modern,
standard IEEE representations. Conversion from IEEE to VAX format is also
supported.

## Installation

To install:  
`python setup.py install`

## Testing

After installation, run:  
`pytest tests/tests.py`

## Usage

See the original [library documentation](http://pubs.usgs.gov/of/2005/1424/) for
a description of the conversion functions available and formats supported. For
each library function, there is a corresponding Python function of the same name
that takes a string argument and returns a string. The input is expected to be a
byte string in the input format, and the output is a byte string in the output
format (for IEEE output formats, the byte order is the native byte order of the
machine).

The `numpy.frombuffer` function can be used to convert the output of `pyvax` to
an array of numeric values. For example:

    >>> import pyvax
    >>> import numpy as np
    >>> fstr = pyvax.from_vax_r4(b'\xd9\xc2\x8b&\xd9\xc2]\x01')
    >>> print np.frombuffer(fstr, dtype='<f4', count=2)
    [-27.14381981 -27.12566566]

## Citation

Baker, L.M., 2005, libvaxdata: VAX Data Format Conversion Routines:
U.S. Geological Survey Open-File Report 2005-1424
[http://pubs.usgs.gov/of/2005/1424/](http://pubs.usgs.gov/of/2005/1424/)
