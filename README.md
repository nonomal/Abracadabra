# Abracadabra：用中文表示一切

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

**Abracadabra** 是一个多表加密之小项目，使用汉字作为密文，支持自定义密文映射和关键词映射，你正在查阅其基于 Node.js 的分支。

Abracadabra 是表演魔术 (施魔法) 时所念的咒语。

设计它的初衷，是为了在中文互联网上公开合理地传输不安全的信息。

**在线体验**: [**Web DEMO Page**](https://sheepchef.github.io/Abracadabra/)

**查阅 C++ 实现**: [**dev_c Branch**](https://github.com/SheepChef/Abracadabra/tree/dev_c)

## 特性

- 方便，密文可以描述自身。
- 随机，加密结果具有随机性。
- 无序，加密的文本如咒语般不可阅读。
- 安心，密码表中已剔除敏感汉字。
- 安全，转轮加密更添破译难度。

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

Abracadabra.BASE64 = "BASE64";
强制用Base64模式加密

Abracadabra.DIRECT = "DIRECT";
强制用普通模式加密(一定条件下)
*/
Abra.Input(input,mode)
```

第一个参数 `input` 接受两种类型的输入，分别是 `String` 和 `Uint8Array`，这是此前在实例化的时候指定的输入类型。

如果你指定了 `UINT8` 却传入 `String`，将抛出错误，反之亦然。

第二个参数 `mode` 接受五种特定字符串的输入，任何其他输入都将被视为 `AUTO` 并被忽略。

如果你指定了 `DIRECT` 或者 `DECRYPT`，且给定输入存在特殊字符，那么将被视为 `AUTO` 并被忽略。

在无错误的情况下， `Input()` 函数的返回值通常是 `0`

### Output()

```Javascript
import { Abracadabra } from 'abracadabra-cn'

let Abra = new Abracadabra(); //不附带参数，

Abra.Input(input,mode)

let Result = Abra.Output() //获取输出
```

在调用 `Output()` 之前，你需要至少调用过一次 `Input()`，否则将会抛出错误。

调用 `Output()` 将获得此前输入的处理结果，其返回类型可能是 `String` 或 `Uint8Array`，取决于对象实例化时指定了何种输出模式。

## 注意

Abracadabra 还在积极开发中，这里是一些注意事项。

### 平台兼容性

你正在查阅 Abracabra 基于 Node.js 的实现。

此分支不存在平台兼容性问题。

### 已知问题

#### 处理文件耗时指数级增加

密文选取的随机性导致了此问题。

原则上不能以牺牲随机性为代价换取执行速度，且本项目之目的并不是将文件转换为上百万个汉字，故搁置该问题。

小于 100kb 的文件均能在可控时间内得到处理。

#### 密本随机性不足

密本亟待扩充，后续会增加汉字映射。

已有的映射不会删减，只会在此基础上增加，以确保未来版本的向下兼容性。

## 细节

### 加密实现

Abracadabra 使用古老的多表加密，以最常用的 500 个汉字(剔除了可能随机组成敏感词的汉字)为密本，对大小写拉丁字母，阿拉伯数字和部分符号进行映射。

大写字母的映射方式为在小写字母前添加一个汉字的标志位，元音字母有更多的映射可能。

### 单重转轮

模拟古老的转轮加密，每次加密均会对密本映射进行偏移。

密本先向右偏移两位，再向左偏移一位。字母、符号、数字分开轮换。

```
abcdefghijklmnopqrstuvwxyz <-- 原始映射 / 加密第一个字符

cdefghijklmnopqrstuvwxyzab <-- 加密第二个字符 / 右移两位
例如，此时要加密字母a，那么会映射到字母c，再查表。

bcdefghijklmnopqrstuvwxyza <-- 加密第三个字符 / 左移一位
例如，此时要加密字母a，那么会映射到字母b，再查表。

以此类推，循环往复。

```

转轮增加了密文的安全性，可以有效抵抗多种攻击。

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
