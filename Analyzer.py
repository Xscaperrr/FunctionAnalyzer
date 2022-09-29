import re

Auth=(["login","auth"],"认证类函数") 
Memprc=(["memcpy","malloc"],"内存处理函数")
Crypto=(["aes","des","rsa","md5","sha-256"],"密码学函数")
Strings=(["str","split"],"字符串类函数")
Files=(["fopen","fclose","fprint","fseek","file"],"文件类函数")
Coding=(["encode","decode"],"编码类函数")
Audio=(["audio","mp3","voice"],"音频函数")
AllType=[Auth,Memprc,Crypto,Strings,Files,Coding,Audio]
with open("/tmp/FuncInfo.out",mode='r') as f,open("/tmp/AnalysisReport.txt",mode='w') as out:
    line=f.readline()#begin行
    line=f.readline()
    while line !="----end-----\n"and line !="":
        FuncName=re.findall('(\w*)\(',line)[0].lower()
        outstr=[]
        for t in AllType:
            if any(s in FuncName for s in t[0]):outstr.append(t[1])
        if outstr==[]:
            out.write(line)
            print(line)
        else:
            line =line[:-1]+" //"
            for s in outstr:
                line+=s+","
            out.write(line[:-1]+"\n")
            print(line[:-1]+"\n")
 
        line=f.readline()