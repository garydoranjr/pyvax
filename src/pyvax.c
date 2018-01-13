#include <stdlib.h>
#include <string.h>
#include <Python.h>

#include "convert_vax_data.h"

static PyObject* _from_vax_r4(PyObject *self, PyObject *args) {
    PyStringObject* input = NULL;
    if (!PyArg_ParseTuple(args, "O!", &PyString_Type, &input)) {
        PyErr_SetString(PyExc_ValueError, "Function takes a single string argument.");
        return NULL;
    }
    char* input_str = PyString_AsString((PyObject*)input);
    size_t input_size = strlen(input_str);
    int array_size = input_size / 4;
    char* output = (char*) calloc(input_size, sizeof(char));

    from_vax_r4((void*) input_str, (void*) output, &array_size);

    PyObject* retval = PyString_FromStringAndSize(output, (Py_ssize_t)input_size);

    free(output);

    return retval;
}

static PyMethodDef pyvax_methods[] = {
   { "from_vax_r4", (PyCFunction)_from_vax_r4, METH_VARARGS,
    "Converts from VAX R4 to IEEE F32.\n"
    "@param input : VAX R4 byte string\n"
    "@return      : IEEE F32 byte string"
   },
   { NULL, NULL, 0, NULL }
};

void initpyvax(void)
{
    PyObject *module;
    module = Py_InitModule3("pyvax", pyvax_methods,
                       "Python libvaxdata wrapper");
    //import_array();
}
