#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#include "convert_vax_data.h"

#ifndef _NPY_3KCOMPAT_H_
#define _NPY_3KCOMPAT_H_

#if PY_VERSION_HEX >= 0x03000000
#ifndef NPY_PY3K
#define NPY_PY3K 1
#endif
#endif

#if defined(NPY_PY3K)

#define PyString_Type PyBytes_Type
#define PyStringObject PyBytesObject
#define PyString_FromStringAndSize PyBytes_FromStringAndSize
#define PyString_AsString PyBytes_AsString
#define PyString_Size PyBytes_Size

#define MOD_DEF(ob, name, doc, methods)	\
  static struct PyModuleDef moduledef = { \
    PyModuleDef_HEAD_INIT, name, doc, -1, methods, }; \
  ob = PyModule_Create(&moduledef);

#define MOD_INIT(name) PyMODINIT_FUNC PyInit_##name(void)
#define MOD_SUCCESS_VAL(val) val
#define MOD_ERROR_VAL NULL

#else

#define PyBytes_Type PyString_Type
#define PyBytesObject PyStringObject
#define PyBytes_FromStringAndSize PyString_FromStringAndSize
#define PyBytes_AsString PyString_AsString
#define PyBytes_Size PyString_Size

#define MOD_DEF(ob, name, doc, methods)	\
  ob = Py_InitModule3(name, methods, doc);

#define MOD_INIT(name) PyMODINIT_FUNC init##name(void)
#define MOD_SUCCESS_VAL(val)
#define MOD_ERROR_VAL

#endif /* NPY_PY3K */


typedef enum {
    FROM_VAX = 0,
    TO_VAX = 1
} VaxConversionDirection;

typedef enum {
    VAX_I2 = 0,
    VAX_I4 = 1,
    VAX_R4 = 2,
    VAX_D8 = 3,
    VAX_G8 = 4,
    VAX_H16 = 5,
} VaxType;

static size_t TYPE_SIZES[] = {2, 4, 4, 8, 8, 16};

static PyObject* generic_conversion(PyObject *self, PyObject *args,
    VaxConversionDirection direction, VaxType vtype) {

    PyStringObject* input = NULL;
    if (!PyArg_ParseTuple(args, "O!", &PyString_Type, &input)) {
        PyErr_SetString(PyExc_ValueError,
            "Function takes a single string argument");
        return NULL;
    }

    size_t type_size = TYPE_SIZES[vtype];

    char* input_str = PyString_AsString((PyObject*)input);
    size_t input_size = (size_t)PyString_Size((PyObject*)input);
    if ((input_size % type_size) != 0) {
        PyErr_SetString(PyExc_ValueError,
            "Input string must be a multiple of type size");
        return NULL;
    }
    size_t array_size = input_size / type_size;
    char* output_str = (char*) calloc(input_size, sizeof(char));

    switch (direction) {
        case FROM_VAX:
            switch (vtype) {
                case VAX_I2:
                    from_vax_i2(
                        (void*) input_str,
                        (void*) output_str,
                        (int*)  &array_size
                    );
                    break;
                case VAX_I4:
                    from_vax_i4(
                        (void*) input_str,
                        (void*) output_str,
                        (int*)  &array_size
                    );
                    break;
                case VAX_R4:
                    from_vax_r4(
                        (void*) input_str,
                        (void*) output_str,
                        (int*)  &array_size
                    );
                    break;
                case VAX_D8:
                    from_vax_d8(
                        (void*) input_str,
                        (void*) output_str,
                        (int*)  &array_size
                    );
                    break;
                case VAX_G8:
                    from_vax_g8(
                        (void*) input_str,
                        (void*) output_str,
                        (int*)  &array_size
                    );
                    break;
                case VAX_H16:
                    from_vax_h16(
                        (void*) input_str,
                        (void*) output_str,
                        (int*)  &array_size
                    );
                    break;
                default:
                    free(output_str);
                    PyErr_SetString(PyExc_ValueError,
                        "Unknown VAX type");
                    return NULL;
            }
            break;
        case TO_VAX:
            switch (vtype) {
                case VAX_I2:
                    to_vax_i2(
                        (void*) input_str,
                        (void*) output_str,
                        (int*)  &array_size
                    );
                    break;
                case VAX_I4:
                    to_vax_i4(
                        (void*) input_str,
                        (void*) output_str,
                        (int*)  &array_size
                    );
                    break;
                case VAX_R4:
                    to_vax_r4(
                        (void*) input_str,
                        (void*) output_str,
                        (int*)  &array_size
                    );
                    break;
                case VAX_D8:
                    to_vax_d8(
                        (void*) input_str,
                        (void*) output_str,
                        (int*)  &array_size
                    );
                    break;
                case VAX_G8:
                    to_vax_g8(
                        (void*) input_str,
                        (void*) output_str,
                        (int*)  &array_size
                    );
                    break;
                case VAX_H16:
                    to_vax_h16(
                        (void*) input_str,
                        (void*) output_str,
                        (int*)  &array_size
                    );
                    break;
                default:
                    free(output_str);
                    PyErr_SetString(PyExc_ValueError,
                        "Unknown VAX type");
                    return NULL;
            }
            break;
        default:
            free(output_str);
            PyErr_SetString(PyExc_ValueError, "Unknown conversion direction");
            return NULL;
    }

    PyObject* retval = PyString_FromStringAndSize(
        output_str, (Py_ssize_t)input_size);

    free(output_str);

    return retval;
}

