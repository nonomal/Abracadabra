# Abracadabra：用中文表示一切

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

**Abracadabra** 是一个多表加密之小项目，使用汉字作为密文，支持自定义密文映射和关键词映射，基于 C++ 17。未来会增加更多语言的实现。

Abracadabra 是表演魔术 (施魔法) 时所念的咒语。

## 特性

- 方便，密文可以描述自身是否被加密以及其类型。
- 无序，加密的文本如咒语般不可阅读。
- 安心，密码表中已剔除敏感汉字。
- 快速，C++ 快如闪电。

## 快速使用

前往 Release 页面下载构建，使用命令行调用程序。
使用参数 `-h` 查看命令帮助。

### ⌨️ CLI 使用须知

```shell
PS C:\Abracadabra>.\abracadabra
*** Abracadabra v0.1, by SheepChef ***
Usage:
      abracadabra [arg] [input]
input   : a string to process
Arguments :
 -l     : Force to encrypt using url mode
 -b     : Force to encrypt using base64 mode
 -n     : Force to encrypt the input directly
 -d     : Force to decrypt the given input
 -h     : Print help information
Tips :
      Usually, the mapped string could tell if itself was mapped and what type itself is.

      Using base64 to process your string could provide the highest compatibility,
      but may lose efficiency if your input had no non-English characters.

      If you are processing links, use link mode could increase the effciency,
      since some common phrases were directly mapped to single characters.
```

强制使用 base64 模式 `-b` 处理字符串可以提供最高的兼容性、但如果输入中没有宽字符，则可能显著降低效率。

如果要处理链接，使用链接模式 `-l` 可以提高效率、因为一些常用短语可以直接加密为单个字符。

如果不附带模式参数 (仅提供文本)，则会自动判断给定的文本是否是密文，依照判断进行处理。不会自动检测给定文本是否是链接，链接模式需要手动指定。如果给定的字符串不存在宽字符，则不会用 base64 预处理字符串，提高效率。

## 注意

Abracadabra 还在积极开发中，这里是一些注意事项。

### 平台兼容性

由于 Abracadabra 的功能涉及中文的输入和输出，在不同平台上，对不同编码的支持各不相同。

项目仅在 Windows 平台上通过了测试，由于使用了 MS 独有的接口以确保命令行输入输出编码的一致性，目前不兼容 Linux 平台。

### 编译

如果你想自行编译 Abracadabra，请确保正确添加了以下依赖库：

- [nlohmann/json](https://github.com/nlohmann/json)
- [cppcodec](https://github.com/tplgy/cppcodec)

请在 Windows x64 环境下用 MinGW 编译，其他环境尚未测试。

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
