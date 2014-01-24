OUTFILE=maketest.exe
CSRCS=   \
  src/main.c \
  src/util.c \

MAKE=make
RM=rm
MKDIR=mkdir
RMDIR=rmdir

OBJDIR=obj
BINDIR=bin

CFLAGS=-c -g
LFLAGS=-g 
       
OBJS=$(CSRCS:.c=.o)
OBJSDIR=$(addprefix $(OBJDIR)/,$(notdir $(OBJS)))
 
COMPILE=gcc $(CFLAGS) -o "$(OBJDIR)/$(@F)" "$<"
LINK=gcc $(LFLAGS) -o "$(OUTFILE)" $(OBJSDIR)

all: $(OUTFILE)

%.o : %.c
	@echo "compiling $<"
	$(COMPILE)

$(OUTFILE): $(OBJDIR)  $(OBJS)
	@echo "linking $<"
	$(LINK)

$(OBJDIR):
	@echo "making directory : $(OBJDIR)"
	$(MKDIR) -p "$(OBJDIR)"

clean:
	$(RM) -f $(OUTFILE)
	$(RM) -f $(OBJDIR)/*.*
	$(RMDIR) $(OBJDIR)

test:
	@echo "OBJS : $(OBJS)"
	@echo "OBJSDIR : $(OBJSDIR)"
	@echo "CSRCS : $(CSRCS)"
	@echo "OBJDIR : $(OBJDIR)"

