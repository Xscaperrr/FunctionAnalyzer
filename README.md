# FunctionAnalyzer  
一个基于Clang Static Analyzer的clang插件。能够将目标文件中所有声明的函数信息输出到文件。  
## 使用  
### 对单个文件使用
```shell script
clang -cc1 -load {path}/FuncDeclPlugin.so -analyze -analyzer-checker=plugin.FuncDeclChecker example.c
```

