#include "lib.h"

void
umain1(void)
{
	u_int who, i;
    int m;

	for (;;) {
		writef("%x am waiting.....\n", syscall_getenvid());
		i = ipc_recv(&who, 0, 0);
		writef("%x got %d from %x\n", syscall_getenvid(), i, who);

		if (i == m + 1) {
            m++;
        }

		writef("send %d from %x to %x\n", m, syscall_getenvid(), who);        
        ipc_send(who, m, 0, 0);

		if (i == 5) {
			return;
		}
	}

}
