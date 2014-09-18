ObjSuf        = o
SrcSuf        = C
LogSuf        = log

ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs)

DEFINES       =

CXX           = g++
CXXFLAGS      = -O -Wall -fPIC $(DEFINES) -Wno-unused-result
CXXFLAGS      += $(ROOTCFLAGS) -I./ -I../../../ -I../../ -I../../../../../IPHCDataFormat

LD            = g++
LDFLAGS       = -g -O -Wall -fPIC -Wl,--no-undefined
LDFLAGS       += $(ROOTLIBS)  -lEG -lTMVA
LDFLAGS       += -l:`pwd`/../../../../IPHCDataFormat/NTFormat/src/libNTuple.so
LDFLAGS       += -l:`pwd`/../../libNTupleAna.so

SOFLAGS       = -shared
LIBS          =

# Uncomment this line if you want to use a script to parse & colorize gcc output
# (You can also export this variable from your bashrc)
GCCPARSER     = 2>&1 | python ~/littleScripts/colorGcc.py

#------------------------------------------------------------------------------
SOURCES       = $(wildcard *.$(SrcSuf))
OBJECTS       = $(SOURCES:.$(SrcSuf)=.$(ObjSuf))
EXECUTABLES   = $(SOURCES:.$(SrcSuf)=)
LOGS          = $(SOURCES:.$(SrcSuf)=.$(LogSuf))
#------------------------------------------------------------------------------
DEFAULT_TARGET = MySelector
#------------------------------------------------------------------------------

all: compile
#all: compile run

compile: $(DEFAULT_TARGET)

run:
	./$(DEFAULT_TARGET) | tee $(DEFAULT_TARGET).$(LogSuf)

#browse:
#       export PLOTS_TO_BROWSE=`ls ../plots/$(shell basename `pwd`)/*.root`; root -l .browse

clean:
	@echo "Cleaning..."
	@echo "rm -f" $(OBJECTS) $(EXECUTABLES) $(LOGS)

#------------------------------------------------------------------------------

#	../.vectorDictionnary_C.so: ../.vectorDictionnary.C
#	cd ..; root -q -l -L .vectorDictionnary.C+

$(DEFAULT_TARGET): $(DEFAULT_TARGET).$(SrcSuf)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $< $(LIBS) $(GCCPARSER)
