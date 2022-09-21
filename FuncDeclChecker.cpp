#include "clang/StaticAnalyzer/Core/BugReporter/BugType.h"
#include "clang/StaticAnalyzer/Core/Checker.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CheckerContext.h"
#include "clang/StaticAnalyzer/Frontend/CheckerRegistry.h"
#include <fstream>
#include <iostream>
using namespace std;

using namespace clang;
using namespace ento;

namespace 
{
  class FuncDeclChecker : public Checker<check::ASTDecl<FunctionDecl>> 
  {
    mutable std::unique_ptr<BugType> BT;

  public:
    void checkASTDecl(const FunctionDecl *D,AnalysisManager &Mgr,BugReporter &BR) const;
};
} // end anonymous namespace

void FuncDeclChecker::checkASTDecl(const FunctionDecl *D,AnalysisManager &Mgr,BugReporter &BR) const
{
  auto name=D->getNameInfo().getAsString();
  auto retType = D->getReturnType().getAsString();
  std::string arg0;
  if(D->getNumParams() > 0)
    arg0 = D->parameters()[0]->getQualifiedNameAsString();
  ofstream outfile;
  outfile.open("afile.dat",ios::app);
  outfile<<retType<<' '<<name<<endl;
  outfile.close();
}

extern "C" void clang_registerCheckers(CheckerRegistry &registry) {
  registry.addChecker<FuncDeclChecker>(
      "plugin.FuncDeclChecker", "Output Function Declaration Infomations to file.",
      "");
}

extern "C" const char clang_analyzerAPIVersionString[] =
    CLANG_ANALYZER_API_VERSION_STRING;