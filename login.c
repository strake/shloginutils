#include <memory.h>
#include <unistd.h>
#include <stdio.h>
#include <err.h>
#include "go.h"

void main (int argc, char *argu[]) {
	char *pass;
	int ii;
	for (ii = 1; ii < argc; ii++) {
		if (argu[ii][0] != '-' || argu[ii][1] == 0) break;
		if (argu[ii][1] == '-' && argu[ii][2] == 0) {
			ii++;
			break;
		}
	}
	
	if (ii >= argc) errx (1, "no name given");
	
	pass = getpass ("Password: ");
	if (authorize (argu[ii], pass) == 0) {
		memset (pass, 0, strlen (pass));
		go (argu[ii], GoChdirHome, 0);
	}
	fputs ("Denied\n", stdout);
	errx (1, "authorization failed");
}
