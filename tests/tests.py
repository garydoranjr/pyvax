""" adaptation of part of Lawrence M. Baker's libvaxdata test suite for Gary Doran's PyVAX wrapper

Authors
-------
|    Jean-Luc Margot (jlm@epss.ucla.edu)

Jean-Luc Margot 
University of California, Los Angeles.
"""

import pyvax as pv
import numpy as np
from pytest import approx

def func_i2(x):
    fstr = pv.from_vax_i2(x)
    print(np.frombuffer(fstr, dtype=np.int16, count=1))
    return np.frombuffer(fstr, dtype=np.int16, count=1)

def func_i4(x):
    fstr = pv.from_vax_i4(x)
    print(np.frombuffer(fstr, dtype=np.int32, count=1))
    return np.frombuffer(fstr, dtype=np.int32, count=1)

def func_f4(x):
    fstr = pv.from_vax_r4(x)
    print(np.frombuffer(fstr, dtype=np.float32, count=1))
    return np.frombuffer(fstr, dtype=np.float32, count=1)

def func_d8(x):
    fstr = pv.from_vax_d8(x)
    print(np.frombuffer(fstr, dtype=np.float64, count=1))
    return np.frombuffer(fstr, dtype=np.float64, count=1)

def func_g8(x):
    fstr = pv.from_vax_g8(x)
    print(np.frombuffer(fstr, dtype=np.float64, count=1))
    return np.frombuffer(fstr, dtype=np.float64, count=1)

def test_i2():
    assert func_i2(b'\x01\x00') ==      1
    assert func_i2(b'\xFF\xFF') ==     -1
    assert func_i2(b'\x00\x01') ==    256
    assert func_i2(b'\x00\xFF') ==   -256
    assert func_i2(b'\x39\x30') ==  12345
    assert func_i2(b'\xC7\xCF') == -12345

def test_i4():
    assert func_i4(b'\x01\x00\x00\x00') ==          1
    assert func_i4(b'\xFF\xFF\xFF\xFF') ==         -1
    assert func_i4(b'\x00\x01\x00\x00') ==        256
    assert func_i4(b'\x00\xFF\xFF\xFF') ==       -256
    assert func_i4(b'\x00\x00\x01\x00') ==      65536
    assert func_i4(b'\x00\x00\xFF\xFF') ==     -65536
    assert func_i4(b'\x00\x00\x00\x01') ==   16777216
    assert func_i4(b'\x00\x00\x00\xFF') ==  -16777216
    assert func_i4(b'\x15\xCD\x5B\x07') ==  123456789
    assert func_i4(b'\xEB\x32\xA4\xF8') == -123456789   

def test_f4():
    assert func_f4(b'\x80\x40\x00\x00') == approx(1.000000, rel=1e-7)     
    assert func_f4(b'\x80\xC0\x00\x00') == approx(-1.000000, rel=1e-7)     
    assert func_f4(b'\x60\x41\x00\x00') == approx(3.500000, rel=1e-7)     
    assert func_f4(b'\x60\xC1\x00\x00') == approx(-3.500000, rel=1e-7)     
    assert func_f4(b'\x49\x41\xD0\x0F') == approx(3.141590, rel=1e-7)     
    assert func_f4(b'\x49\xC1\xD0\x0F') == approx(-3.141590, rel=1e-7)     
    assert func_f4(b'\xF0\x7D\xC2\xBD') == approx(9.9999999E+36, rel=1e-7)
    assert func_f4(b'\xF0\xFD\xC2\xBD') == approx(-9.9999999E+36, rel=1e-7)
    assert func_f4(b'\x08\x03\xEA\x1C') == approx(9.9999999E-38, rel=1e-7)
    assert func_f4(b'\x08\x83\xEA\x1C') == approx(-9.9999999E-38, rel=1e-7)
    assert func_f4(b'\x9E\x40\x52\x06') == approx(1.234568, rel=1e-7)     
    assert func_f4(b'\x9E\xC0\x52\x06') == approx(-1.234568, rel=1e-7)     

