#include <shadow.h>
#include <string.h>
#include <stdio.h>
#include <err.h>
#include "auth.h"

/* return 0 iff user authorized
 * pass argument in the clear
 */
int authorize (const char *name, const char *pass) {
	struct spwd *shp;
	char *x; /* password hash */

	shp = getspnam (name);
	if (!shp) {
		warnx ("failed to find password");
		return 1;
	}
	
	switch (shp -> sp_pwdp[0]) {
	case '!': return 1;
	case '$': break;
	default : warnx ("bad password format");
	          return 1;
	}
	x = crypt (pass, shp -> sp_pwdp);
	if (!x) {
		warnx ("failed to compute password hash");
		return 1;
	}
	
	return (strcmp (x, shp -> sp_pwdp));
}
