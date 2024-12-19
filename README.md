# Abracadabra 魔曰

<div align=center>
<img src="https://github.com/user-attachments/assets/4c6544fe-166b-4572-acd6-cd1d6d3b4ca0" width="20%" height="20%">
</div>

<div align=center>
<h3>Abracadabra 魔曰</h3>
</div>

<div align=center>
  
![License](https://img.shields.io/github/license/SheepChef/Abracadabra?color=yellow)
![GitHub commit activity](https://img.shields.io/github/commit-activity/t/SheepChef/Abracadabra?color=31b046)
![C++](https://img.shields.io/badge/lang-C%2B%2B-%2300aaff)
![JavaScript](https://img.shields.io/badge/lang-JavaScript-orange)

![GitHub Release](https://img.shields.io/github/v/release/SheepChef/Abracadabra?color=b33bb3)
![GitHub Repo stars](https://img.shields.io/github/stars/SheepChef/Abracadabra)

</div>

<div align=center>

[<img src="https://img.shields.io/badge/立刻使用-ffd91c?logo=cloudflarepages&style=for-the-badge&logoColor=000000" width="170"/>](https://abracadabra-demo.pages.dev/)
[<img src="https://img.shields.io/badge/下载插件-8a54ff?logo=googlechrome&style=for-the-badge&logoColor=ffffff" width="170" />](https://github.com/SheepChef/Abracadabra?tab=readme-ov-file#%E6%B5%8F%E8%A7%88%E5%99%A8%E6%8F%92%E4%BB%B6)

[<img src="https://img.shields.io/badge/前端源码仓库-9a10b5?style=for-the-badge" width="120" />](https://github.com/SheepChef/Abracadabra_demo)
[<img src="https://img.shields.io/badge/贡献压缩字典-54ffac?style=for-the-badge" width="120" />](https://forms.gle/BBD5McqU6Bws6hiw6)
[<img src="https://img.shields.io/badge/更新频道-0970ba?logo=telegram&style=for-the-badge&logoColor=ffffff" width="118" />](https://t.me/abracadabra_cn)

</div>

**Abracadabra(魔曰)** 是一个文本即时加密/脱敏工具，也可用于加密文件，有 C++和 JavaScript 两个语言的实现

设计它的初衷，是为了在中文互联网上公开合理地传输不安全的信息

请阅读 [**部署指南**](DEPLOY.md) 快速开始使用本项目。

要深入了解本项目，请查阅 [**深入细节和使用指南**](https://github.com/SheepChef/Abracadabra/blob/main/USAGE.md)

更多内容和本算法与同类产品的比较，请阅读[**博客文章**](https://shef.cc/2024/11/30/abracadabra/)

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

### 浏览器插件

浏览器插件基于本项目的 JavaScript 实现。

已上架 **Chrome WebStore** 和 **Edge 加载项** 。

如果不方便访问 Chrome 插件商店，也可以访问 Edge 插件商店。

[<img src="https://img.shields.io/badge/Chrome 商店-8a54ff?logo=chromewebstore&style=for-the-badge&logoColor=ffffff" width="171" />](https://chrome.google.com/webstore/detail/jgmlgdoefnmlealmfmhjhnoiejaifpko)
[<img src="https://img.shields.io/badge/MSEdge 商店-8a54ff?logo=data:image/svg%2bxml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCAyMyAyMyI+CiAgICA8cGF0aCBmaWxsPSIjZjNmM2YzIiBkPSJNMCAwaDIzdjIzSDB6Ii8+CiAgICA8cGF0aCBmaWxsPSIjZjM1MzI1IiBkPSJNMSAxaDEwdjEwSDF6Ii8+CiAgICA8cGF0aCBmaWxsPSIjODFiYzA2IiBkPSJNMTIgMWgxMHYxMEgxMnoiLz4KICAgIDxwYXRoIGZpbGw9IiMwNWE2ZjAiIGQ9Ik0xIDEyaDEwdjEwSDF6Ii8+CiAgICA8cGF0aCBmaWxsPSIjZmZiYTA4IiBkPSJNMTIgMTJoMTB2MTBIMTJ6Ii8+Cjwvc3ZnPg==&style=for-the-badge&logoColor=ffffff" width="170" />](https://microsoftedge.microsoft.com/addons/detail/abracadabra-%E9%AD%94%E6%9B%B0/kfkmhdcahjblddpkkmnjeppmfmfoihkb)

Edge 加载项的审核速度十分缓慢，因此更新速度显著慢于 Chrome WebStore。

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

## 功能比较

| 特性         | Abracadabra       | 与熊论道        | 佛曰             | 兽音             | Whisperer       |
| ------------ | ----------------- | --------------- | --------------- | --------------- | --------------- |
| 易用性       | ✅ 傻瓜化         | ✅ 傻瓜化       | ✅ 傻瓜化       | ✅ 傻瓜化       | ✅ 傻瓜化       |
| 加密方案     | ✅ 公开/安全      | ❌ 不公开/不安全 | ✅ 公开/安全    | 🟡 公开/不安全  | 🟡 公开/不安全   |
| 加密地点     | ✅ 本地           | ❌ 服务器      | ✅ 本地          | ✅ 本地         | 🟡 依赖后端     |
| 密文长度     | 🟡 较短           | 🟡 较短        | ❌ 冗长          | ❌ 冗长         | ✅ 短          |     
| 密本构成     | ✅ 常见字         | 🟡 生僻字       | 🟡 生僻字        | ❌ 无密本       | ✅ 常见字      |
| 密文随机     | ✅ 强随机性       | ❌ 无随机性     | ✅ 强随机性      | ❌ 无随机性     | 🟡 弱随机性     |
| 密文特征     | ✅ 较难识别       | ❌ 容易识别     | ❌ 容易识别      | ❌ 容易识别     | ✅ 较难识别     |
| 加解密自动   | ✅ 全自动         | ❌ 手动         | ❌ 手动         | ❌ 手动         | ❌ 手动         |
| 错误校验     | ✅ 校验位         | ❌ 无校验       | ❌ 无校验       | ❌ 无校验        | ❌ 无校验      |
| 自部署       | ✅ 简单          | ❌ 不可自部署    | 🟡 无文档       | ✅ 简单         | 🟡 无文档       |
| 开源         | ✅ 开源          | ❌ 不开源       | ❌ 不开源       | ✅ 开源         | ✅ 开源         |

## 鸣谢

本项目借鉴了与熊论道(熊曰加密)的设计思路，但由于与熊论道并不开源，故没有引用其代码的可能。

感谢 Unishox2 提供高效的短文本压缩方案。

感谢贡献 PR 和参与测试的所有人。

## Star History

[![Star History Chart](https://api.star-history.com/svg?repos=SheepChef/Abracadabra&type=Date)](https://star-history.com/#SheepChef/Abracadabra&Date)
