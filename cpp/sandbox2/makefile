OUTFILEWIN=sbox.exe
OUTFILELIN=sbox

ifeq ($(OS),Windows_NT)
  # Windows stuff
  OUTFILE=$(OUTFILEWIN)
  OSDIR=src/windows
else
  # Linux stuff
  OUTFILE=$(OUTFILELIN)
  OSDIR=src/linux
endif

CPPSRCS=    \
  main.cpp  \
  file1.cpp \
  file2.cpp \

CSRCS=  \

SRCS=$(CPPSRCS) $(CSRCS)

MAKE=make
RM=rm
MKDIR=mkdir
RMDIR=rmdir

#OBJDIR=.
OBJDIR=obj
BINDIR=bin
DEPDIR=dep
SRCDIR=src

CFLAGS=-c -g -I "$(OSDIR)"
LFLAGS=-g 
    
CPPOBJS=$(CPPSRCS:.cpp=.o)
COBJS=$(CSRCS:.c=.o)
OBJS= $(CPPOBJS) $(COBJS)
OBJSDIR=$(addprefix $(OBJDIR)/,$(notdir $(OBJS)))
DEPFILES=$(addprefix $(DEPDIR)/,$(OBJS:.o=.d))
 
COMPILE=g++ $(CFLAGS) -o "$(OBJDIR)/$(@F)" "$<"
LINK=g++ $(LFLAGS) -o "$(OUTFILE)" $(OBJSDIR)

VPATH = $(OBJDIR) $(DEPDIR) $(SRCDIR) $(OSDIR)

all: $(OUTFILE)

# pull in dependency info for *existing* .o files
-include $(DEPFILES)

%.o : %.c
	@echo "compiling $<"
	$(COMPILE)
	gcc -MM $(CFLAGS) $< > $(DEPDIR)/$*.d

%.o : %.cpp
	@echo "compiling $<"
	$(COMPILE)
	g++ -MM $(CFLAGS) $< > $(DEPDIR)/$*.d

$(OUTFILE): $(OBJDIR) $(DEPDIR) $(OBJS)
	@echo "linking $<"
	$(LINK)

$(OBJDIR):
	@echo "making directory : $(OBJDIR)"
	$(MKDIR) -p "$(OBJDIR)"

$(DEPDIR):
	@echo "making directory : $(DEPDIR)"
	$(MKDIR) -p "$(DEPDIR)"

clean:
	$(RM) -f $(OUTFILELIN)
	$(RM) -f $(OUTFILEWIN)
	$(RM) -f $(OBJDIR)/*.*
	$(RM) -f $(DEPDIR)/*.*
	$(RMDIR) $(DEPDIR)
	$(RMDIR) $(OBJDIR)

test:
	@echo "COBJS:   " $(COBJS)
	@echo "CPPOBJS: " $(CPPOBJS)
	@echo "OBJS:    " $(OBJS)
	@echo "SRCS:    " $(SRCS)
	@echo "CFLAGS:  " $(CFLAGS)

