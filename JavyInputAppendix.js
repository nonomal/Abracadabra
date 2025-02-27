// 这是在编译后附加到Artifact后面的额外内容
// 使得Javy可以将其编译成WASM

/*

传入的参数应当是JSON

{
  "method":"", // NEXT | OLD
  "inputType":"", // TEXT | UINT8
  "outputType":"", // TEXT | UINT8
  "input":"",  //输入的数据，如果是TEXT请直接输入纯文本，如果是任意字节，请输入Base64编码字符串
  "mode":"",   // ENCRYPT | DECRYPT | AUTO   // AUTO 仅在 method 指定 OLD 时合法 
  "key":"",    //加密密钥，一个字符串 //如果缺省，自动使用默认值
  "q":bool,    //OLD模式下，决定是否添加标志位 | NEXT模式下，决定输出密文是否有标点符号
  "r":number,  //仅NEXT模式下需要：算法的随机程度，越大随机性越强，默认 50，最大100，超过100将会出错;
  
}

*/

function base64ToUint8Array(base64) {
    // 将Base64字符串转换为二进制字符串
    const binaryString = _atob(base64);
    // 将二进制字符串转换为Uint8Array
    const len = binaryString.length;
    const bytes = new Uint8Array(len);
    for (let i = 0; i < len; i++) {
        bytes[i] = binaryString.charCodeAt(i);
    }
    return bytes;
}

function uint8ArrayToBase64(uint8Array) {
    return _btoa(String.fromCharCode.apply(null, uint8Array));
}

// Read input from stdin
const Javyinput = JavyreadInput();
// Call the function with the input
const Javyresult = index(Javyinput);
// Write the result to stdout
JavywriteOutput(Javyresult);

// The main function.
function index(input) {
  if(input === "ERROR"){
    return "INCORRECT JSON";
  }

  if(input.method == "NEXT"){
    if(input.inputType == "TEXT"){
        let Abra = new Abracadabra(input.inputType,input.outputType);
        Abra.Input_Next(input.input,input.mode,input.key,input.q,input.r);
        let Output = Abra.Output();
        if(input.outputType == "UINT8"){
            Output = uint8ArrayToBase64(Output);
        }
        return Output;
    }else if(input.inputType == "UINT8"){
        let Abra = new Abracadabra(input.inputType,input.outputType);
        let UINT8In = base64ToUint8Array(input.input);
        Abra.Input_Next(UINT8In,input.mode,input.key,input.q,input.r);
        let Output = Abra.Output();
        if(input.outputType == "UINT8"){
            Output = uint8ArrayToBase64(Output);
        }
        return Output;
    }else{
        return "ERROR inputType";
    }
  }else if(input.method == "OLD"){
    if(input.inputType == "TEXT"){
        let Abra = new Abracadabra(input.inputType,input.outputType);
        Abra.Input(input.input,input.mode,input.key,input.q);
        let Output = Abra.Output();
        if(input.outputType == "UINT8"){
            Output = uint8ArrayToBase64(Output);
        }
        return Output;
    }else if(input.inputType == "UINT8"){
        let Abra = new Abracadabra(input.inputType,input.outputType);
        let UINT8In = base64ToUint8Array(input.input);
        Abra.Input(UINT8In,input.mode,input.key,input.q);
        let Output = Abra.Output();
        if(input.outputType == "UINT8"){
            Output = uint8ArrayToBase64(Output);
        }
        return Output;
    }else{
        return "ERROR inputType";
    }
  }else{
    return "ERROR method";
  }
}

// Read input from stdin
function JavyreadInput() {
  const chunkSize = 1024;
  const inputChunks = [];
  let totalBytes = 0;

  // Read all the available bytes
  while (1) {
    const buffer = new Uint8Array(chunkSize);
    // Stdin file descriptor
    const fd = 0;
    const bytesRead = Javy.IO.readSync(fd, buffer);

    totalBytes += bytesRead;
    if (bytesRead === 0) {
      break;
    }
    inputChunks.push(buffer.subarray(0, bytesRead));
  }

  // Assemble input into a single Uint8Array
  const { finalBuffer } = inputChunks.reduce(
    (context, chunk) => {
      context.finalBuffer.set(chunk, context.bufferOffset);
      context.bufferOffset += chunk.length;
      return context;
    },
    { bufferOffset: 0, finalBuffer: new Uint8Array(totalBytes) },
  );

  const InputDecoded = new TextDecoder().decode(finalBuffer);
  try {
    return JSON.parse(InputDecoded);;
  } catch {
    return "ERROR";
  }
}

// Write output to stdout
function JavywriteOutput(output) {
  const encodedOutput = new TextEncoder().encode(JSON.stringify(output));
  const buffer = new Uint8Array(encodedOutput);
  // Stdout file descriptor
  const fd = 1;
  Javy.IO.writeSync(fd, buffer);
}