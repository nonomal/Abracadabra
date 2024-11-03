# Abracadabra：用中文表示一切

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

**Abracadabra** 是一个多表加密之小项目，使用汉字作为密文，支持自定义密文映射和关键词映射，基于 C++ 11。未来会增加更多语言的实现。

Abracadabra 是表演魔术 (施魔法) 时所念的咒语。

设计它的初衷，是为了在中文互联网上公开合理地传输不安全的信息。

**在线体验**: [**Web DEMO Page**](https://sheepchef.github.io/Abracadabra/)

**查阅 Web 实现**: [**dev_node Branch**](https://github.com/SheepChef/Abracadabra/tree/dev_nodejs)

## 特性

![动画](https://github.com/user-attachments/assets/7ec6e01c-230d-4d27-a0b1-80015307c5f4)

- 方便，密文可以描述自身。
- 随机，加密结果具有随机性。
- 无序，加密的文本如咒语般不可阅读。
- 安心，密码表中已剔除敏感汉字。

## 快速使用

前往 Release 页面下载构建，使用命令行调用程序。
使用参数 `-h` 查看命令帮助。

### ⌨️ CLI 使用须知

```shell
PS C:\Abracadabra> .\abracadabra.exe -h
***Abracadabra v0.2 , by SheepChef***
Usage: G:\Code-projects\Abracadabra\abracadabra.exe [OPTIONS] [DEFAULT]

Positionals:
  DEFAULT TEXT Excludes: -l -b -n -d -f -o -i
                              Input text, if there is no given option besides.

Options:
  -h,--help                   Print this help message and exit
  -l Excludes: DEFAULT -b -n -d
                              Force to encrypt using url mode
  -b Excludes: DEFAULT -l -n -d
                              Force to encrypt using base64 mode
  -n Excludes: DEFAULT -l -b -d
                              Force to encrypt the input directly
  -d Excludes: DEFAULT -l -b -n
                              Force to decrypt the given input
  -f TEXT Excludes: DEFAULT -i
                              Input an arbitrary given file.
  -o TEXT Excludes: DEFAULT   Declare an output file to save the result.
  -i TEXT Excludes: DEFAULT -f
                              Input text, expected if -f is not used.
```

程序的输入和输出分离，输入可以是 `-i` 后跟一串字符串，也可以是 `-f` 后指定任意文件。 默认情况下结果输出在控制台，也可以 `-o` 后指定一个输出文件。

**理论上本程序可以处理任何文件，但不建议尝试处理大小超过 100kb 以上的文件，处理大文件的速度很慢，且对大部分文件强制使用 Base64 模式。** 如果指定文件仅包括英文字母，数字和部分符号，那么你可以指定处理方式。文件加密的处理依赖标志位，去除标志位可能导致文件无法解密。

使用 base64 模式 `-b` 处理字符串可以提供最高的兼容性、但如果输入中没有宽字符，则可能显著降低效率。

如果要处理链接，使用链接模式 `-l` 可以提高效率、因为一些常用短语可以直接加密为单个字符。不会自动检测给定文本是否是链接，链接模式需要手动指定。

如果不附带任何模式参数 (仅提供文本)，则会自动判断给定的文本是否是密文，依照判断进行处理。

如果给定的字符串不存在宽字符，则不会用 base64 预处理字符串，提高效率。

## 注意

Abracadabra 还在积极开发中，这里是一些注意事项。

### 平台兼容性

由于 Abracadabra 的功能涉及中文的输入和输出，在不同平台上，对不同编码的支持各不相同。

项目在 Windows 11 和 Ubuntu 22.04 LTS 上通过了编译测试。

在嵌入式平台(armv7a, armv8a)上通过了运行测试。

### 已知问题

#### 处理文件耗时指数级增加

C++ JSON 解析库或多或少存在性能问题，特别是在执行大量枚举时。

本项目之目的并不是将文件转换为上百万个汉字，故搁置该问题。

小于 100kb 的文件均能在可控时间内得到处理。大文件用 Node.js 处理更加高效，但解密可能导致浏览器卡死。

该问题将在未来积极解决。

#### 密本随机性不足

密本亟待扩充，后续会增加汉字映射。

已有的映射不会删减，只会在此基础上增加，以确保未来版本的向下兼容性。

### 依赖

如果你想自行编译 Abracadabra，请确保正确添加了以下依赖库：

- [nlohmann/json](https://github.com/nlohmann/json)
- [cppcodec](https://github.com/tplgy/cppcodec)
- [CLI11](https://github.com/CLIUtils/CLI11)

另外，请确保您的环境中安装了 C++11 标准库。

本项目并不复杂，推荐直接用指令调用 g++ 进行构建。如果您愿意，也可以尝试 CMake。

## 细节

### 加密实现

Abracadabra 使用古老的多表加密，以最常用的 500 个汉字(剔除了可能随机组成敏感词的汉字)为密本，对大小写拉丁字母，阿拉伯数字和部分符号进行映射。

大写字母的映射方式为在小写字母前添加一个汉字的标志位，元音字母有更多的映射可能。

### 标志位

使用 日本和制汉字 与 部分生僻字 组成二字标志位，用于标记密文的类型。

和制汉字和选定的生僻字，在正常情况下不可能同时出现，杜绝类型判断错误的问题。

### 密码表

密码表公开可见，你可以自行修改密码表，编译出属于你自己的 Abracadabra。

### 灵感

Abracadabra 的灵感来源于网络上曾流行过的熊曰加密。

## Todo

- [x] ~~实现更规范地解析命令参数~~
- [x] ~~实现加密任意文件，输出文本文档~~
- [ ] 用 Python 完整实现 Abracadabra 的轮子
- [x] ~~用 Node.js 完整实现 Abracadabra 的轮子~~
- [ ] 实现让嵌入自定义密本更具灵活性
