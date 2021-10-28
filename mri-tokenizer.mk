mri-tokenizer.$(OBJEXT): parse.c

# Build process is similar to miniruby with the following changes:
# 1. parse.o is excluded from linking (but parse.c is still generated)
# 2. main.o is replaced with mri-tokenizer.o that includes parse.c
# This way we can get access to all structs and functions defined in parse.c in our mri-tokenizer.c
mri-tokenizer$(EXEEXT): config.status mri-tokenizer.$(OBJEXT) objs $(ARCHFILE)
	$(ECHO) linking $@
	$(CC) $(EXE_LDFLAGS) $(XLDFLAGS) mri-tokenizer.$(OBJEXT) $(MINIOBJS) $(filter-out parse.$(OBJEXT),$(COMMONOBJS)) $(MAINLIBS) $(LIBS) $(OUTFLAG)$@
