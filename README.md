# Abracadabra：用中文表示一切

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

**Abracadabra** 是一个多表加密之小项目，使用汉字作为密文，支持自定义密文映射和关键词映射，基于 C++ 11。

Abracadabra 是表演魔术 (施魔法) 时所念的咒语。

C++ 版本和 Node.js 版本完全等效，密文可以互相交叉解密。

设计它的初衷，是为了在中文互联网上公开合理地传输不安全的信息。

**在线体验**: [**Web DEMO Page**](https://sheepchef.github.io/Abracadabra/)

**查阅 Web 实现**: [**dev_node Branch**](https://github.com/SheepChef/Abracadabra/tree/dev_nodejs)

## 特性

![动画](https://github.com/user-attachments/assets/7ec6e01c-230d-4d27-a0b1-80015307c5f4)

- 方便，密文可以描述自身。
- 随机，加密结果具有随机性。
- 无序，加密的文本如咒语般不可阅读。
- 安心，密码表中已剔除敏感汉字。
- 安全，AES256 + 三重转轮加密。

## 快速使用

前往 Release 页面下载构建，使用命令行调用程序。
使用参数 `-h` 查看命令帮助。

你可以用以下文本来测试，请使用默认密钥(不要输入密钥)。
```
家他你烃瞐雨峦心夕心已千迷心斋处非了青褔十第个濑总春办硼图客理明到当所分奏汐挽项更动处那上硫雨高分于硫因第部能名协要山每笋雨缬冰设呢位页一坤数琉敬心当作啊雫赴呢心能
```

### ⌨️ CLI 使用须知

```shell
PS C:\Abracadabra> .\abracadabra.exe -h
***Abracadabra v2.0.0***
Usage: C:\Abracadabra\abracadabra.exe [OPTIONS] [DEFAULT]

Positionals:
  DEFAULT TEXT Excludes: -l -e -d -f -i
                              Input text, if there is no given option besides.

Options:
  -h,--help                   Print this help message and exit
  -l Excludes: DEFAULT -e -d  Force to encrypt using url mode.
  -e Excludes: DEFAULT -l -d  Force to encrypt normally.
  -d Excludes: DEFAULT -l -e  Force to decrypt the given input.
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

**理论上本程序可以处理任何文件，解密显著慢于加密。** 文件加密的处理依赖标志位，去除标志位可能导致文件无法解密。

如果要处理链接，使用链接模式 `-l` 可以提高效率、因为一些常用短语可以直接加密为单个字符。不会自动检测给定文本是否是链接，链接模式需要手动指定。

你可以在 `-k` 后附带密钥来增加密文的安全性，安全性由多重因素保证，详情请见下方加密细节。

如果你没有指定密钥，那么将使用默认密钥 `ABRACADABRA`，这会降低安全性。

`-t` 用于额外输出加/解密的中间步骤(Base64)结果，由此你可以查看密钥对转轮步骤的影响。

`-g` 用于忽略解密过程中的数据合法性检查。

如果不附带任何模式参数 (仅提供文本)，则会自动判断给定的文本是否是密文，依照判断进行处理。

## 注意

Abracadabra 还在积极开发中，这里是一些注意事项。

### 平台兼容性

由于 Abracadabra 的功能涉及中文的输入和输出，在不同平台上，对不同编码的支持各不相同。

项目在 Windows 11 和 Ubuntu 22.04 LTS 上通过了编译测试。

在嵌入式平台(armv7a, armv8a)上通过了运行测试。

### 依赖

如果你想自行编译 Abracadabra，请确保正确添加了以下依赖库：

- [nlohmann/json](https://github.com/nlohmann/json) 用于 JSON 密本的解析
- [cppcodec](https://github.com/tplgy/cppcodec) 用于 Base64 编解码
- [CLI11](https://github.com/CLIUtils/CLI11) 用于解析命令行参数
- [tiny-AES-c](https://github.com/kokke/tiny-AES-c) 用于 AES 加密
- [PicoSHA2](https://github.com/okdshin/PicoSHA2) 用于计算哈希

另外，请确保您的环境中安装了 C++11 标准库。

本项目并不复杂，推荐直接用指令调用 g++ 进行构建。如果您愿意，也可以尝试 CMake。

## 加密细节

### 加密过程

```
原数据 -> AES-256-CTR -> Base64 -> 三重转轮 / 映射汉字 -> 密文
```

### 映射表

Abracadabra 使用古老的多表加密，以最常用的 3000 个汉字(剔除了可能随机组成敏感词的汉字)为密本，对大小写拉丁字母，阿拉伯数字和部分符号进行映射。

大写字母的映射方式为在小写字母前添加一个汉字的标志位。

你可以自行修改映射表，制造独属于你的加密程序。

### AES-256-CTR

核心安全性由久经考验的 AES 加密算法提供，我们不打算重新发明密码学。

AES 加密密钥和转轮密钥是同一个。

### 三重转轮

模拟古老的转轮加密，每次加密均会对密本映射进行偏移。

简言之，程序会将给定的密钥进行 SHA256，得到一个长度为 32 的 Uint8_t 数组。

这个数组中的每个数字，都会决定三重转轮中每个转轮每次迭代的转动方向和转动距离，其复杂程度堪比甚至胜过 Enigma 机。

数字，字母和符号分别拥有一套转轮，即总共九个转轮，改变密钥相当于更换一套完全不同的转轮。

转轮显著增加了 Base64 密文的安全性，可以有效抵抗多种攻击，如果你对具体实现方法感兴趣，欢迎查阅代码。

### 随机性

在映射为汉字的时候，每个字母/数字/符号均有多种可能性，完全随机选择。

这进一步降低了密文的规律性，让它看起来像毫无逻辑的乱码。

### 标志位

使用 日本和制汉字 与 汉语停用字 组成二字标志位，用于标记密文的类型。

标志位隐蔽，在密文中随机位置插入，不易察觉。

### 灵感

Abracadabra 的灵感来源于网络上曾流行过的熊曰加密。

## Abracadabra VS 与熊论道

```
愿青空的祝福，与我的羽翼同在

Abracadabra(等效密文，默认密钥):
1# 锂前地想谁闭茶暑作后仍使子斋设醇的数苑锂第将没总羟办苑畅熙获舜人像夏雨次绸裕部矽西谁钠将硫作铵赴绪寒注所注能名曲该仑绣小字缬柔因垈名位被为身注当把处当桜转名哦名茶迟
2# 羧竹您向字峦处路作月千琅项峦转迷了环位羧羟请没悦两份桜笋名回占舜个璃者哦次汐于茶萌鸠心钠上业转淳雨页冻设瞐所转站蒸曲大厂铂苑哦氯雪作蒸成于和身字琉从字琉织又环蒸茶据
3# 十兰地岩织并项至茶本磋类泊得部使和因褔振所之没几者磋酞添瀚实羯等文两泊淳侃无雨矽西作篇等却分高谁页业雨羟织据垈又过多沢山几褔部妃呀设畅褔绪有身子走把子氯谁棉茶呢雨站

与熊论道(唯一密文): 
呋食食嘍嗡吖物吃訴吖物嗅喜達拙達發怎嘍襲現嗷既歡嚄類捕歡達哞呆麼出啽吃堅和吖既森寶蜂眠森告發沒破吖歡嘶盜達告爾取襲
```

| 特性 \ 工具     | Abracadabra     | 与熊论道     |
| -------------- | --------------- | ------------ |
| 易用性 | ⚠️稍弱 | ✅傻瓜化 |
| 加密后文本长度 | ❌较长(即将引入压缩) | ✅较短 |
| 是否开源 | ✅完全开源 | ❌不开源 |
| 加密方式 | ✅AES-256 / 转轮 | ❌非公开算法 |
| 加密过程 | ✅密钥参与 | ❌无密钥 |
| 算法安全 | ✅抗多种攻击 | ❌易受已知/选择明文攻击 |
|随机性| ✅强随机性(密文多变) | ❌无随机性(密文固定) |
| 隐私性 | ✅完全本地加密 | ❌上传到私人服务器加密 |
| 密文构成 | ✅汉字常见字 | ❌罕见字 |
| 密文特征 | ✅无明显特征 | ❌特征明显 |



## Todo

- [x] ~~实现更规范地解析命令参数~~
- [x] ~~实现加密任意文件，输出文本文档~~
- [x] ~~用 Node.js 完整实现 Abracadabra 的轮子~~
- [x] ~~实现让嵌入自定义密本更具灵活性~~
- [ ] 数据的可靠压缩
