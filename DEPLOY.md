# 魔曰 部署指南

这篇文档系统地介绍 Abracadabra(魔曰)两个语言版本的部署指南。
**注意：C++版本** ***不支持*** **文言仿真加密，仅支持传统加密。**

- [**C++**](#c-命令行)
- [**JavaScript**](#javascript-npm-库)

## C++ 命令行

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

### C++ 平台兼容性

由于 Abracadabra 的功能涉及中文的输入和输出，在不同平台上，对不同编码的支持各不相同。

项目在 Windows 11 和 Ubuntu 22.04 LTS 上通过了编译测试。

在嵌入式平台(armv7a, armv8a)上通过了运行测试。

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

除了 Zlib 以外，本项目使用的所有库均是头文件/单文件库，因此只需事先下载库文件，编译时指定 Include 目录即可。

本项目并不复杂，推荐直接用指令调用 g++ 进行构建。

## JavaScript NPM 库

使用 npm 下载 Abracadabra 库。

```shell
npm install abracadabra-cn
```

然后，在项目中引入库文件

```javascript
import { Abracadabra } from "abracadabra-cn";
```

如果你想在网页中全量引入本库，可以导入 `abracadabra-cn.umd.cjs`

你可以用以下文本来测试，请使用默认密钥(不要输入密钥)。

```
边难全您事二起住协踵先铭碘个版赴沢月及务褔集咫氧檀银绮铭学叫涧于路以白盈种四通重都俟沥困栀裳间烯化所德即园湍
```

### NPM 部署说明

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

#### Input() 传统加密函数

Abracadabra 库中仅有三个方法，`Input()` 是其中一个。

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

#### Input_Next() 文言仿真加密函数

`Input_Next()` 函数用来对数据执行文言文仿真加密。

```Javascript
import { Abracadabra } from 'abracadabra-cn'

let Abra = new Abracadabra(); //不附带参数，

/*
MODES:

Abracadabra.ENCRYPT = "ENCRYPT";
强制加密

Abracadabra.DECRYPT = "DECRYPT";
强制解密

*/
Abra.Input_Next(input,mode,key,q,r)
```

第一个参数 `input` 接受两种类型的输入，分别是 `String` 和 `Uint8Array`，这是此前在实例化的时候指定的输入类型。

如果你指定了 `UINT8` 却传入 `String`，将抛出错误，反之亦然。

第二个参数 `mode` 接受上文中特定字符串的输入，任何其他输入都将被忽略，不会输出任何结果。

第三个参数 `key` 接受字符串类型的密钥输入，如果不提供，则默认使用内置密钥 `ABRACADABRA`。

如果指定了错误的密码，那么在解码/解密数据校验过程中会抛出错误。

第四个参数 `q` 接受布尔值的输入，如果传入 `true`，则加密结果中将不含标点符号，解密时可以忽略这个参数。

第五个参数 `r` 接受整数值的输入，最小值`0`，最大值`100`，超过 100 的输入将会报错。输入值越大，句式选择算法的随机性越大；输入值为 0 时，句式选择步骤将只选择载荷字最多的那个。

在无错误的情况下， `Input()` 函数的返回值通常是 `0`。

#### Output()

```Javascript
import { Abracadabra } from 'abracadabra-cn'

let Abra = new Abracadabra(); //不附带参数，

Abra.Input(input,mode,key,q)

let Result = Abra.Output() //获取输出
```

在调用 `Output()` 之前，你需要至少调用过一次 `Input()`，否则将会抛出错误。

调用 `Output()` 将获得此前输入的处理结果，其返回类型可能是 `String` 或 `Uint8Array`，取决于对象实例化时指定了何种输出模式。
