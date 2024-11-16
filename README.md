# Abracadabra：用中文表示一切

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

**Abracadabra** 是一个多表加密之小项目，使用汉字作为密文，支持自定义密文映射和关键词映射，你正在查阅其基于 Node.js 的分支。

Abracadabra 是表演魔术 (施魔法) 时所念的咒语。

C++ 版本和 Node.js 版本完全等效，密文可以互相交叉解密。

设计它的初衷，是为了在中文互联网上公开合理地传输不安全的信息。

**在线体验**: [**Web DEMO Page**](https://sheepchef.github.io/Abracadabra/)

**查阅 C++ 实现**: [**dev_c Branch**](https://github.com/SheepChef/Abracadabra/tree/dev_c)

## 特性

- 方便，密文可以描述自身。
- 随机，加密结果具有随机性。
- 无序，加密的文本如咒语般不可阅读。
- 安心，密码表中已剔除敏感汉字。
- 安全，AES256 + 三重转轮加密。

## 快速使用

使用 npm 下载 Abracadabra 库。

```
npm install abracadabra-cn
```

然后，在项目中引入库文件

```
import { Abracadabra } from 'abracadabra-cn'
```

如果你想在网页中全量引入本库，可以导入 `abracadabra-cn.umd.cjs`

你可以用以下文本来测试，请使用默认密钥(不要输入密钥)。

```
家他你烃瞐雨峦心夕心已千迷心斋处非了青褔十第个濑总春办硼图客理明到当所分奏汐挽项更动处那上硫雨高分于硫因第部能名协要山每笋雨缬冰设呢位页一坤数琉敬心当作啊雫赴呢心能
```

## 部署说明

Abracadabra 库仅包含一个类型，即`Abracadabra`

使用前，你需要实例化该类型，实例化时需要两个参数来指定输入输出的方式，如果不附带参数，则自动使用默认值 `TEXT`。

```Javascript
import { Abracadabra } from 'abracadabra-cn'

let Abra = new Abracadabra(); //不附带参数，

/*
Abracadabra.TEXT = "TEXT"
Abracadabra.UINT8 = "UINT8"
*/
let Abra = new Abracadabra(InputMode,OutputMode);
//参数必须是上述二者中的一个，传入其他值会导致错误。
```

`TEXT` 表明将来的输入/输出为 `String`，`UINT8` 表明将来的输入/输出为 `Uint8Array`，你可以灵活使用两种不同的类型。

### Input()

Abracadabra 库中仅有两个方法，`Input()` 是其中一个。

```Javascript
import { Abracadabra } from 'abracadabra-cn'

let Abra = new Abracadabra(); //不附带参数，

/*
Abracadabra.LINK = "LINK";
强制以链接模式加密

Abracadabra.DECRYPT = "DECRYPT";
强制解密(一定条件下)

Abracadabra.AUTO = "AUTO";
自动(遵循自动逻辑)

Abracadabra.NORMAL = "NORMAL";
强制普通加密

*/
Abra.Input(input,mode,key)
```

第一个参数 `input` 接受两种类型的输入，分别是 `String` 和 `Uint8Array`，这是此前在实例化的时候指定的输入类型。

如果你指定了 `UINT8` 却传入 `String`，将抛出错误，反之亦然。

第二个参数 `mode` 接受特定字符串的输入，任何其他输入都将被视为 `AUTO` 并被忽略。

第三个参数 `key` 接受字符串类型的密钥输入，如果不提供，则默认使用内置密钥 `ABRACADABRA`。

如果指定了错误的密码，那么在解码/解密数据校验过程中会抛出错误。

在无错误的情况下， `Input()` 函数的返回值通常是 `0`。

### Output()

```Javascript
import { Abracadabra } from 'abracadabra-cn'

let Abra = new Abracadabra(); //不附带参数，

Abra.Input(input,mode,key)

let Result = Abra.Output() //获取输出
```

在调用 `Output()` 之前，你需要至少调用过一次 `Input()`，否则将会抛出错误。

调用 `Output()` 将获得此前输入的处理结果，其返回类型可能是 `String` 或 `Uint8Array`，取决于对象实例化时指定了何种输出模式。

## 注意

Abracadabra 还在积极开发中，这里是一些注意事项。

### 平台兼容性

你正在查阅 Abracabra 基于 Node.js 的实现。

此分支不存在平台兼容性问题。

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

## Todo

- [x] ~~实现更规范地解析命令参数~~
- [x] ~~实现加密任意文件，输出文本文档~~
- [x] ~~用 Node.js 完整实现 Abracadabra 的轮子~~
- [x] ~~实现让嵌入自定义密本更具灵活性~~
- [ ] 数据的可靠压缩
