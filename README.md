# FunctionAnalyzer  
一个基于Clang Static Analyzer的clang插件。能够将目标文件中所有声明的函数信息输出到文件。
## 编译  
若不想编译,可尝试直接使用Release中的.so文件。  
在clang/lib/Analysis/plugins文件夹下clone该项目,并在该目录下的CMakeList.txt中添加
```cmake  
add_subdirectory(FunctionAnalyzer)
```  
重新编译整个clang后则会在build/lib生成.so文件。  
## 使用  
### 对单个文件使用
```shell script
clang -cc1 -load PATH/FuncDeclPlugin.so -analyze -analyzer-checker=plugin.FuncDeclChecker example.c
//PATH为FuncDeclPlugin.so文件所在目录，若为自行编译则位于build/lib/
//example.c为目标文件
```
### 对项目使用  
对项目使用时首先确保在安装clang时同时安装了scan-build。  
在该项目目录下使用make时改为
```shell script
scan-build -load-plugin PATH/FuncDeclPlugin.so -enable-checker plugin.FuncDeclChecker make
////PATH为FuncDeclPlugin.so文件所在目录，若为自行编译则位于build/lib/
```
## 输出
插件的输出文件位于/tmp/FuncInfo.out  
## 外置分析函数
运行目录下的Analyzer.py即可。
```shell script
python Analyzer.py
```
输出位置为/tmp/AnalysisReport.txt