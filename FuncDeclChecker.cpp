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
    mutable ofstream outfile;
  public:
    FuncDeclChecker();
    ~FuncDeclChecker();
    void checkASTDecl(const FunctionDecl *D,AnalysisManager &Mgr,BugReporter &BR) const;
  };
} // end anonymous namespace
FuncDeclChecker::FuncDeclChecker()
{
  outfile.open("FuncInfo.out");
  outfile<<"----begin-----"<<endl;
}
FuncDeclChecker::~FuncDeclChecker()
{
  outfile<<"----end-----"<<endl;
  outfile.close();
}
void FuncDeclChecker::checkASTDecl(const FunctionDecl *D,AnalysisManager &Mgr,BugReporter &BR) const
{
  auto name=D->getNameInfo().getAsString();
  auto retType = D->getReturnType().getAsString();
  string args="";
  if(D->getNumParams() > 0)
    args= D->parameters()[0]->getQualifiedNameAsString();
    for(int i=1;i<D->getNumParams();i++)
      args += " , " + (D->parameters()[i]->getQualifiedNameAsString());
  string out=retType + ' ' +name + '(' +args + ')';
  outfile<<out<<endl;
}

extern "C" void clang_registerCheckers(CheckerRegistry &registry) {
  registry.addChecker<FuncDeclChecker>(
      "plugin.FuncDeclChecker", "Output Function Declaration Infomations to file.",
      "");
}

extern "C" const char clang_analyzerAPIVersionString[] =
    CLANG_ANALYZER_API_VERSION_STRING;