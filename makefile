WARN = -Wall -Wgen- -Wppt

fixkey.obj: fixkey.c imphook.def
	icc $(WARN) -c -Ss+ -B"/PM:PM" fixkey.c imphook.def

fixkey.exe:	fixkey.obj imphook.def
	icc $(WARN) -B"/PM:PM" fixkey.obj imphook.def
	rc icon.res fixkey.exe

fixhook.obj: fixhook.c fixhook.def
	icc $(WARN) -c -Ss+ -Ge- fixhook.c fixhook.def

fixhook.dll:	fixhook.obj fixhook.def
	icc $(WARN) -Ss+ -Ge- fixhook.obj fixhook.def