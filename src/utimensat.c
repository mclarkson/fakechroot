/*
    libfakechroot -- fake chroot environment
    Copyright (c) 2010 Piotr Roszatycki <dexter@debian.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
*/


#include <config.h>

#ifdef HAVE_UTIMENSAT

#define _ATFILE_SOURCE
#include <sys/time.h>
#include "libfakechroot.h"


wrapper(utimensat, int, (int dirfd, const char * pathname, const struct timespec times [2], int flags))
{
    char *fakechroot_path, fakechroot_buf[FAKECHROOT_PATH_MAX];
    debug("utimeat(%d, \"%s\", &buf, %d)", dirfd, pathname, flags);
    expand_chroot_path(pathname, fakechroot_path, fakechroot_buf);
    return nextcall(utimensat)(dirfd, pathname, times, flags);
}

#endif
