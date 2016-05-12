static PyObject * THPStorage_(size)(THPStorage *self)
{
  HANDLE_TH_ERRORS
  return PyLong_FromLong(THStorage_(size)(self->cdata));
  END_HANDLE_TH_ERRORS
}

static PyObject * THPStorage_(elementSize)(THPStorage *self)
{
  HANDLE_TH_ERRORS
  return PyLong_FromLong(THStorage_(elementSize)());
  END_HANDLE_TH_ERRORS
}

static PyObject * THPStorage_(retain)(THPStorage *self)
{
  HANDLE_TH_ERRORS
  THStorage_(retain)(self->cdata);
  return (PyObject*)self;
  END_HANDLE_TH_ERRORS
}

static PyObject * THPStorage_(free)(THPStorage *self)
{
  HANDLE_TH_ERRORS
  THStorage_(free)(self->cdata);
  return (PyObject*)self;
  END_HANDLE_TH_ERRORS
}

static PyObject * THPStorage_(new)(THPStorage *self)
{
  HANDLE_TH_ERRORS
  return THPStorage_(newObject)(THStorage_(new)());
  END_HANDLE_TH_ERRORS
}

static PyObject * THPStorage_(resize)(THPStorage *self, PyObject *number_arg)
{
  HANDLE_TH_ERRORS
  if (!PyLong_Check(number_arg))
    return NULL;
  long newsize = PyLong_AsLong(number_arg);
  if (PyErr_Occurred())
    return NULL;
  THStorage_(resize)(self->cdata, newsize);
  Py_INCREF(self);
  return (PyObject*)self;
  END_HANDLE_TH_ERRORS
}

static PyObject * THPStorage_(fill)(THPStorage *self, PyObject *number_arg)
{
  HANDLE_TH_ERRORS
  real rvalue;
  if (!THPUtils_(parseReal)(number_arg, &rvalue))
    return NULL;
  THStorage_(fill)(self->cdata, rvalue);
  Py_INCREF(self);
  return (PyObject*)self;
  END_HANDLE_TH_ERRORS
}

// Declared in StorageCopy.cpp
static PyObject * THPStorage_(copy)(THPStorage *self, PyObject *other);

static PyMethodDef THPStorage_(methods)[] = {
  {"copy", (PyCFunction)THPStorage_(copy), METH_O, NULL},
  {"elementSize", (PyCFunction)THPStorage_(elementSize), METH_NOARGS, NULL},
  {"fill", (PyCFunction)THPStorage_(fill), METH_O, NULL},
  {"free", (PyCFunction)THPStorage_(free), METH_NOARGS, NULL},
  {"new", (PyCFunction)THPStorage_(new), METH_NOARGS, NULL},
  {"resize", (PyCFunction)THPStorage_(resize), METH_O, NULL},
  {"retain", (PyCFunction)THPStorage_(retain), METH_NOARGS, NULL},
  {"size", (PyCFunction)THPStorage_(size), METH_NOARGS, NULL},
  {NULL}
};
