OUTFILE=svg.exe

CSRCS=                 \
	main.cpp       \
	xml.cpp        \
	utility.cpp    \
	svgDwg.cpp     \
	svgBase.cpp    \
	svgRect.cpp    \
	svgLine.cpp    \
	svgEllipse.cpp \
	svgText.cpp    \
	svgGroup.cpp   \

COMPILER=g++
LINKER=g++
       
CFLAGS=-c -g
LFLAGS=-g 
DFLAGS=-MM

MAKE=make
RM=rm
MKDIR=mkdir
RMDIR=rmdir

OBJDIR=obj
SRCDIR=.
COMMONDIR=../common

OBJS=$(CSRCS:.cpp=.o)

OBJSDIR=$(addprefix $(OBJDIR)/,$(notdir $(OBJS)))
SRCSDIR=$(addprefix $(SRCDIR)/,$(notdir $(CSRCS)))

VPATH=$(SRCDIR):$(OBJDIR):$(COMMONDIR)

all: $(OUTFILE)

.cpp.o:
	@echo "compiling $<"
	$(COMPILER) $(CFLAGS) -o $(OBJDIR)/$@ -I $(COMMONDIR) $<

$(OUTFILE): $(OBJDIR)  $(OBJS)
	@echo "linking $<"
	$(LINKER) $(LFLAGS) -o $@ $(OBJSDIR)

$(OBJDIR):
	@echo "making directory : $(OBJDIR)"
	$(MKDIR) -p "$(OBJDIR)"

clean:
	$(RM) -f $(OUTFILE)
	$(RM) -f $(OBJDIR)/*.*
	$(RMDIR) $(OBJDIR)

test:
	@echo "OBJS : $(OBJS)"
	@echo "CSRCS : $(CSRCS)"

 

