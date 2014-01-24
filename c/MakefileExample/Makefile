.SILENT:

OUTNAME=sandbox

ifdef COMSPEC
OUTNAME:=$(OUTNAME).exe
endif

CC=g++
LD=g++

RM=rm -f
RMDIR=rmdir

CSRCS =   \
  file1.c \
  file2.c \
  main.c  \

INCLUDES=  \
  src      \
  src/dir1 \
  src/dir2 \

VPATH=     \
  src      \
  src/dir1 \
  src/dir2 \

INCLUDEFLAGS=$(addprefix -I,$(INCLUDES))

DEBUG=-g
CFLAGS=-c $(DEBUG) -Wall $(INCLUDEFLAGS)
LINKFLAGS=$(DEBUG) -Wall

OBJDIR=obj
BINDIR=bin
DEPDIR=dep
DIRS=$(OBJDIR) $(BINDIR) $(DEPDIR)

OUTFILE=$(BINDIR)/$(OUTNAME)

OBJECTS=$(addprefix $(OBJDIR)/,$(subst .c,.o,$(CSRCS)))  
DEPENDS=$(addprefix $(DEPDIR)/,$(subst .c,.d,$(CSRCS)))

all: $(OUTFILE)

$(OUTFILE): $(OBJECTS) | $(BINDIR)
	echo "linking: $@ from $^"
	$(LD)  $(LINKFLAGS) -o $@ $^

-include $(DEPENDS)

$(OBJDIR)/%.o: %.c | $(OBJDIR) $(DEPDIR)
	echo "compiling: "$<
	$(CC)  $(CFLAGS) $< -o $@
	$(CC) -MM -MT $@ $(CFLAGS) $< > $(DEPDIR)/$*.d

$(DIRS):
	echo "making directory: "$@
	mkdir -p $@

debug:
	echo CSRCS=$(CSRCS)
	echo OBJECTS=$(OBJECTS)
	echo OUTFILE=$(OUTFILE)
	echo INCLUDEFLAGS=$(INCLUDEFLAGS)
	echo DEPENDS=$(DEPENDS)
	echo OS=$(OS)

clean:
	-$(RM) $(DEPDIR)/*.d  2>/dev/null
	-$(RM) $(OBJDIR)/*.o  2>/dev/null
	-$(RM) $(OUTFILE)     2>/dev/null
	-$(RMDIR) $(DEPDIR)   2>/dev/null
	-$(RMDIR) $(OBJDIR)   2>/dev/null
	-$(RMDIR) $(BINDIR)   2>/dev/null

.PHONY: all clean debug


