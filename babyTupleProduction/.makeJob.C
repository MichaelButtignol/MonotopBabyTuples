
#include "ProofLauncher.h"
#include "TSelector.h"

//
// Stupid ROOT wants to compile shit its own way,
// so I'm compiling an other C program that in turn 
// call ROOT compiler, so PROOF doesn't have to call it
// when it starts, so that I can parse the errors properly.
// Good job ROOT for reinventing C++ with your rubbish.
//

int main(int argc, char* argv[])
{
  gSystem->AddIncludePath("-I./");
  gSystem->AddIncludePath("-I../");
  gSystem->AddIncludePath("-I../../");
  gSystem->AddIncludePath("-I../../../");
  gSystem->AddIncludePath("-I../../../../");
  gSystem->AddIncludePath("-I../../../../../IPHCDataFormat/");
  TSelector* macro = TSelector::GetSelector(MACRO_NAME);
  return (0);
}


