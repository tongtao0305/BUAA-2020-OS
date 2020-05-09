#include "lib.h"

void umain(void)
{
	u_int who = 0x1802, m;

	for (;;) {
		//writef("%x am waiting.....\n", syscall_getenvid());
		m = ipc_recv(&who, 0x1001, 0);
		writef("C got %d from B\n", m);
        ipc_send(0x1001, ++m, 0, 0);
		writef("C send %d to B\n", m);        

		if (m == 5) {
			return;
		}
	}

}
