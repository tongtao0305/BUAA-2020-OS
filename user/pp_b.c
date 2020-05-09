#include "lib.h"

void umain(void)
{
	u_int who = 0x1001, i, j, m = 0;

	for (;;) {
        // b进程先发出m
        writef("B send m = %d\n", m);
	    ipc_send_double(0x800, 0x1802, m, 0, 0);

        // b进程分别从a和c接收m
        i = ipc_recv(&who, 0x800, 0);
        writef("B got %d from %x\n", i, who);
        j = ipc_recv(&who, 0x1802, 0);
        writef("B got %d from %x\n", j, who);

        if ((i == j) && (i == 5)){
            return;
        }

        if ((i == j) && (i == (m + 1))) {
            m = i + 1;
        }
	}

}
