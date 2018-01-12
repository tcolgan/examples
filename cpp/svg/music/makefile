OUTFILE=svg.exe
CSRCS=                 \
	main.cpp       \
	abc.cpp        \
	appStaff.cpp   \
	appTab.cpp     \
	xyzFeature.cpp \
	xyzMelody.cpp  \
	musSymbols.cpp \
	xml.cpp        \
	appUtility.cpp \
	utility.cpp    \
	svgDwg.cpp     \
	svgBase.cpp    \
	svgRect.cpp    \
	svgLine.cpp    \
	svgEllipse.cpp \
	svgText.cpp    \
	svgGroup.cpp   \
	svgPoly.cpp    \

COMPILER=g++
LINKER=g++
       
MAKE=make
RM=rm
MKDIR=mkdir
RMDIR=rmdir

OBJDIR=obj
SRCDIR=src
SVGDIR=../common

OBJS=$(CSRCS:.cpp=.o)

OBJSDIR=$(addprefix $(OBJDIR)/,$(notdir $(OBJS)))
SRCSDIR=$(addprefix $(SRCDIR)/,$(notdir $(CSRCS)))
SVGSDIR=$(addprefix $(SVGDIR)/,$(notdir $(SVGSRCS)))

VPATH=$(SRCDIR):$(OBJDIR):$(SVGDIR)

CFLAGS=-c -g -I $(SRCDIR) -I $(SVGDIR)
LFLAGS=-g 
DFLAGS=-MM


all: $(OUTFILE)

.cpp.o:
	@echo "compiling $<"
	$(COMPILER) $(CFLAGS) -o $(OBJDIR)/$@ $<

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


