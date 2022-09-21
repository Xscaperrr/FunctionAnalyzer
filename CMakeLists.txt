set(LLVM_LINK_COMPONENTS
  Support
  )

set(LLVM_EXPORTED_SYMBOL_FILE ${CMAKE_CURRENT_SOURCE_DIR}/FuncDeclPlugin.exports)
add_llvm_library(FuncDeclPlugin MODULE BUILDTREE_ONLY FuncDeclChecker.cpp)

clang_target_link_libraries(FuncDeclPlugin PRIVATE
  clangAnalysis
  clangAST
  clangStaticAnalyzerCore
  clangStaticAnalyzerFrontend
  )