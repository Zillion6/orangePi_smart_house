#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "face.h"

void face_Init(void)
{
    Py_Initialize();
    
    PyObject *sys = PyImport_ImportModule("sys");
    PyObject *path = PyObject_GetAttrString(sys, "path");
    PyList_Append(path, PyUnicode_FromString("."));
}

void face_Finalize(void)
{
    Py_Finalize();
}
  
double alicloud_Search_Face(void)
{
    system(WGET_CMD);

    PyObject *pModule = PyImport_ImportModule("face");
    if (!pModule)
    {
        PyErr_Print();
        printf("Error: failed to load face.py\n");
        goto FAILED_MODULE;
    }
    
    PyObject *pFunc = PyObject_GetAttrString(pModule, "alicloud_Search_Face");
    if (!pFunc)
    {
        PyErr_Print();
        printf("Error: failed to load alicloud_Search_Face\n");
        goto FAILED_FUNC;
    }
		
    PyObject *pValue = PyObject_CallObject(pFunc, NULL);
	if (!pValue)
    {
        PyErr_Print();
        printf("Error: function call failed\n");
        goto FAILED_VALUE;
    }
		
	double result = 0.00;
	if(!PyArg_Parse(pValue, "d", &result))
    {
        PyErr_Print();
        printf("Error: parse failed\n");
        goto FAILED_RESULT;
    }
    
    printf("result = %lf\n", result);
    
FAILED_RESULT:
    Py_DECREF(pValue);
FAILED_VALUE:
    Py_DECREF(pFunc);
FAILED_FUNC:
    Py_DECREF(pModule);
FAILED_MODULE:
    return result;
}