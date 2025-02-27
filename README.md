# Abracadabra 魔曰

<div align=center>
<img src="https://github.com/user-attachments/assets/4c6544fe-166b-4572-acd6-cd1d6d3b4ca0" width="20%" height="20%">
</div>

<div align=center>
<h3>Abracadabra 魔曰</h3>

<h3>下一代文本防和谐工具</h3>
</div>

<div align=center>
  
![License](https://img.shields.io/github/license/SheepChef/Abracadabra?color=yellow)
![JavaScript](https://img.shields.io/badge/lang-JavaScript-orange)
![WASM](https://img.shields.io/badge/binary-WASM-b33bb3)

[<img src="https://img.shields.io/github/v/release/SheepChef/Abracadabra?color=00aaff"/>](https://github.com/SheepChef/Abracadabra/releases/latest)
![GitHub Repo stars](https://img.shields.io/github/stars/SheepChef/Abracadabra)

</div>

<div align=center>

[<img src="https://img.shields.io/badge/立刻使用-ffd91c?logo=cloudflarepages&style=for-the-badge&logoColor=000000" width="170"/>](https://abracadabra-demo.pages.dev/)
[<img src="https://img.shields.io/badge/下载插件-8a54ff?logo=googlechrome&style=for-the-badge&logoColor=ffffff" width="170" />](#浏览器插件)

[<img src="https://img.shields.io/badge/前端源码仓库-9a10b5?style=for-the-badge" width="120" />](https://github.com/SheepChef/Abracadabra_demo)
[<img src="https://img.shields.io/badge/贡献压缩字典-54ffac?style=for-the-badge" width="120" />](https://forms.gle/BBD5McqU6Bws6hiw6)
[<img src="https://img.shields.io/badge/更新频道-0970ba?logo=telegram&style=for-the-badge&logoColor=ffffff" width="118" />](https://t.me/abracadabra_cn)

</div>

**Abracadabra(魔曰)** 是一个安全高效的文本脱敏加密工具，对任意给定数据进行处理。

由此使数据不易被自动过滤识别，减低封删率，增加审核成本。

请查阅 [**部署指南**](DEPLOY.md) 快速开始使用本项目。

要深入了解本项目的设计思路，内部机制和最佳实践，请查阅 [**细节和使用指南**](https://github.com/SheepChef/Abracadabra/blob/main/USAGE.md)

更多延申内容，例如本算法与同类产品的比较，请查阅 [**博客文章**](https://shef.cc/2024/11/30/abracadabra/)

## 特性

- **仿真，使用文言语法句式**。
- 简短，密文简短方便传播。
- 随机，加密结果具有随机性。
- 安心，密码表中已剔除敏感汉字。
- 安全，AES256 + 三重转轮混淆。
- 双模式，同时支持仿真加密和传统加密。

###  **古文仿真：下一代防和谐解决方案**

> 虽无灯花之看，亦旅以良开临韵，鹏欲至物航定，但霞梦诚返，鹂当信花泊放，却风森良进，以书现，若走花度岩，舒鸢临笑，兰镜善停。
>
> 此语有绚绸悠褔，慧涧聪岩，不夏也，鸳可言云探问，且铃涧远奏，茶想彰花称选，且书雪轻赴，此雪有谜鸳少梦，极天莹空，今现韵以泊良雨，以岩，当去瑞花，非韵买鸢所当良画，不可去也。

生成高仿真文言文，**参考康熙二十三年《古文观止》真实语料**。

与传统方案一致的高强度加密，更复杂的组句/语法选择机制，更先进的消息隐写。

将链接和短文本隐写在似是而非的文言文中，**_骗过所有传统检测，_**[**_甚至大语言模型_**](https://github.com/SheepChef/Abracadabra/issues/64)(结果因模型而异)。

密文高度随机，支持用户自行选择密文的随机性。

## 快速使用

请查阅 [**部署指南**](DEPLOY.md) 来了解详细使用方法。

### JavaScript

使用 npm 下载 Abracadabra 库。

你也可以前往 Release 页面直接下载Js文件。

```shell
npm install abracadabra-cn
```

然后，在项目中引入库文件

```javascript
import { Abracadabra } from "abracadabra-cn";
```

### WebAssembly

前往 Release 下载编译好的 WebAssembly 文件。

然后，使用 [**wasmtime**](https://github.com/bytecodealliance/wasmtime) 来调用它。

```shell

echo '{"method":"NEXT","mode":"ENCRYPT","inputType":"TEXT","outputType":"TEXT","input":"测试","key":"ABRACADABRA","q":true,"r":50}' | wasmtime abracadabra-cn.wasm

```

本项目的 WebAssembly 模块使用 [**Javy**](https://github.com/bytecodealliance/javy) 编译而来，方便在 C++、Rust、Go 等语言中调用，**不推荐**在类似 Python、 Java、Node.js 的解释器中调用。

要调用本 WebAssembly 模块，需要使用尚在预览状态的 [**WASI**](https://github.com/WebAssembly/WASI)，目前仅有 wasmtime 提供了最完整的 WASI 支持，但它在各个语言的实现并不一致，具体请见 [**部署指南**](DEPLOY.md)。

### 静态页面 / 前端源码

本项目有自动托管在Cloudflare Pages的静态页面可供直接使用。

如果你想自行快速部署这个静态页，可以在Release中下载快速部署文件包。若要自行编译或修改，请前往前端源代码仓库。

浏览器插件的源码同样在前端源代码仓库，位于crx分支。

[<img src="https://img.shields.io/badge/静态页面-ffd91c?logo=cloudflarepages&style=for-the-badge&logoColor=000000" width="130"/>](https://abracadabra-demo.pages.dev/)
[<img src="https://img.shields.io/badge/前端源码-9a10b5?style=for-the-badge" width="103" />](https://github.com/SheepChef/Abracadabra_demo)

### 浏览器插件

浏览器插件基于本项目的 JavaScript 实现。

已上架 **Chrome WebStore**, **Edge 加载项** 和 **Firefox 扩展**。

如果不方便访问Chrome插件商店，也可以访问Edge插件商店，和Firefox扩展商店。

[<img src="https://img.shields.io/badge/Chrome 商店-8a54ff?logo=chromewebstore&style=for-the-badge&logoColor=ffffff" width="171" />](https://chrome.google.com/webstore/detail/jgmlgdoefnmlealmfmhjhnoiejaifpko)
[<img src="https://img.shields.io/badge/MSEdge 商店-8a54ff?logo=data:image/svg%2bxml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCAyMyAyMyI+CiAgICA8cGF0aCBmaWxsPSIjZjNmM2YzIiBkPSJNMCAwaDIzdjIzSDB6Ii8+CiAgICA8cGF0aCBmaWxsPSIjZjM1MzI1IiBkPSJNMSAxaDEwdjEwSDF6Ii8+CiAgICA8cGF0aCBmaWxsPSIjODFiYzA2IiBkPSJNMTIgMWgxMHYxMEgxMnoiLz4KICAgIDxwYXRoIGZpbGw9IiMwNWE2ZjAiIGQ9Ik0xIDEyaDEwdjEwSDF6Ii8+CiAgICA8cGF0aCBmaWxsPSIjZmZiYTA4IiBkPSJNMTIgMTJoMTB2MTBIMTJ6Ii8+Cjwvc3ZnPg==&style=for-the-badge&logoColor=ffffff" width="170" />](https://microsoftedge.microsoft.com/addons/detail/abracadabra-%E9%AD%94%E6%9B%B0/kfkmhdcahjblddpkkmnjeppmfmfoihkb)
[<img src="https://img.shields.io/badge/Firefox 商店-8a54ff?logo=firefoxbrowser&style=for-the-badge&logoColor=ffffff" width="174" />](https://addons.mozilla.org/zh-CN/firefox/addon/abracadabra-%E9%AD%94%E6%9B%B0/)

> **提示：Edge 插件商店的上架审核速度十分缓慢，因此更新速度也更慢。不推荐从Edge商店下载本插件。**

## 注意

Abracadabra 还在积极开发中，这里是一些注意事项。

### 密文污染(传统加密)

加密选择的标志位尽可能地排除了日常情况下出现碰撞的可能。

但有些极其特殊的时候，例如你正在尝试加密日语和中文夹杂的文本/文件，此时有可能出现污染现象。

如果出现污染现象，程序会立刻抛出错误并退出。

你可以选择强制加密来解决此问题。

## 细节概要

请查阅 [**细节和使用指南**](https://github.com/SheepChef/Abracadabra/blob/main/USAGE.md) 了解更多

### 加解密过程

```
明文 -> 压缩 -> AES-256-CTR -> Base64 -> 三重转轮 / 映射汉字 / 组句(仅仿真加密)-> 密文

密文 -> 解仿真(仅仿真加密) -> 转轮逆映射 -> Base64 -> AES-256-CTR 解密 -> 解压缩 -> 明文
```

### 映射表

Abracadabra 以最常用的 3000 个汉字为密本，对大小写拉丁字母，阿拉伯数字和部分符号进行映射。

密表为纯人工编纂，剔除了可能随机组成敏感词的汉字，不含任何贬义字。

映射表公开可查，查阅 [**映射表(传统)**](https://github.com/SheepChef/Abracadabra/blob/main/src/cplusplus/mapping.json) 或者 [**映射表(仿真)**](https://github.com/SheepChef/Abracadabra/blob/main/src/javascript/mapping_next.json) 以了解密本的全貌。

### AES-256-CTR

核心安全性由久经考验的 AES 加密算法提供，采用无填充的AES-256-CTR，节省密文长度。

AES 加密密钥和转轮密钥是同一个，均采用哈希值。

### 三重转轮混淆

模拟古老的转轮，每次加密均会对密本映射进行偏移。

简言之，程序会将给定的密钥进行 SHA256，得到一个长度为 32 的 Uint8_t 数组。

这个数组中的每个数字，都会决定三重转轮中每个转轮每次迭代的转动方向和转动距离。

数字/符号，字母分别拥有一套转轮，即总共六个转轮，改变密钥相当于更换一套完全不同的转轮。

转轮显著增加了 Base64 密文的安全性，查阅 [**Issue#30**](https://github.com/SheepChef/Abracadabra/issues/30) 来了解转轮的详细运行机制。

### 随机性

在映射为汉字的时候，每个字母/数字/符号均有多种可能性，完全随机选择。

这进一步降低了密文的规律性，让关键词分词识别难以奏效。

## 功能比较

<table width="450px">
<tr>
<th>特性</th>
<th align=center>Abracadabra</th>
<th align=center>与熊论道</th>
<th align=center>佛曰</th>
<th align=center>兽音</th>
<th align=center>Whisperer</th>
</tr>
<tr>
<td>开源</td>
<td align=center>✅</td>
<td align=center>❌</td>
<td align=center>❌</td>
<td align=center>✅</td>
<td align=center>✅</td>
</tr>
<tr>
<td>易用</td>
<td align=center>✅</td>
<td align=center>✅</td>
<td align=center>✅</td>
<td align=center>✅</td>
<td align=center>✅</td>
</tr>
<tr>
<td>加密</td>
<td align=center>✅</td>
<td align=center>❌</td>
<td align=center>✅</td>
<td align=center>❌</td>
<td align=center>❌</td>
</tr>
<tr>
<td>仿真伪装</td>
<td align=center>✅</td>
<td align=center>❌</td>
<td align=center>❌</td>
<td align=center>❌</td>
<td align=center>❌</td>
</tr>
<tr>
<td>本地运行</td>
<td align=center>✅</td>
<td align=center>❌</td>
<td align=center>✅</td>
<td align=center>✅</td>
<td align=center>✅</td>
</tr>
<tr>
<td>短密文</td>
<td align=center>✅</td>
<td align=center>🟡</td>
<td align=center>❌</td>
<td align=center>❌</td>
<td align=center>✅</td>
</tr>
<tr>
<td>随机性</td>
<td align=center>✅</td>
<td align=center>❌</td>
<td align=center>✅</td>
<td align=center>❌</td>
<td align=center>🟡</td>
</tr>
<tr>
<td>抗识别</td>
<td align=center>✅</td>
<td align=center>❌</td>
<td align=center>❌</td>
<td align=center>❌</td>
<td align=center>✅</td>
</tr>
<tr>
<td>自判断</td>
<td align=center>✅</td>
<td align=center>❌</td>
<td align=center>❌</td>
<td align=center>❌</td>
<td align=center>❌</td>
</tr>
<tr>
<td>自校验</td>
<td align=center>✅</td>
<td align=center>❌</td>
<td align=center>✅</td>
<td align=center>❌</td>
<td align=center>❌</td>
</tr>
<tr>
<td>易部署</td>
<td align=center>✅</td>
<td align=center>❌</td>
<td align=center>❌</td>
<td align=center>✅</td>
<td align=center>🟡</td>
</tr>
</table>

## 鸣谢

感谢 [**Unishox2**](https://github.com/siara-cc/Unishox2) 提供高效的短文本压缩方案。

感谢贡献 PR 和参与测试的所有人。

## Star History

[![Star History Chart](https://api.star-history.com/svg?repos=SheepChef/Abracadabra&type=Date)](https://star-history.com/#SheepChef/Abracadabra&Date)
