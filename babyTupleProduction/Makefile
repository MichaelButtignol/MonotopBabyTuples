# Extensions configuration
ObjSuf        = o
SrcSuf        = C
ExeSuf        = run
LogSuf        = log

# IPHC paths

IPHCDATAFORMAT_NTUPLE = `pwd`/../../../../../IPHCDataFormat/
IPHCANALYSIS_NTUPLE   = `pwd`/../../../

# Root flags

ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs) 

# Compiler
CXX           = g++

# Compiler options
CXXFLAGS      = -std=c++0x 
CXXFLAGS      = -g -O -Wall -fPIC -Wno-unused-result -Wl,--no-undefined 

# Include paths
INCLUDES       = $(ROOTCFLAGS) 
INCLUDES      += -I ./
INCLUDES      += -I ./../
INCLUDES      += -I ../../
INCLUDES      += -I ../../../
INCLUDES      += -I ../../../../
INCLUDES      += -I $(IPHCDATAFORMAT_NTUPLE)/

# Linker options
LDFLAGS       += $(ROOTLIBS) -lEG -lTMVA -lProof -lProofPlayer -lMinuit -lMinuit2
LDFLAGS       += -l:$(IPHCDATAFORMAT_NTUPLE)/NTFormat/src/libNTuple.so
LDFLAGS       += -l:`pwd`/libNTupleAna.so
LDFLAGS       += -l:`pwd`/../../../LHAPDF/lib/libLHAPDF.so.0

# Uncomment this line if you want to use a script to parse & colorize gcc output
# (You can also export this variable from your bashrc)
GCCPARSER     = 2>&1 | python ~/littleScripts/colorGcc.py -o

# Filter the useless PROOF output
PROOFFILTER = 2>&1 | tr '\r' '\n' | grep -v --line-buffered "Opening connections\|Setting up worker servers\|Info in <\|no dictionary for\|TUnixSystem::DynamicPathName\|TDataSetManager::ScanDataSet\|exact location of files\|Validating files\|Output file:\|set to parallel mode\|Starting PROOF-Lite\|merging output objects\|objects have been merged\|still sending\|0.00 %" | perl -e '$$| = 1 ;' -pe 's|MB/s]\n|MB/s]\x0D|g;' 

#------------------------------------------------------------------------------
SOURCES       = $(wildcard *.$(SrcSuf))
OBJECTS       = $(SOURCES:.$(SrcSuf)=.$(ObjSuf))
EXECUTABLES   = $(SOURCES:.$(SrcSuf)=.$(ExeSuf))
LOGS          = $(SOURCES:.$(SrcSuf)=.$(LogSuf))
ROOTMESS1     = $(wildcard *.d)
ROOTMESS2     = $(wildcard *.so)
#------------------------------------------------------------------------------
PROOF_LAUNCHER = ProofLauncher
PROOF_JOB = ProofJob
PROOF_FORMAT = ProofFormat
#------------------------------------------------------------------------------

help:
	@echo "Specify a target :"
	@echo "  - job      : compiles your PROOF job description"
	@echo "  - prod     : launch your job on multiple workers"
	@echo "  - moveProd : derp"
	
job: $(PROOF_JOB)_C.so

prod: job  $(PROOF_LAUNCHER).$(ExeSuf)
	@./$(PROOF_LAUNCHER).$(ExeSuf) $(PROOFFILTER) | tee $(PROOF_LAUNCHER).$(LogSuf)

clean:
	@echo "Cleaning..."
	@rm -rf $(OBJECTS) $(EXECUTABLES) $(LOGS) $(ROOTMESS1) $(ROOTMESS2) backup_outputProof* NTAna

#------------------------------------------------------------------------------

copyLibAna:
	@cp $(IPHCANALYSIS_NTUPLE)/libNTupleAna.so ./libNTupleAna.so

$(PROOF_JOB)_C.so: copyLibAna $(PROOF_FORMAT).h
	@echo "Compiling job description..."
	@$(CXX) $(CXXFLAGS) $(INCLUDES) $(LDFLAGS) -o .makeJob.run .makeJob.C
	@export IPHCDATAFORMAT_NTUPLE=$(IPHCDATAFORMAT_NTUPLE); export IPHCANALYSIS_NTUPLE=$(IPHCANALYSIS_NTUPLE); ./.makeJob.run $(GCCPARSER)

%.$(ExeSuf): %.$(SrcSuf)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LDFLAGS) -o $@ $< $(GCCPARSER)


