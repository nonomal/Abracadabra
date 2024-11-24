# Abracadabra：魔曰

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

**Abracadabra(魔曰)** 是一个文本即时加密/脱敏工具，也可用于加密文件。这是其 JavaScript 分支。

Abracadabra 是表演魔术 (施魔法) 时所念的咒语，**魔曰** 是本项目的中文别名。

C++ 版本和 Node.js 版本完全等效，密文可以互相交叉解密。

设计它的初衷，是为了在中文互联网上公开合理地传输不安全的信息。

**在线体验**: [**Github DEMO Page**](https://sheepchef.github.io/Abracadabra_demo/)

**在线体验(国内直连)**: [**Cloudflare DEMO Page**](https://abracadabra-demo.pages.dev/)

**Demo 页源码仓库**: [**Abracadabra-demo**](https://github.com/SheepChef/Abracadabra_demo)

**C++ 实现**: [**dev_c Branch**](https://github.com/SheepChef/Abracadabra/tree/dev_c)

Telegram: [@abracadabra_cn](https://t.me/abracadabra_cn)

## 特性

- 方便，密文可以描述自身。
- 简短，密文简短方便传播。
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

[**深入细节和使用指南**](https://github.com/SheepChef/Abracadabra/blob/main/USAGE.md)

你可以用以下文本来测试，请使用默认密钥(不要输入密钥)。

```
边难全您事二起住协踵先铭碘个版赴沢月及务褔集咫氧檀银绮铭学叫涧于路以白盈种四通重都俟沥困栀裳间烯化所德即园湍
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
MODES:

Abracadabra.ENCRYPT = "ENCRYPT";
强制加密

Abracadabra.DECRYPT = "DECRYPT";
强制解密

Abracadabra.AUTO = "AUTO";
自动(遵循自动逻辑)

*/
Abra.Input(input,mode,key,q)
```

第一个参数 `input` 接受两种类型的输入，分别是 `String` 和 `Uint8Array`，这是此前在实例化的时候指定的输入类型。

如果你指定了 `UINT8` 却传入 `String`，将抛出错误，反之亦然。

第二个参数 `mode` 接受上文中特定字符串的输入，任何其他输入都将被视为 `AUTO` 并被忽略。

第三个参数 `key` 接受字符串类型的密钥输入，如果不提供，则默认使用内置密钥 `ABRACADABRA`。

如果指定了错误的密码，那么在解码/解密数据校验过程中会抛出错误。

第四个参数 `q` 接受布尔值的输入，如果传入 `true`，则加密结果中将不含标志位，更加隐蔽，但解密时需要强制解密。

在无错误的情况下， `Input()` 函数的返回值通常是 `0`。

### Output()

```Javascript
import { Abracadabra } from 'abracadabra-cn'

let Abra = new Abracadabra(); //不附带参数，

Abra.Input(input,mode,key,q)

let Result = Abra.Output() //获取输出
```

在调用 `Output()` 之前，你需要至少调用过一次 `Input()`，否则将会抛出错误。

调用 `Output()` 将获得此前输入的处理结果，其返回类型可能是 `String` 或 `Uint8Array`，取决于对象实例化时指定了何种输出模式。

## 注意

Abracadabra 还在积极开发中，这里是一些注意事项。

### 平台兼容性

你正在查阅 Abracabra 基于 JavaScript 的实现。

此分支不存在平台兼容性问题。

### 文件处理速度

鱼与熊掌不可兼得，本算法由于需要频繁查表，故对大文件(>3MB)处理速度较低。

本项目之目的并不是加密大文件，故不会采取积极措施优化大文件的处理速度。

### 密文污染

加密选择的标志位尽可能地排除了日常情况下出现碰撞的可能。

但有些极其特殊的时候，例如你正在尝试加密日语和中文夹杂的文本/文件，此时有可能出现污染现象。

如果出现污染现象，程序会立刻抛出错误并退出。你可以选择强制加密来解决此问题。

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

## 鸣谢

本项目借鉴了与熊论道(熊曰加密)的设计思路，但由于与熊论道并不开源，故没有引用其代码的可能。

感谢 Unishox2 提供高效的短文本加密方案。

感谢贡献 PR 和参与测试的所有人。
