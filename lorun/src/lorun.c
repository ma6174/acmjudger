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

#include "lorun.h"
#include "convert.h"
#include "run.h"
#include "diff.h"


int initRun(struct Runobj *runobj, PyObject *args)
{
    PyObject *config, *args_obj, *trace_obj, *time_obj, *memory_obj;
    PyObject *calls_obj, *runner_obj, *fd_obj;
    
    if (!PyArg_ParseTuple(args, "O", &config))
        RAISE1("initRun parseTuple failure");
    if(!PyDict_Check(config)) RAISE1("argument must be a dict");
    
    if((args_obj = PyDict_GetItemString(config,"args")) == NULL)
        RAISE1("must supply args");
    
    if((runobj->args = genRunArgs(args_obj)) == NULL) return -1;
    
    if((fd_obj = PyDict_GetItemString(config, "fd_in")) == NULL)
        runobj->fd_in = -1;
    else runobj->fd_in = PyLong_AsLong(fd_obj);
    if((fd_obj = PyDict_GetItemString(config, "fd_out")) == NULL)
        runobj->fd_out = -1;
    else runobj->fd_out = PyLong_AsLong(fd_obj);
    if((fd_obj = PyDict_GetItemString(config, "fd_err")) == NULL)
        runobj->fd_err = -1;
    else runobj->fd_err = PyLong_AsLong(fd_obj);
      
    if((time_obj = PyDict_GetItemString(config,"timelimit")) == NULL)
        RAISE1("must supply timelimit");
    runobj->time_limit = PyLong_AsLong(time_obj);
    
    if((memory_obj = PyDict_GetItemString(config,"memorylimit")) == NULL)
        RAISE1("must supply memorylimit");
    runobj->memory_limit = PyLong_AsLong(memory_obj);
    
    if((runner_obj = PyDict_GetItemString(config,"runner")) == NULL)
        runobj->runner = -1;
    else
        runobj->runner = PyLong_AsLong(runner_obj);
    
    if((trace_obj = PyDict_GetItemString(config,"trace")) != NULL){
        if(trace_obj == Py_True){
            runobj->trace = 1;
            //trace mode: supply calls and files to access.
            if((calls_obj = PyDict_GetItemString(config,"calls")) == NULL)
                RAISE1("trace == True, so you must specify calls.");
            if(!PyList_Check(calls_obj))
                RAISE1("calls must be a list.");
            if(initCalls(calls_obj, runobj->inttable)) return -1;
            
            if((runobj->files = PyDict_GetItemString(config,"files")) == NULL)
                RAISE1("trace == True, so you must specify files.");
            if(!PyDict_Check(runobj->files))
                RAISE1("files must be a dcit.");
        } else runobj->trace = 0;
    } else runobj->trace = 0;
    
    return 0;
}

PyObject *run(PyObject *self, PyObject *args)
{
    struct Runobj runobj = {0};
    struct Result rst = {0};
    rst.re_call = -1;
    
    if(initRun(&runobj, args)){
        if(runobj.args)
            free((void*)runobj.args);
        return NULL;
    }
    
    if(runit(&runobj, &rst) == -1)
        return NULL;
    if(runobj.args)
        free((void*)runobj.args);
    
    return genResult(&rst);
}

PyObject* check(PyObject *self, PyObject *args)
{
    int user_fd, right_fd, rst;
    
    if (!PyArg_ParseTuple(args, "ii", &right_fd, &user_fd))
        RAISE0("run parseTuple failure");
    
    if(checkDiff(right_fd, user_fd, &rst) == -1)
        return NULL;
    
    return Py_BuildValue("i", rst);
}

#define run_description "run(argv_dict):\n"\
    "\targv_dict contains:\n"\
    "\t@args : cmd to run\n"\
    "\t@fd_in, fd_out, fd_err : stdin,stdout,stderr fd\n"\
    "\t@timelimit : program time limit\n"\
    "\t@memorylimit : program memory limit\n"\
    "\t@runner : run user\n"\
    "\t@trace : trace?"

#define check_description "check(right_fd, userout_fd)\n"

static PyMethodDef lorunMethods[]={
	{"run", run, METH_VARARGS, run_description},
	{"check", check, METH_VARARGS, check_description},
	{NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC initlorun(void)
{
	(void) Py_InitModule("lorun",lorunMethods);
}
