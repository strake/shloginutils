enum {
	GoKeepEnviron = 1,
	GoFork        = 2,
	GoSetSID      = 4,
	GoChdirHome   = 8,
	GoSearchPath  = 16,
};

extern void go (const char *name, int flags, char *argu[]);
