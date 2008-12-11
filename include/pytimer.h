/*
 * pytimer.h
 * pyparted type definitions for pytimer.c
 *
 * Copyright (C) 2007  Red Hat, Inc.
 *
 * This copyrighted material is made available to anyone wishing to use,
 * modify, copy, or redistribute it subject to the terms and conditions of
 * the GNU General Public License v.2, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY expressed or implied, including the implied warranties of
 * MERCHANTABILITY or FITNESS FOR A * PARTICULAR PURPOSE.  See the GNU General
 * Public License for more details.  You should have received a copy of the
 * GNU General Public License along with this program; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.  Any Red Hat trademarks that are incorporated in the
 * source code or documentation are not subject to the GNU General Public
 * License and may only be used or replicated with the express permission of
 * Red Hat, Inc.
 *
 * Red Hat Author(s): David Cantrell <dcantrell@redhat.com>
 */

#ifndef PYTIMER_H_INCLUDED
#define PYTIMER_H_INCLUDED

#include <Python.h>
#include <structmember.h>

#include <parted/parted.h>

/* 1:1 function mappings for timer.h in libparted */
PyObject *py_ped_timer_destroy(PyObject *s, PyObject *args);
PyObject *py_ped_timer_new_nested(PyObject *s, PyObject *args);
PyObject *py_ped_timer_destroy_nested(PyObject *s, PyObject *args);
PyObject *py_ped_timer_touch(PyObject *s, PyObject *args);
PyObject *py_ped_timer_reset(PyObject *s, PyObject *args);
PyObject *py_ped_timer_update(PyObject *s, PyObject *args);
PyObject *py_ped_timer_set_state_name(PyObject *s, PyObject *args);

/* _ped.Timer type is the Python equivalent of PedTimer in libparted */
typedef struct {
    PyObject_HEAD

    /* PedTimer members */
    float frac;
    time_t start;
    time_t now;
    time_t predicted_end;
    char *state_name;
    PedTimerHandler *handler;
    void *context;
} _ped_Timer;

static PyMemberDef _ped_Timer_members[] = {
    {NULL}
};

static PyMethodDef _ped_Timer_methods[] = {
    {"destroy", (PyCFunction) py_ped_timer_destroy, METH_VARARGS, NULL},
    {"new_nested", (PyCFunction) py_ped_timer_new_nested, METH_VARARGS, NULL},
    {"destroy_nested", (PyCFunction) py_ped_timer_destroy_nested,
                       METH_VARARGS, NULL},
    {"touch", (PyCFunction) py_ped_timer_touch, METH_VARARGS, NULL},
    {"reset", (PyCFunction) py_ped_timer_reset, METH_VARARGS, NULL},
    {"update", (PyCFunction) py_ped_timer_update, METH_VARARGS, NULL},
    {"set_state_name", (PyCFunction) py_ped_timer_set_state_name,
                       METH_VARARGS, NULL},
    {NULL}
};

void _ped_Timer_dealloc(_ped_Timer *self);
int _ped_Timer_traverse(_ped_Timer *self, visitproc visit, void *arg);
int _ped_Timer_clear(_ped_Timer *self);
int _ped_Timer_init(_ped_Timer *self, PyObject *args, PyObject *kwds);
PyObject *_ped_Timer_get(_ped_Timer *self, void *closure);
int _ped_Timer_set(_ped_Timer *self, PyObject *value, void *closure);

static PyGetSetDef _ped_Timer_getset[] = {
    {"frac", (getter) _ped_Timer_get, (setter) _ped_Timer_set,
             "PedTimer frac", "frac"},
    {"start", (getter) _ped_Timer_get, (setter) _ped_Timer_set,
              "PedTimer.start", "start"},
    {"now", (getter) _ped_Timer_get, (setter) _ped_Timer_set,
            "PedTimer.now", "now"},
    {"predicted_end", (getter) _ped_Timer_get, (setter) _ped_Timer_set,
                      "PedTimer.predicted_end", "predicted_end"},
    {"state_name", (getter) _ped_Timer_get, (setter) _ped_Timer_set,
                   "PedTimer.state_name", "state_name"},
    {NULL}  /* Sentinel */
};

extern PyTypeObject _ped_Timer_Type_obj;

#endif /* PYTIMER_H_INCLUDED */

/* vim:tw=78:ts=4:et:sw=4
 */
