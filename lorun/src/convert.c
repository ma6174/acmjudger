/**
 * Loco program runner core
 * Copyright (C) 2011  Lodevil(Du Jiong)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "convert.h"

int initCalls(PyObject *li, u_char calls[]) {
    PyObject *t;
    Py_ssize_t len, i;

    memset(calls, 0, sizeof(u_char) * CALLS_MAX);

    len = PyList_Size(li);
    for (i = 0; i < len; i++) {
        t = PyList_GetItem(li, i);
        if (PyLong_Check(t))
            RAISE1("calls must be a list of numbers.");
        calls[PyInt_AsLong(t)] = 1;
    }

    return 0;
}

PyObject *genResult(struct Result *rst) {
    PyObject *rst_obj, *j, *t, *m;
    if ((rst_obj = PyDict_New()) == NULL)
        RAISE0("new dict failure");

    j = PyLong_FromLong(rst->judge_result);
    t = PyLong_FromLong(rst->time_used);
    m = PyLong_FromLong(rst->memory_used);

    if (!j || !t || !m)
        RAISE0("set item falure(1)");

    if (PyDict_SetItemString(rst_obj, "result", j)) {
        RAISE0("set item falure");
    }

    if (!rst->judge_result) {
        if (PyDict_SetItemString(rst_obj, "timeused", t)
                || PyDict_SetItemString(rst_obj, "memoryused", m)) {
            RAISE0("set item failure");
        }
    }

    if (rst->re_signum)
        PyDict_SetItemString(rst_obj, "re_signum",
                PyLong_FromLong(rst->re_signum));
    if (rst->re_call != -1)
        PyDict_SetItemString(rst_obj, "re_call", PyLong_FromLong(rst->re_call));
    if (rst->re_file)
        PyDict_SetItemString(rst_obj, "re_file",
                PyString_FromString(rst->re_file));

    return rst_obj;
}

char * const * genRunArgs(PyObject *args_obj) { //generate the argsments for exec*
    PyObject *arg;
    const char **args;
    int len, i;

    if (!PyList_Check(args_obj))
        RAISE0("args must be a list")

    len = PyList_GET_SIZE(args_obj);
    args = (const char**) malloc(sizeof(char*) * (len + 1));

    for (i = 0; i < len; i++) {
        if ((arg = PyList_GetItem(args_obj, i)) == NULL) {
            free(args);
            return NULL;
        }
        args[i] = PyString_AsString(arg);
    }
    args[i] = NULL;

    return (char * const *) args;
}