def test_d8():
    assert func_d8(b'\x80\x40\x00\x00\x00\x00\x00\x00') == approx(1.000000000000000, rel=1e-14) 
    assert func_d8(b'\x80\xC0\x00\x00\x00\x00\x00\x00') == approx(-1.000000000000000, rel=1e-14)
    assert func_d8(b'\x60\x41\x00\x00\x00\x00\x00\x00') == approx(3.500000000000000, rel=1e-14) 
    assert func_d8(b'\x60\xC1\x00\x00\x00\x00\x00\x00') == approx(-3.500000000000000, rel=1e-14)
    assert func_d8(b'\x49\x41\xDA\x0F\x21\xA2\xBE\x68') == approx(3.141592653589793, rel=1e-14)
    assert func_d8(b'\x49\xC1\xDA\x0F\x21\xA2\xBE\x68') == approx(-3.141592653589793, rel=1e-14)
    assert func_d8(b'\xF0\x7D\xC2\xBD\xBB\x1A\xDB\x48') == approx(1.0000000000000000E+37, rel=1e-14)
    assert func_d8(b'\xF0\xFD\xC2\xBD\xBB\x1A\xDB\x48') == approx(-1.0000000000000000E+37, rel=1e-14)
    assert func_d8(b'\x08\x03\xEA\x1C\x54\x14\x75\x5C') == approx(9.9999999999999999E-38, rel=1e-14)
    assert func_d8(b'\x08\x83\xEA\x1C\x54\x14\x75\x5C') == approx(-9.9999999999999999E-38, rel=1e-14)
    assert func_d8(b'\x9E\x40\x52\x06\x62\x14\xE7\xCE') == approx(1.234567890123450, rel=1e-14)
    assert func_d8(b'\x9E\xC0\x52\x06\x62\x14\xE7\xCE') == approx(-1.234567890123450, rel=1e-14)

def test_g8():
    assert func_g8(b'\x10\x40\x00\x00\x00\x00\x00\x00') == approx(1.000000000000000, rel=1e-14)
    assert func_g8(b'\x10\xC0\x00\x00\x00\x00\x00\x00') == approx(-1.000000000000000, rel=1e-14)
    assert func_g8(b'\x2C\x40\x00\x00\x00\x00\x00\x00') == approx(3.500000000000000, rel=1e-14)
    assert func_g8(b'\x2C\xC0\x00\x00\x00\x00\x00\x00') == approx(-3.500000000000000, rel=1e-14)
    assert func_g8(b'\x29\x40\xFB\x21\x44\x54\x18\x2D') == approx(3.141592653589793, rel=1e-14)
    assert func_g8(b'\x29\xC0\xFB\x21\x44\x54\x18\x2D') == approx(-3.141592653589793, rel=1e-14)
    assert func_g8(b'\xBE\x47\xB8\x17\x57\x43\x1B\x69') == approx(1.0000000000000000E+37, rel=1e-14)
    assert func_g8(b'\xBE\xC7\xB8\x17\x57\x43\x1B\x69') == approx(-1.0000000000000000E+37, rel=1e-14)
    assert func_g8(b'\x61\x38\x9D\x03\x8A\x42\x8F\x8B') == approx(9.9999999999999999E-38, rel=1e-14)
    assert func_g8(b'\x61\xB8\x9D\x03\x8A\x42\x8F\x8B') == approx(-9.9999999999999999E-38, rel=1e-14)
    assert func_g8(b'\x13\x40\xCA\xC0\x8C\x42\xDD\x59') == approx(1.234567890123450, rel=1e-14)
    assert func_g8(b'\x13\xC0\xCA\xC0\x8C\x42\xDD\x59') == approx(-1.234567890123450, rel=1e-14)

