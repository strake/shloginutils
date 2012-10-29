#include <unistd.h>
#include <stdio.h>
#include "go.h"
#include "util.h"

void main (int argc, char *argu[]) {
	char *pass;
	int ii;
	selfname = argu[0];
	for (ii = 1; ii < argc; ii++) {
		if (argu[ii][0] != '-' || argu[ii][1] == 0) break;
		if (argu[ii][1] == '-' && argu[ii][2] == 0) {
			ii++;
			break;
		}
	}
	
	if (ii >= argc) die (1, "%s: no name given\n", argu[0]);
	
	pass = getpass ("Password: ");
	if (authorize (argu[ii], pass) == 0) {
		memset (pass, 0, strlen (pass));
		go (argu[ii], 0, 0);
	}
	fputs ("Denied\n", stdout);
	die (1, "%s: authorization failed\n", argu[0]);
}
