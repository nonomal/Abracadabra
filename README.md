# Abracadabra：魔曰


<div align=center>
<img src="https://github.com/user-attachments/assets/4c6544fe-166b-4572-acd6-cd1d6d3b4ca0" width="20%" height="20%">
</div>

<div align=center>
<h3>Abracadabra 魔曰</h3>
</div>

<div align=center>
  
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![C++](https://img.shields.io/badge/lang-C%2B%2B-blue)
![JavaScript](https://img.shields.io/badge/lang-JavaScript-orange)
![NPM Downloads](https://img.shields.io/npm/dy/abracadabra-cn?label=npm)
![GitHub Repo stars](https://img.shields.io/github/stars/SheepChef/Abracadabra)

<a href="https://chrome.google.com/webstore/detail/jgmlgdoefnmlealmfmhjhnoiejaifpko">
<img src="https://github.com/user-attachments/assets/9d2a3518-eb92-4c52-9191-098d1abdd399" width="18%" height="18%">
</a>

</div>

<div align=center>
  
**Abracadabra(魔曰)** 是一个文本即时加密/脱敏工具，也可用于加密文件，有C++和JavaScript两个语言的实现

设计它的初衷，是为了在中文互联网上公开合理地传输不安全的信息


[**在线体验**](https://abracadabra-demo.pages.dev/) || [**Demo页/浏览器插件仓库**](https://github.com/SheepChef/Abracadabra_demo) || [**Telegram频道**](https://t.me/abracadabra_cn)

请阅读 [**部署指南**](DEPLOY.md) 快速开始使用本项目

要深入了解本项目，请查阅 [**深入细节和使用指南**](https://github.com/SheepChef/Abracadabra/blob/main/USAGE.md) 

</div>

## 特性

![动画](https://github.com/user-attachments/assets/5e5eab85-461b-4dde-8aa6-2c985a2de5f1)

- 方便，密文可以描述自身。
- 简短，密文简短方便传播。
- 随机，加密结果具有随机性。
- 无序，加密的文本如咒语般不可阅读。
- 安心，密码表中已剔除敏感汉字。
- 安全，AES256 + 三重转轮加密。

## 快速使用

请查阅 [**部署指南**](DEPLOY.md) 来了解详细使用方法。

### C++

前往 Release 页面下载构建，使用命令行调用程序。
使用参数 `-h` 查看命令帮助。

### JavaScript

使用 npm 下载 Abracadabra 库。

```shell
npm install abracadabra-cn
```

然后，在项目中引入库文件

```javascript
import { Abracadabra } from "abracadabra-cn";
```

## 注意

Abracadabra 还在积极开发中，这里是一些注意事项。

### 密文污染

加密选择的标志位尽可能地排除了日常情况下出现碰撞的可能。

但有些极其特殊的时候，例如你正在尝试加密日语和中文夹杂的文本/文件，此时有可能出现污染现象。

如果出现污染现象，程序会立刻抛出错误并退出。

对于 C++版本，你可以指定 `-f` 强制加密，也可以指定 `-g` 忽略检查并继续尝试解密(通常不会成功)。

对于 JavaScript 版本，你可以选择强制加密来解决此问题。

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

| 特性         | Abracadabra       | 与熊论道        |
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
| 浏览器插件   | ✅ 支持           | ❌ 不支持       |
| 开源         | ✅ 开源           | ❌ 不开源       |

## 鸣谢

本项目借鉴了与熊论道(熊曰加密)的设计思路，但由于与熊论道并不开源，故没有引用其代码的可能。

感谢 Unishox2 提供高效的短文本加密方案。

感谢贡献 PR 和参与测试的所有人。