static PyObject* _to_vax_i2(PyObject *self, PyObject *args) {
    return generic_conversion(self, args, TO_VAX, VAX_I2);
}

static PyObject* _to_vax_i4(PyObject *self, PyObject *args) {
    return generic_conversion(self, args, TO_VAX, VAX_I4);
}

static PyObject* _to_vax_r4(PyObject *self, PyObject *args) {
    return generic_conversion(self, args, TO_VAX, VAX_R4);
}

static PyObject* _to_vax_d8(PyObject *self, PyObject *args) {
    return generic_conversion(self, args, TO_VAX, VAX_D8);
}

static PyObject* _to_vax_g8(PyObject *self, PyObject *args) {
    return generic_conversion(self, args, TO_VAX, VAX_G8);
}

static PyObject* _to_vax_h16(PyObject *self, PyObject *args) {
    return generic_conversion(self, args, TO_VAX, VAX_H16);
}

static PyObject* _from_vax_i2(PyObject *self, PyObject *args) {
    return generic_conversion(self, args, FROM_VAX, VAX_I2);
}

static PyObject* _from_vax_i4(PyObject *self, PyObject *args) {
    return generic_conversion(self, args, FROM_VAX, VAX_I4);
}

static PyObject* _from_vax_r4(PyObject *self, PyObject *args) {
    return generic_conversion(self, args, FROM_VAX, VAX_R4);
}

static PyObject* _from_vax_d8(PyObject *self, PyObject *args) {
    return generic_conversion(self, args, FROM_VAX, VAX_D8);
}

static PyObject* _from_vax_g8(PyObject *self, PyObject *args) {
    return generic_conversion(self, args, FROM_VAX, VAX_G8);
}

static PyObject* _from_vax_h16(PyObject *self, PyObject *args) {
    return generic_conversion(self, args, FROM_VAX, VAX_H16);
}

static PyMethodDef pyvax_methods[] = {
   { "from_vax_i2", (PyCFunction)_from_vax_i2, METH_VARARGS,
    "Converts from VAX I2 to I16.\n"
    "@param input : VAX I2 byte string\n"
    "@return      : I16 byte string"
   },
   { "from_vax_i4", (PyCFunction)_from_vax_i4, METH_VARARGS,
    "Converts from VAX I4 to I32.\n"
    "@param input : VAX I4 byte string\n"
    "@return      : I32 byte string"
   },
   { "from_vax_r4", (PyCFunction)_from_vax_r4, METH_VARARGS,
    "Converts from VAX R4 to IEEE F32.\n"
    "@param input : VAX R4 byte string\n"
    "@return      : IEEE F32 byte string"
   },
   { "from_vax_d8", (PyCFunction)_from_vax_d8, METH_VARARGS,
    "Converts from VAX D8 to IEEE F64.\n"
    "@param input : VAX D8 byte string\n"
    "@return      : IEEE F64 byte string"
   },
   { "from_vax_g8", (PyCFunction)_from_vax_g8, METH_VARARGS,
    "Converts from VAX G8 to IEEE F64.\n"
    "@param input : VAX G8 byte string\n"
    "@return      : IEEE F64 byte string"
   },
   { "from_vax_h16", (PyCFunction)_from_vax_h16, METH_VARARGS,
    "Converts from VAX H16 to Alpha 128-bit float.\n"
    "@param input : VAX H16 byte string\n"
    "@return      : Alpha 128-bit float byte string"
   },
   { "to_vax_i2", (PyCFunction)_to_vax_i2, METH_VARARGS,
    "Converts from I16 to VAX I2.\n"
    "@param input : I16 byte string\n"
    "@return      : VAX I2 byte string"
   },
   { "to_vax_i4", (PyCFunction)_to_vax_i4, METH_VARARGS,
    "Converts from I32 to VAX I4.\n"
    "@param input : I32 byte string\n"
    "@return      : VAX I4 byte string"
   },
   { "to_vax_r4", (PyCFunction)_to_vax_r4, METH_VARARGS,
    "Converts from IEEE F32 to VAX R4.\n"
    "@param input : IEEE F32 byte string\n"
    "@return      : VAX R4 byte string"
   },
   { "to_vax_d8", (PyCFunction)_to_vax_d8, METH_VARARGS,
    "Converts from IEEE F64 to VAX D8.\n"
    "@param input : IEEE F64 byte string\n"
    "@return      : VAX D8 byte string"
   },
   { "to_vax_g8", (PyCFunction)_to_vax_g8, METH_VARARGS,
    "Converts from IEEE F64 to VAX G8.\n"
    "@param input : IEEE F64 byte string\n"
    "@return      : VAX G8 byte string"
   },
   { "to_vax_h16", (PyCFunction)_to_vax_h16, METH_VARARGS,
    "Converts from Alpha 128-bit float to VAX H16.\n"
    "@param input : Alpha 128-bit float byte string\n"
    "@return      : VAX H16 byte string"
   },
   { NULL, NULL, 0, NULL }
};

MOD_INIT(pyvax)
{
    PyObject *module;

    MOD_DEF(module, "pyvax", "Python libvaxdata wrapper", pyvax_methods);

    if (module == NULL)
      return MOD_ERROR_VAL;

    return MOD_SUCCESS_VAL(module);
}

#endif /* _NPY_3KCOMPAT_H_ */
