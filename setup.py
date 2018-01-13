#!/usr/bin/env python
import os
import numpy as np
from setuptools import setup
from setuptools.extension import Extension

SOURCE_DIR = 'src'
SOURCES = [
    'pyvax.c',
    'convert_vax_data.c',
]

pyvax = Extension(
    'pyvax',
    sources=[os.path.join(SOURCE_DIR, s) for s in SOURCES],
)

setup(
    name='pyvax',
    version='1.0',
    description=(
      "Python wrapper the libvaxdata library"
    ),
    author='Gary Doran',
    author_email='garydoranjr@gmail.com',
    platforms=['unix'],
    provides=['pyvax'],
    ext_modules=[pyvax],
)
