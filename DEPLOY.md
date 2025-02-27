# 魔曰 部署指南

这篇文档系统地介绍 Abracadabra(魔曰) 部署指南。

- [**Javascript**](#javascript)
- [**WebAssembly**](#webassembly)

## JavaScript

使用 npm 下载 Abracadabra 库。

```shell
npm install abracadabra-cn
```

然后，在项目中引入库文件

```javascript
import { Abracadabra } from "abracadabra-cn";
```

如果你想在网页中全量引入本库，可以导入 `abracadabra-cn.umd.cjs`

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

## WebAssembly

前往 Release 下载编译好的 WebAssembly 文件。

然后，推荐使用 [**wasmtime**](https://github.com/bytecodealliance/wasmtime) 来调用它，其他 Runtime 不做特别兼容。

本项目的 WebAssembly 模块使用 [**Javy**](https://github.com/bytecodealliance/javy) 编译而来，方便在 C++、Rust、Go 等语言中调用，**不推荐**在类似 Python、 Java、Node.js 的解释器中调用。

要调用本 WebAssembly 模块，需要使用尚在预览状态的 [**WASI**](https://github.com/WebAssembly/WASI)，目前仅有 wasmtime 提供了最完整的 WASI 支持，但它在各个语言的实现并不一致。

本模块的合法输入为一个JSON字符串，输入时请勿附带注释，遵循以下格式：

```json

{
  "method":"", // NEXT | OLD //前者是仿真加密，后者是传统加密
  "inputType":"", // TEXT | UINT8
  "outputType":"", // TEXT | UINT8
  "input":"",  //输入的数据，如果是TEXT请直接输入纯文本，如果是任意字节，请输入Base64编码字符串
  "mode":"",   // ENCRYPT | DECRYPT | AUTO   // AUTO 仅在 method 指定 OLD 时合法 
  "key":"",    //加密密钥，一个字符串，不可缺省，JavaScript实现的默认值为 ABRACADABRA
  "q":bool,    //OLD模式下，决定是否去除标志位 | NEXT模式下，决定输出密文是否有标点符号
  "r":number,  //仅NEXT模式下需要：算法的随机程度，越大随机性越强，默认 50，最大100，超过100将会出错;
  
}

```

用 wasmtime CLI 调用，在不同的命令行里有不同的方式，大多数时候是输入字符串的字符集的区别，以及是否需要在字符串外面加单引号的区别。

在 Windows CMD 或者 Powershell 中调用，请确保执行了 `chcp 65001` 以调整代码页为UTF-8。

```shell

echo '{"method":"NEXT","mode":"ENCRYPT","inputType":"TEXT","outputType":"TEXT","input":"测试","key":"ABRACADABRA","q":true,"r":50}' | wasmtime abracadabra-cn.wasm

```

对于其他语言，你需要使用 Wasmtime WASI 的 `stdin` 和 `stdout` 接口来操作本模块的输入输出，调用 `_start` 方法来启动本模块。

下方提供 Python 的示例，其他语言请自行查阅 wasmtime 对应的文档。

```shell

pip install wasmtime

```

```python

import wasmtime

def run_wasi(wasm_file):
    engine = wasmtime.Engine()
    module = wasmtime.Module.from_file(engine, wasm_file)
    store = wasmtime.Store(engine)
    linker = wasmtime.Linker(engine)
    wasi = wasmtime.WasiConfig()
    #Python 的 wasmtime 实现，想写入stdin，必须使用一个文件。
    #文件里填写要输入的JSON。
    wasi.stdin_file = "<Path_to_JSON_File>"
    wasi.inherit_stdout()
    wasi.inherit_stderr()
    linker.define_wasi()
    store.set_wasi(wasi)
    instance = linker.instantiate(store, module)
    start = instance.exports(store)["_start"]
    start(store)
try:
    run_wasi("<Path_to_WASM_Module_File>")
except FileNotFoundError:
    print(f"Error: WASM file '{wasm_file}' not found.")
except wasmtime.WasmtimeError as e:
    print(f"Wasmtime error: {e}")
except Exception as e:
    print(f"An unexpected error occurred: {e}")

```

### 用 Javy 编译模块



首先，拉取仓库，安装 [**Javy**](https://github.com/bytecodealliance/javy)，配置恰当的环境。

然后，像编译普通JS库一样，执行：

```shell

npm install

npm run build

```

在输出文件夹中，找到 `abracadabra-cn-javy.js`

然后用 Javy 在命令行中编译：

```shell

javy build "Path/to/abracadabra-cn-javy.js" -o "path/Output.wasm"

```