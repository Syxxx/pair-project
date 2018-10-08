# Github 项目地址

[github](https://github.com/FZU1816K/personal-project/tree/master/Cplusplus/031602431)


# PSP表格

PSP2.1 | 	Personal Software Process Stages |	预估耗时（分钟） |实际耗时（分钟）  
---|---|---|---
 Planning | 	计划 | 10 |4
· Estimate | 	· 估计这个任务需要多少时间 | 10 |4
Development | 开发  | 335| 635
· Analysis | 	· 需求分析 (包括学习新技术)  | 50| 70
· Design Spec | 	· 生成设计文档  | 80|  30
· Design Review | 	· 设计复审| 20| 10
· Coding Standard | 	· 代码规范 (为目前的开发制定合适的规范)  | 15 | 5
·  Design | 	· 具体设计  | 40| 30
· Coding| 	· 具体编码  | 60| 300
· Code Review | 	· 代码复审  |10 | 10
· Test | 	· 测试（自我测试，修改代码，提交修改）  | 60| 180
Reporting| 	报告  | 40| 110
· Test Repor | 	· 测试报告  | 20| 40
· Size Measurement | 	· 计算工作量  | 5| 10
· Postmortem & Process Improvement Plan | 	· 事后总结, 并提出过程改进计划  |15 | 60
    |       | 	合计  | 385| 749

# 解题思路

拿到题目后，我首先联想到的是曾经写过的统计一行里有几个单词的一段程序。那段程序通过逐个获取字符，结合InWord标志位来判定单词个数。

之后结合了单词的判断方法造了如下的流程图



在写了`processChar`函数之后，感觉情况有点过于复杂，而且出现了遗漏。因此将判断合法性的过程与分离单词的过程相分离，成为如下流程图。



联想到python中的高阶函数，我将“读取文件得到字符”的过程和“处理字符”的过程分成两个类，以便修改“处理字符”的方式。如果需要进行对字符的其他操作，便可以提升类`ScanProcesser`为父类，而将`SomeScanProcesser`作为其子类。

整体构思完成之后查询了文件的输入输出操作，在比对了`fstream`和`FILE*`写法的不同之后，我选择`FILE*`方式。因为`fstream`方式所提供的更详细的错误信息在这个解决方案里并不是很有用，`fstream`下的`getc`方法也比较复杂。

# 实现过程

根据上述流程图 得到下面的几个类

## 1. `ArgParse`类

用于解析用户的输入参数并验证其合法性

该类在Main函数中被调用

主要方法：
 
    // 构造时对输入参数处理
    ArgParser(int argc, char* argv[]);
    
    // 获取处理后的文件名
    string getFileName()；
    
    // 用户错误输入时的测试文档
    int helpDoc();

## 2. `Scanner`类

打开文件并逐个获取字符，并向`ScanProcesser`类传递该字符
特别的，在读取到EOF时，该类会额外传递一个EOF

主要方法：
 
    // 构造时从外界获取文件名并打开，得到对应的FILE*指针
    Scanner::Scanner(std::string inFileName, ScanProcesser* inProcesser)
    
    // 逐个读取字符并传递
    int Scanner::scan();



## 3. `ScanProcesser`类

对`Scanner`类传来的每一个字符进行相应的处理，以得到字符数等多个结果数据


主要方法：
 
    // 构造时从外界获取std::map指针
    ScanProcesser(map<string,int> * inStrMap);
    
    // 对一个字符进行处理
    // 统计各数据并将 字符串及其出现次数存入std::Map中
    int processChar(char c);

    // 从std::Map中获取数据并排序，得到前十个字符串
    int processTop10Words();
    


# 改进过程

这次工程中，对程序的改进一部分依旧伴随着代码的实际书写，另一部分则伴随着新多出来的单元测试和性能分析。


在最开始的设计中，`ScanProcesser`类传递字符数等结果给`Scanner`类，再由`Scanner`类传递给主函数，进行输出。在代码复审时发现这样操作和`Scanner`类原本的用意不符合，而且产生了一个不必要的冗余。因此重构各个结构数据到`Scanner`类里。

在写完`ScanProcesser`类并进行单元测试时，便发现代码中存在的bug和冗余，由此进行了一定量的修复和重构。

其后通过对整个程序的单元测试，发现了EOF未处理、中文无法处理等一些问题，并很快的处理了。

而在性能分析之后，发现占比最大的分别是std::string和std::map，发现了自己测试时使用的一句`string str;`没有删除。但是对于std::map暂时没有什么更好的思路。

# 代码说明

    class ScanProcesser{

    private:
        int charNum;
        int wordNum;
        int wordNumTotal;
        int lineNum;
        int inWord;// IN = 1, OUT = 0 标志扫描指针在一个疑似单词串中
        int newLine;// OLD = 1, NEW = 0
                    // 标志此行有无非空白符，即是否为新行
        stringstream* ss; //存储当前找到的可疑单词序列
        const int SPACE = ' ';
        const int LINESYM = '\n';
        const int TAB = '\t';
        const int LINKWORDSYM = '-';
    };

    // 处理单个字符并更新数据
    int ScanProcesser::processChar(char c){
        
        // 存储当前找到的单词
        string nowWord;

        if (c == EOF) {
            if (newLine == OLD)

                // 当文件最后一行有数据时，行数增加1
                lineNum++;
        }
        else {

            // 中文字符不对字符数影响
            if (isascii(c))
                charNum++;
            else {
                c = TAB;
            }
        }

        //遇到换行符时刷新空行标志
        if (c == LINESYM) {
            if (newLine == OLD) {
                newLine = NEW;
                lineNum++;
            }
        }
        else {
            if (newLine == NEW) {
                if (!(c == SPACE || c == TAB))
                    newLine = OLD;
            }
        }
        
        // 遇到分隔符
        if (!(isalnum(c))){
            
            // 在可疑单词序列内，则判断单词合法性，将合法单词存入map
            if (inWord == IN) {
                *ss >> nowWord;
                if (checkWordValid(nowWord)) {
                    map<string, int>::iterator iter;

                    iter = strMap->find(nowWord);

                    if (iter != strMap->end()) {
                        wordNumTotal++;
                        int count = (iter->second) + 1;
                        strMap->erase(iter);
                        strMap->insert(pair<string, int>(nowWord, count));
                    }
                    else {
                        wordNum++;
                        wordNumTotal++;
                        strMap->insert(pair<string, int>(nowWord, 1));
                    }
                }
                inWord = OUT;
                delete ss;
                ss = new stringstream();//刷新ss
            }
            else;
        }
        else if (isalnum(c)){
            if (isalpha(c))
                c = tolower(c);
            if (inWord == IN);
            else{
                // 若不在可疑单词序列内，置标志位为IN
                // 视为进入可疑单词序列
                inWord = IN;
            }
            *ss << c;
        }
        else;
        return 0;
    }



# 心路历程

在看完题目要求的时候，虽然感觉到算法并不是很复杂，但是我感觉需要很多的时间。在投靠了python（误）之后，也已经很长时间没有写这么长的c++代码了，以至于上来甚至出现了语法错误。

和以前写项目，最大的变化是加入了单元测试和流程图。在整理完流程图的第二天，打开工程的时候我就已经有点忘记接下来要写哪些部分的代码了，靠着流程图才想起来。

在写类的同时写单元测试，让我能够方便地对单独的类进行分析测试。原先写这样的工程时，由于主要的类之间具有重要的联系，往往需要改变`Main`函数甚至将一些private部分改为public。完成功能之后，对整体项目的单元测试让我能够很快的对新的改动进行测试，从而确认改动的正确性。

然而单元测试真是想的头破血流。为了大数据下能够正确运行，找出了sicp里仲夏夜之梦的txt来和璟哥进行对拍（PS: 读者不妨也和我对拍一下）。比较困惑如何去构建好的测试用例。