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

#include "access.h"
#include <sys/syscall.h>
#include <sys/ptrace.h>
#include <fcntl.h>
#include <string.h>

int fileAccess(PyObject *files, const char *file, long flags) {
    PyObject *perm_obj;
    long perm;

    if ((perm_obj = PyDict_GetItemString(files, file)) == NULL) {
        return 0;
    }
    //printf("%s:%d\n",file,flags);
    perm = PyInt_AsLong(perm_obj);
    if (perm == flags)
        return 1;

    return 0;
}

static long file_temp[100];
int checkAccess(struct Runobj *runobj, int pid, struct user_regs_struct *regs) {
#if __WORDSIZE == 64
    if (!runobj->inttable[regs->orig_rax])
#else
        if (!runobj->inttable[regs->orig_eax])
#endif
        return ACCESS_CALL_ERR;

#if __WORDSIZE == 64
    switch (regs->orig_rax)
#else
    switch (regs->orig_eax)
#endif
    {
        case SYS_open: {
            int i, j;

            for (i = 0; i < 100; i++) {
#if __WORDSIZE == 64
                long t = ptrace(PTRACE_PEEKDATA, pid,
                        regs->rdi + i * sizeof(long), NULL);
#else
                long t = ptrace(PTRACE_PEEKDATA, pid, regs->ebx + i*sizeof(long), NULL);
#endif
                file_temp[i] = t;
                const char* test = (const char*) &file_temp[i];
                for (j = 0; j < sizeof(long); j++) {
                    if (!test[j]) {
                        goto l_cont;
                    }
                }
            }
            l_cont: file_temp[99] = 0;

#if __WORDSIZE == 64
            if (fileAccess(runobj->files, (const char *) file_temp, regs->rsi))
#else
                if(fileAccess(runobj->files, (const char *)file_temp, regs->ecx))
#endif
                return ACCESS_OK;
            return ACCESS_FILE_ERR;
        }
    }

    return ACCESS_OK;
}

const char* lastFileAccess(void) {
    file_temp[99] = 0;
    return (const char*) file_temp;
}
