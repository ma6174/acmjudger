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

#include "diff.h"
#include <sys/mman.h>

int equalStr(const char *s, const char *s2) {
    const char *c1 = s, *c2 = s2;
    while (*c1 && c2 && (*c1++ == *c2++))
        ;
    if ((*c1 | *c2) == 0)
        return 1;
    return 0;
}

#define RETURN(rst) {*result = rst;return 0;}
int checkDiff(int rightout_fd, int userout_fd, int *result) {
    char *userout, *rightout;

    off_t userout_len, rightout_len;
    userout_len = lseek(userout_fd, 0, SEEK_END);
    rightout_len = lseek(rightout_fd, 0, SEEK_END);

    if (userout_len == -1 || rightout_len == -1)
        RAISE1("lseek failure");

    if (userout_len >= MAX_OUTPUT)
        RETURN(OLE);

    lseek(userout_fd, 0, SEEK_SET);
    lseek(rightout_fd, 0, SEEK_SET);

    if ((userout_len && rightout_len) == 0) {
        if (userout_len || rightout_len)
            RETURN(WA)
        else
            RETURN(AC)
    }

    if ((userout = (char*) mmap(NULL, userout_len, PROT_READ | PROT_WRITE,
            MAP_PRIVATE, userout_fd, 0)) == MAP_FAILED) {
        RAISE1("mmap userout filure");
    }

    if ((rightout = (char*) mmap(NULL, rightout_len, PROT_READ | PROT_WRITE,
            MAP_PRIVATE, rightout_fd, 0)) == MAP_FAILED) {
        munmap(userout, userout_len);
        RAISE1("mmap right filure");
    }

    if ((userout_len == rightout_len) && equalStr(userout, rightout)) {
        munmap(userout, userout_len);
        munmap(rightout, rightout_len);
        RETURN(AC);
    }

    const char *cuser = userout, *cright = rightout;
    const char *end_user = userout + userout_len;
    const char *end_right = rightout + rightout_len;
    while ((cuser < end_user) && (cright < end_right)) {
        while ((cuser < end_user)
                && (*cuser == ' ' || *cuser == '\n' || *cuser == '\r'
                        || *cuser == '\t'))
            cuser++;
        while ((cright < end_right)
                && (*cright == ' ' || *cright == '\n' || *cright == '\r'
                        || *cright == '\t'))
            cright++;
        if (cuser == end_user || cright == end_right)
            break;
        if (*cuser != *cright)
            break;
        cuser++;
        cright++;
    }
    while ((cuser < end_user)
            && (*cuser == ' ' || *cuser == '\n' || *cuser == '\r'
                    || *cuser == '\t'))
        cuser++;
    while ((cright < end_right)
            && (*cright == ' ' || *cright == '\n' || *cright == '\r'
                    || *cright == '\t'))
        cright++;
    if (cuser == end_user && cright == end_right) {
        munmap(userout, userout_len);
        munmap(rightout, rightout_len);
        RETURN(PE);
    }

    munmap(userout, userout_len);
    munmap(rightout, rightout_len);
    RETURN(WA);
}

