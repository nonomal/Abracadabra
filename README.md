# Abracadabra：用中文表示一切

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

**Abracadabra** 是一个文本即时加密/脱敏工具，也可用于加密文件，基于 C++ 11。

Abracadabra 是表演魔术 (施魔法) 时所念的咒语。

C++ 版本和 Node.js 版本完全等效，密文可以互相交叉解密。

设计它的初衷，是为了在中文互联网上公开合理地传输不安全的信息。

**在线体验**: [**Github DEMO Page**](https://sheepchef.github.io/Abracadabra_demo/)

**在线体验(国内直连)**: [**Cloudflare DEMO Page**](https://abracadabra-demo.pages.dev/)

**JavaScript 实现**: [**dev_node Branch**](https://github.com/SheepChef/Abracadabra/tree/dev_nodejs)

Telegram: [@abracadabra_cn](https://t.me/abracadabra_cn)

## 特性

![动画](https://github.com/user-attachments/assets/7ec6e01c-230d-4d27-a0b1-80015307c5f4)

- 方便，密文可以描述自身。
- 简短，密文简短方便传播。
- 随机，加密结果具有随机性。
- 无序，加密的文本如咒语般不可阅读。
- 安心，密码表中已剔除敏感汉字。
- 安全，AES256 + 三重转轮加密。

## 快速使用

前往 Release 页面下载构建，使用命令行调用程序。
使用参数 `-h` 查看命令帮助。

你可以用以下文本来测试，请使用默认密钥(不要输入密钥)。

```
边难全您事二起住协踵先铭碘个版赴沢月及务褔集咫氧檀银绮铭学叫涧于路以白盈种四通重都俟沥困栀裳间烯化所德即园湍
```

### ⌨️ CLI 使用须知

```shell
PS C:\Abracadabra> .\abracadabra.exe -h
***Abracadabra v2.5.1***
Usage: abracadabra_win_amd64 [OPTIONS] [DEFAULT]

Positionals:
  DEFAULT TEXT Excludes: -f -i
                              Input text, if there is no given option besides.

Options:
  -h,--help                   Print this help message and exit
  -e Excludes: -d             Force to encrypt.
  -d Excludes: -e -q          Force to decrypt.
  -q Excludes: -d             Skip appending encrypt marks.
  -g                          Ignore any data checks.
  -t                          Test/Debug mode, output more informations.
  -f TEXT Excludes: DEFAULT -i
                              Input an arbitrary given file.
  -o TEXT                     Declare an output file to save the result.
  -i TEXT Excludes: DEFAULT -f
                              Input text, expected if -f is not used.
  -k TEXT                     Key to encrypt, ABRACADABRA in default.
```

程序的输入和输出分离，输入可以是 `-i` 后跟一串字符串，也可以是 `-f` 后指定任意文件。 默认情况下结果输出在控制台，也可以 `-o` 后指定一个输出文件。

**理论上本程序可以处理任何文件，解密显著慢于加密。**

**处理 3MB 及以上文件时速度缓慢，加密用时呈指数增长，解密用时是加密的数倍。**

你可以在 `-k` 后附带密钥来增加密文的安全性，安全性由多重因素保证，详情请见下方加密细节。

如果你没有指定密钥，那么将使用默认密钥 `ABRACADABRA`，这会降低安全性。

`-e` 强制加密给定数据，无视标志位检测结果。

`-d` 强制解密给定数据，无视标志位检测结果。

`-q` 可以跳过向密文增加标志位的步骤，增强隐蔽性，但解密时需要显式指定 `-d` 解密。

`-t` 用于额外输出加/解密的中间步骤(Base64)结果，由此你可以查看密钥对转轮步骤的影响。

`-g` 用于忽略解密过程中的数据合法性检查。

如果不附带任何模式参数 (仅提供文本)，则会自动判断给定的文本是否是密文，依照判断进行处理。

## 注意

Abracadabra 还在积极开发中，这里是一些注意事项。

### 平台兼容性

由于 Abracadabra 的功能涉及中文的输入和输出，在不同平台上，对不同编码的支持各不相同。

项目在 Windows 11 和 Ubuntu 22.04 LTS 上通过了编译测试。

在嵌入式平台(armv7a, armv8a)上通过了运行测试。

### 文件处理速度

鱼与熊掌不可兼得，本算法由于需要频繁查表，故对大文件(>3MB)处理速度较低。

本项目之目的并不是加密大文件，故不会采取积极措施优化大文件的处理速度。

### 编译与依赖

如果你想自行编译 Abracadabra，请确保正确添加了以下依赖库：

- [nlohmann/json](https://github.com/nlohmann/json) 用于 JSON 密本的解析
- [cppcodec](https://github.com/tplgy/cppcodec) 用于 Base64 编解码
- [CLI11](https://github.com/CLIUtils/CLI11) 用于解析命令行参数
- [tiny-AES-c](https://github.com/kokke/tiny-AES-c) 用于 AES 加密
- [PicoSHA2](https://github.com/okdshin/PicoSHA2) 用于计算哈希
- [zlib](https://zlib.net/) 压缩支持库
- [gzip-hpp](https://github.com/mapbox/gzip-hpp) 对 Gzip 压缩进行简单封装
- [Unishox2](https://github.com/siara-cc/Unishox2/) 短文本压缩库

另外，请确保您的环境中安装了 C++11 标准库。你需要提前编译 zlib 库并在编译时链接它。

本项目并不复杂，推荐直接用指令调用 g++ 进行构建。如果您愿意，也可以尝试 CMake。

### 密文污染

加密选择的标志位尽可能地排除了日常情况下出现碰撞的可能。

但有些极其特殊的时候，例如你正在尝试加密日语和中文夹杂的文本/文件，此时有可能出现污染现象。

如果出现污染现象，程序会立刻抛出错误并退出。

你可以指定 `-f` 强制加密，也可以指定 `-g` 忽略检查并继续尝试解密(通常不会成功)。

## 加密细节

### 加密过程

```
原数据 -> 压缩 -> AES-256-CTR -> Base64 -> 三重转轮 / 映射汉字 -> 密文
```

### 映射表

Abracadabra 使用古老的多表加密，以最常用的 3000 个汉字(剔除了可能随机组成敏感词的汉字)为密本，对大小写拉丁字母，阿拉伯数字和部分符号进行映射。

你可以自行修改映射表，制造独属于你的加密程序。

### AES-256-CTR

核心安全性由久经考验的 AES 加密算法提供，我们不打算重新发明密码学。

AES 加密密钥和转轮密钥是同一个，均采用哈希值。

### 三重转轮

模拟古老的转轮加密，每次加密均会对密本映射进行偏移。

简言之，程序会将给定的密钥进行 SHA256，得到一个长度为 32 的 Uint8_t 数组。

这个数组中的每个数字，都会决定三重转轮中每个转轮每次迭代的转动方向和转动距离，其复杂程度堪比甚至胜过 Enigma 机。

数字/符号，字母分别拥有一套转轮，即总共六个转轮，改变密钥相当于更换一套完全不同的转轮。

转轮显著增加了 Base64 密文的安全性，可以有效抵抗多种攻击，如果你对具体实现方法感兴趣，欢迎查阅代码。

### 随机性

在映射为汉字的时候，每个字母/数字/符号均有多种可能性，完全随机选择。

这进一步降低了密文的规律性，让它看起来像毫无意义的汉字字符串。

### 标志位

使用 日本和制汉字 与 汉语停用字 组成二字标志位，用于标记密文的类型。

标志位隐蔽，在密文中随机位置插入，不易察觉。

### 灵感

Abracadabra 的灵感来源于网络上曾流行过的熊曰加密。

## Abracadabra VS 与熊论道

```
愿青空的祝福，与我的羽翼同在

Abracadabra(等效密文，默认密钥):
靛让每菁选名氘添硫业纽定妃祉们间檀飒蛟建去菁畔坞店只玖不班走欲办泉玊靠益登很更雫砥浇惦服谜曳经描芳贮类座钒件
氖霞上铂赛些夕给锗所片奖过达侃五霞裕化鸠带萌芳留欤智请鲤花锻千悟羟短好要铁年萤萤祁莺间营桅无琼氮经店完沢添局
本好房咨至浣理雅茶夏前缬赴款谜玊每客着舒事方何也欣茶在闪图带仅钠祥没沃汨锡鸭院个氘大座去莉纽北款桜氧闭泉描本

与熊论道(唯一密文):
呋食食嘍嗡吖物吃訴吖物嗅喜達拙達發怎嘍襲現嗷既歡嚄類捕歡達哞呆麼出啽吃堅和吖既森寶蜂眠森告發沒破吖歡嘶盜達告爾取襲
```

| 特性 \ 工具  | Abracadabra       | 与熊论道        |
| ------------ | ----------------- | --------------- |
| 易用性       | 🟡 稍弱           | ✅ 傻瓜化       |
| 加密文本体积 | ✅ 更短           | 🟡 较短         |
| 加密方式     | ✅ AES-256 / 转轮 | ❌ 非公开算法   |
| 加密过程     | ✅ 密钥参与       | ❌ 无用户密钥   |
| 算法安全     | ✅ 抗多种攻击     | ❌ 易受攻击     |
| 随机性       | ✅ 密文多变       | ❌ 密文固定     |
| 隐私性       | ✅ 完全本地加密   | ❌ 上传到服务器 |
| 密文构成     | ✅ 常见字         | 🟡 罕见字       |
| 密文特征     | ✅ 无明显特征     | ❌ 特征明显     |
| 文件加密     | ✅ 支持(较慢)     | ❌ 不支持       |
| 开源         | ✅ 开源           | ❌ 不开源       |

## Todo

- [x] ~~实现更规范地解析命令参数~~
- [x] ~~实现加密任意文件，输出文本文档~~
- [x] ~~用 Node.js 完整实现 Abracadabra 的轮子~~
- [x] ~~实现让嵌入自定义密本更具灵活性~~
- [x] ~~数据的可靠压缩~~
