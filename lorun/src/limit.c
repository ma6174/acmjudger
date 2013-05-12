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

#include "limit.h"
#include <sys/resource.h>
#include <sys/time.h>

long time_limit, memory_limit;
const char *last_limit_err;

int setResLimit(void) {
#define RAISE_EXIT(err) {last_limit_err = err;return -1;}
    struct rlimit rl;

    rl.rlim_cur = time_limit / 1000 + 2;
    rl.rlim_max = rl.rlim_cur + 1;
    if (setrlimit(RLIMIT_CPU, &rl))
        RAISE_EXIT("set RLIMIT_CPU failure");

    /*rl.rlim_cur = 128 * 1024 * 1024;
     rl.rlim_max = rl.rlim_cur + 1024;
     if (setrlimit(RLIMIT_AS, &rl))
     RAISE_EXIT("set RLIMIT_AS failure");*/

    rl.rlim_cur = 256 * 1024 * 1024;
    rl.rlim_max = rl.rlim_cur + 1024;
    if (setrlimit(RLIMIT_STACK, &rl))
        RAISE_EXIT("set RLIMIT_STACK failure");

    struct itimerval p_realt;
    p_realt.it_interval.tv_sec = time_limit / 1000 + 3;
    p_realt.it_interval.tv_usec = 0;
    p_realt.it_value = p_realt.it_interval;
    if (setitimer(ITIMER_REAL, &p_realt, (struct itimerval *) 0) == -1)
        RAISE_EXIT("set ITIMER_REAL failure");

    return 0;
}
