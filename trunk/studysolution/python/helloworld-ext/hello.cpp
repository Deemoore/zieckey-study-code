#include "Python.h"

PyObject* hello(PyObject* self, PyObject* args){
    const char * str;

    if (! PyArg_ParseTuple(args, "s", &str))
      return NULL;


    return Py_BuildValue("s",str);
}



static PyMethodDef moduleMethods[] = 
{
    //python function,  the real c++ function,  Tuple as args,  the comments
    {"getstr",           hello,                  METH_VARARGS,   "hello comments"},
    {NULL, NULL, 0, NULL}

};

PyMODINIT_FUNC inithello(void){
    Py_InitModule("hello", moduleMethods);
}
