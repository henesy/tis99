#include <u.h>
#include <libc.h>
#include <bio.h>

#include "tis100.h"

void
usage(void)
{
	fprint(2, "usage: %s [-f file.s]", argv0);
	exits("usage");
}


// Emulate the imaginary TIS-100 system
void
main(int argc, char *argv[])
{
	char *fname = "/fd/0";

	ARGBEGIN {
	case 'f':
		fname = EARGF(usage());
		break;
	default:
		sysfatal("err: unknown flag '%c'", ARGC());
	} ARGEND



}
