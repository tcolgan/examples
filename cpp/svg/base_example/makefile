OUTFILEWIN=svg.exe
OUTFILELIN=svg

ifeq ($(OS),Windows_NT)
  # Windows stuff
  OUTFILE=$(OUTFILEWIN)
else
  # Linux stuff
  OUTFILE=$(OUTFILELIN)
endif

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
RMDIR=rm -rf

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
	$(RM) -f $(OUTFILEWIN)
	$(RM) -f $(OUTFILELIN)
	$(RM) -f $(OBJDIR)/*.*
	$(RMDIR) $(OBJDIR)

test:
	@echo "OBJS : $(OBJS)"
	@echo "CSRCS : $(CSRCS)"

 

