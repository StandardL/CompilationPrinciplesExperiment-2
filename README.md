# 编译原理课程实验2 - Xlex词法生成器

## 实验要求：

### 必做：

1. 正则表达式应该支持单个字符，运算符号有： 连接、选择（|）、闭包（*）、括号（）、可选（?  ）
2. 要提供一个源程序编辑界面，让用户输入一行（一个）或多行（多个）正则表达式（可保存、打开正则表达式文件）
3. 需要提供窗口以便用户可以查看转换得到的NFA（用状态转换表呈现即可）
4. 需要提供窗口以便用户可以查看转换得到的DFA（用状态转换表呈现即可）
5. 需要提供窗口以便用户可以查看转换得到的最小化DFA（用状态转换表呈现即可）
6. 需要提供窗口以便用户可以查看转换得到的词法分析程序（该分析程序需要用C/C++语言描述）
7. 用户界面应该是windows界面
8. 应该书写完善的软件文档

### 选做：
1. 扩充正则表达式的运算符号，如   [ ] 、 正闭包（+） 等。

## 💻程序

### 截图

![image-20231028104916620](https://github.com/StandardL/CompilationPrinciplesExperiment-2/raw/main/images/%E7%A8%8B%E5%BA%8F%E4%B8%BB%E7%95%8C%E9%9D%A2.png)

### 支持处理的正则表达式运算符

连接（^），选择（|），闭包（*），括号（ () ），可选（?）

### 🧪测试数据

共使用6组测试数据，具体请参见[Test instance文件夹](https://github.com/StandardL/CompilationPrinciplesExperiment-2/tree/main/src/Test%20instances).

## 🧭编译

### 环境要求

#### Qt 6.2.4

- Qt Design Studio 4.2.0
- Qt 6.2.4
  - MSVC 2019 64-bit
  - MinGW 11.2.0 64-bit
  - Qt 5 Compatibility Module
  - Qt Shader Tools
  - Additional Libraries
- Developer and Designer Tools
  - Qt Creator 11.0.2
  - Qt Creator 11.0.2 CDB Debugger Support
  - Debugging Tools for Windows
  - MinGW 11.2.0 64-bit
  - Qt Installer Framwork 4.6
  - CMake 3.24.2
  - Ninja 1.10.2

## ☁未来展望

- [ ] QT界面美化
- [ ] UnitTest
  
## 🔗其他链接

- [Console(CLI)版本](https://github.com/StandardL/ComplieExp2-Console)
- [更多测试数据](https://blog.csdn.net/weixin_50094312/article/details/127581508?spm=1001.2101.3001.6650.5&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-5-127581508-blog-130661267.235%5Ev38%5Epc_relevant_anti_vip_base&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7ERate-5-127581508-blog-130661267.235%5Ev38%5Epc_relevant_anti_vip_base&utm_relevant_index=10)
- [HarmonyOS鸿蒙字体](https://developer.harmonyos.com/cn/design/resource)
