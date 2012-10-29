enum {
	GoKeepEnviron = 1,
	GoFork        = 2,
	GoSetSID      = 4,
};

extern void go (const char *name, int flags, char *argu[]);
