/*
 * Copyright (C) 2015 - Florent Revest <revestflo@gmail.com>
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

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <linux/fb.h>
#include <assert.h>

// TODO: We should be able to specify which framebuffer must be used and at which frequency the loop should be executed

int main(int argc, char *argv[])
{
    struct fb_var_screeninfo var;
    int fd = open("/dev/fb0", O_RDWR);
  
    setpriority(PRIO_PROCESS, 0, -20);
    assert(fd >= 0);

    if(argc > 1 && !strcmp(argv[1], "--loop"))
    {
        while(ioctl(fd, FBIOPAN_DISPLAY, &var) >= 0)
            usleep(16666);
        perror("Failed FBIOPAN_DISPLAY");
        return 1;
    }
    else if(ioctl(fd, FBIOPAN_DISPLAY, &var) < 0)
    {
        perror("Failed FBIOPAN_DISPLAY");
        return 1;
    }
    return 0;
}
