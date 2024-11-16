import { Base64 } from "js-base64";
import CryptoJS from "crypto-js";

const Map =
  '{"basic":{"alphabet":{"a":["请","上","中","之","等","人","到","年","个","将"],"b":["得","可","并","发","过","协","曲","闭","斋","峦"],"c":["页","于","而","被","无","挽","裕","斜","绪","镜"],"d":["由","把","好","从","会","帕","莹","盈","敬","粒"],"e":["的","在","了","是","为","有","和","我","一","与"],"f":["站","最","号","及","能","迟","鸭","呈","玻","据"],"g":["着","很","此","但","看","浩","附","侃","汐","绸"],"h":["名","呢","又","图","啊","棉","畅","蒸","玫","添"],"i":["对","地","您","给","这","下","网","也","来","你"],"j":["更","天","去","用","只","矽","萌","镁","芯","夸"],"k":["第","者","所","两","里","氢","羟","纽","夏","春"],"l":["自","做","前","二","他","氦","汀","兰","竹","捷"],"m":["家","点","路","至","十","锂","羧","暑","夕","振"],"n":["区","想","向","主","四","铍","烃","惠","芳","岩"],"o":["就","新","吗","该","不","多","还","要","让","大"],"p":["小","如","成","位","其","硼","酞","褔","苑","笋"],"q":["吧","每","机","几","总","碳","铂","涓","绣","悦"],"r":["起","它","内","高","次","氮","铵","奏","鲤","淳"],"s":["非","元","类","五","使","氧","醇","迷","霁","琅"],"t":["首","进","即","没","市","氖","酯","琳","绫","濑"],"u":["后","三","本","都","时","月","或","说","已","以"],"v":["种","快","那","篇","万","钠","炔","柯","睿","琼"],"w":["长","按","报","比","信","硅","烷","静","欣","束"],"x":["再","带","才","全","呀","磷","烯","柔","雪","冰"],"y":["业","却","版","美","们","硫","桉","寒","冻","玖"],"z":["像","走","文","各","当","氯","缬","妃","琉","璃"]},"number":{"0":["卡","风","水","放","花","钾","宏","谊","探","棋"],"1":["需","头","话","曾","楼","钙","吾","恋","菲","遥"],"2":["连","系","门","力","量","钛","苗","氛","鹤","雀"],"3":["书","亿","跟","深","方","钒","鸳","鸯","纸","鸢"],"4":["若","低","谈","明","百","铬","羯","尧","舜","兆"],"5":["关","客","读","双","回","锰","熙","瀚","渊","灯"],"6":["较","品","嘛","单","价","钴","阑","珊","雁","鹂"],"7":["山","西","动","厂","热","锌","鹃","鸠","昆","仑"],"8":["言","笑","度","易","身","镓","乾","坤","澈","饺"],"9":["份","星","千","仍","办","锗","彗","聪","慧","磋"]},"symbol":{"+":["集","费","传","室","拉","瑞","琴","森","辉"],"/":["难","界","指","管","具","善","智","蔬","缎"],"?":["相","儿","李","早","拿"],"-":["科","白","段","飞","住"],".":["利","红","板","光","约"],"(":["变","款","林","夹","院"],")":["服","句","声","务","游"],"[":["股","南","社","阿","远"],"]":["意","换","些","必","赛"],"<":["届","完","乐","彩","讲"],">":["展","帮","且","物","班"],",":["何","流","密","某","房"],"|":["语","亚","常","除","装"],"=":["极","载","题","刚","气","程","舒","雅","益"],"@":["米","影","德","世","坐"],"#":["北","招","短","活","斯"],"!":["值","店","树","哪","余"],"~":["盘","速","座","求","创"],"`":["梦","足","半","视","安"],"$":["空","歌","派","顶","登"],"%":["夜","云","感","啦","欲"],"^":["边","工","眼","街","奖"],"&":["获","占","理","任","实"],"*":["知","掉","色","讯","克"],"_":["直","评","往","层","园"],"{":["留","靠","亦","罗","营"],"}":["合","尚","产","诚","汨"],":":["曱","朩","杉","杸","歩"],";":["毋","氕","気","氘","氙"]," ":["叧","叺","叻","叾","吅","叿","吙","呡","呤","呮","呭","呾","呟","吂","吤"],"\\t":["圠","圡","圢","圤","圥","圦","坆","夨","夨","夬","夳","夶","奀","夻","夼"],"\\n":["孒","孖","尐","尛","尢","尣","巛","巜","幷","弐","彑","彡","彳","忄","扖"]}},"link":{"http":["贴","则","老","生","达"],"://":["商","行","周","证","经"],"magnet":["事","场","同","化","找"],"udp":["建","手","道","间","式"],"tcp":["特","城","型","定","接"],"ftp":["局","问","重","叫","通"],":?xt=urn:btih:":["件","少","面","金","近"],"torrent":["买","听","学","见","称"],"www":["写","选","片","体","组"],"mailto":["先","仅","别","表","现"]},"special":{"BIG":["未","哦","部","项","谁","分","转","字","数","心","子","处","作","因","设","环","青","雨","泊","注","织","赴","茶"],"DECRYPT":{"JP":["桜","込","凪","雫","実","沢"],"CN":["汢","垈","玊","欤","瞐","囧"]}}}';

var RoundFlip = 0; //标志现在到哪了
var RoundControl = new Uint8Array(32); //一个数组，用密钥哈希来控制轮转的行为
const Normal_Characters =
  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+=_-/?.>,<|`~!@#$%^&*(){}[];: \n\t1234567890"; //表内有映射的所有字符组成的字符串
const LETTERS = "abcdefghijklmnopqrstuvwxyz";
var LETTERS_ROUND_1 = "abcdefghijklmnopqrstuvwxyz";
var LETTERS_ROUND_2 = "tdgxnvyscmahlqwopjzeiurbfk"; //手动随机打乱的乱序轮
var LETTERS_ROUND_3 = "abcdefghijklmnopqrstuvwxyz";
const BIG_LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const NUMBERS = "1234567890";
var NUMBERS_ROUND_1 = "1234567890";
var NUMBERS_ROUND_2 = "3709641852"; //手动随机打乱的乱序轮
var NUMBERS_ROUND_3 = "1234567890";
const SYMBOLS = "+=_-/?.>,<|`~!@#$%^&*(){}[];: \n\t";
var SYMBOLS_ROUND_1 = "+=_-/?.>,<|`~!@#$%^&*(){}[];: \n\t";
var SYMBOLS_ROUND_2 = "@,$\t~&<[%{`#:|/*(=]?\n+.;>} _)-!^"; //手动随机打乱的乱序轮
var SYMBOLS_ROUND_3 = "+=_-/?.>,<|`~!@#$%^&*(){}[];: \n\t";
const SIG_DECRYPT_JP = "桜込凪雫実沢";
const SIG_DECRYPT_CN = "汢垈玊欤瞐囧";
const NULL_STR = "孎"; //默认忽略的占位字符，一个生僻字。

const Map_Obj = JSON.parse(Map);

function AES_256_CTR_E(Uint8attr, key) {
  let KeyHash = CryptoJS.SHA256(key);
  let KeyHashHash = CryptoJS.SHA256(KeyHash); //密钥两次哈希

  let HashArray = wordArrayToUint8Array(KeyHash);
  let HashHashArray = wordArrayToUint8Array(KeyHashHash);

  let ivArray = new Uint8Array(16);

  for (var i = 0; i < 16; i++) {
    ivArray[i] = HashHashArray[i];
  }

  let iv = CryptoJS.lib.WordArray.create(ivArray);
  let msg = CryptoJS.lib.WordArray.create(Uint8attr);

  let Enc = CryptoJS.AES.encrypt(msg, KeyHash, {
    mode: CryptoJS.mode.CTR,
    padding: CryptoJS.pad.NoPadding,
    iv: iv,
  });
  return wordArrayToUint8Array(Enc.ciphertext);
}

// 将WordArray转换为Uint8Array
function wordArrayToUint8Array(data) {
  const dataArray = new Uint8Array(data.sigBytes);
  for (let i = 0x0; i < data.sigBytes; i++) {
    dataArray[i] = (data.words[i >>> 0x2] >>> (0x18 - (i % 0x4) * 0x8)) & 0xff;
  }
  return dataArray;
}

function stringToUint8Array(str) {
  let tempBase64 = Base64.encode(str);
  return Base64.toUint8Array(tempBase64);
}
function Uint8ArrayTostring(fileData) {
  let tempBase64 = Base64.fromUint8Array(fileData);
  return Base64.decode(tempBase64);
}

function setCharOnIndex(string, index, char) {
  if (index > string.length - 1) return string;
  return string.substring(0, index) + char + string.substring(index + 1);
}

function GetRandomIndex(length) {
  let Rand1 = Math.floor(Math.random() * 10000);
  let Rand2 = Rand1 % length;
  return Rand2;
}

function insertStringAtIndex(str, value, index) {
  // 分割字符串为两部分，并在中间插入新值
  return str.slice(0, index) + value + str.slice(index);
}

function difference(arr1, arr2) {
  return arr1.filter((item) => !arr2.includes(item));
}
function rotateString(str, n) {
  return str.slice(n) + str.slice(0, n);
}

function LrotateString(str, n) {
  return str.slice(str.length - n) + str.slice(0, str.length - n);
}
function RoundKeyMatch(keyIn) {
  //查询轮换密钥的键值
  let idx1, idx2, idx3;
  let idx1_1, idx2_1, idx3_1;
  let idx1_2, idx2_2, idx3_2;

  idx1 = LETTERS.indexOf(keyIn);
  idx2 = NUMBERS.indexOf(keyIn);
  idx3 = SYMBOLS.indexOf(keyIn);

  idx1_1 = LETTERS.indexOf(LETTERS_ROUND_1[idx1]);
  idx2_1 = NUMBERS.indexOf(NUMBERS_ROUND_1[idx2]);
  idx3_1 = SYMBOLS.indexOf(SYMBOLS_ROUND_1[idx3]);

  idx1_2 = LETTERS.indexOf(LETTERS_ROUND_2[idx1_1]);
  idx2_2 = NUMBERS.indexOf(NUMBERS_ROUND_2[idx2_1]);
  idx3_2 = SYMBOLS.indexOf(SYMBOLS_ROUND_2[idx3_1]);

  if (idx1 != -1) {
    //判断给定字符的类型
    return LETTERS_ROUND_3[idx1_2];
  } else if (idx2 != -1) {
    return NUMBERS_ROUND_3[idx2_2];
  } else if (idx3 != -1) {
    return SYMBOLS_ROUND_3[idx3_2];
  }
  return NULL_STR;
}

function DRoundKeyMatch(keyIn) {
  //查询轮换密钥的键值
  let idx1, idx2, idx3;
  let idx1_1, idx2_1, idx3_1;
  let idx1_2, idx2_2, idx3_2;

  idx1 = LETTERS_ROUND_3.indexOf(keyIn);
  idx2 = NUMBERS_ROUND_3.indexOf(keyIn);
  idx3 = SYMBOLS_ROUND_3.indexOf(keyIn);

  idx1_1 = LETTERS_ROUND_2.indexOf(LETTERS[idx1]);
  idx2_1 = NUMBERS_ROUND_2.indexOf(NUMBERS[idx2]);
  idx3_1 = SYMBOLS_ROUND_2.indexOf(SYMBOLS[idx3]);

  idx1_2 = LETTERS_ROUND_1.indexOf(LETTERS[idx1_1]);
  idx2_2 = NUMBERS_ROUND_1.indexOf(NUMBERS[idx2_1]);
  idx3_2 = SYMBOLS_ROUND_1.indexOf(SYMBOLS[idx3_1]);

  if (idx1 != -1) {
    //判断给定字符的类型
    return LETTERS[idx1_2];
  } else if (idx2 != -1) {
    return NUMBERS[idx2_2];
  } else if (idx3 != -1) {
    return SYMBOLS[idx3_2];
  }
  return NULL_STR;
}

function RoundKey() {
  let ControlNum = 0;
  if (RoundFlip == 32) {
    RoundFlip = 0;
  }
  ControlNum = RoundControl[RoundFlip] % 10; //哈希字节对十取余即操作数
  if (ControlNum == 0) {
    //等于零就赋值为10
    ControlNum = 10;
  }

  if (ControlNum % 2 == 0) {
    //操作数是偶数
    LETTERS_ROUND_1 = rotateString(LETTERS_ROUND_1, 1); //将第一个密钥轮向右轮一位
    NUMBERS_ROUND_1 = rotateString(NUMBERS_ROUND_1, 1);
    SYMBOLS_ROUND_1 = rotateString(SYMBOLS_ROUND_1, 1);

    LETTERS_ROUND_2 = LrotateString(LETTERS_ROUND_2, ControlNum / 2); //将第二个密钥轮向左轮ControlNum/2位
    NUMBERS_ROUND_2 = LrotateString(NUMBERS_ROUND_2, ControlNum / 2);
    SYMBOLS_ROUND_2 = LrotateString(SYMBOLS_ROUND_2, ControlNum / 2);

    LETTERS_ROUND_3 = rotateString(LETTERS_ROUND_3, ControlNum / 2 + 1); //将第三个密钥轮向右轮ControlNum/2+1位
    NUMBERS_ROUND_3 = rotateString(NUMBERS_ROUND_3, ControlNum / 2 + 1);
    SYMBOLS_ROUND_3 = rotateString(SYMBOLS_ROUND_3, ControlNum / 2 + 1);
  } else {
    //操作数是奇数
    LETTERS_ROUND_1 = LrotateString(LETTERS_ROUND_1, 2); //将第一个密钥轮向左轮2位
    NUMBERS_ROUND_1 = LrotateString(NUMBERS_ROUND_1, 2);
    SYMBOLS_ROUND_1 = LrotateString(SYMBOLS_ROUND_1, 2);

    LETTERS_ROUND_2 = rotateString(LETTERS_ROUND_2, ControlNum); //将第二个密钥轮向右轮ControlNum位
    NUMBERS_ROUND_2 = rotateString(NUMBERS_ROUND_2, ControlNum);
    SYMBOLS_ROUND_2 = rotateString(SYMBOLS_ROUND_2, ControlNum);

    LETTERS_ROUND_3 = LrotateString(LETTERS_ROUND_3, (ControlNum + 3) / 2); //将第三个密钥轮向左轮(ControlNum+3)/2位
    NUMBERS_ROUND_3 = LrotateString(NUMBERS_ROUND_3, (ControlNum + 3) / 2);
    SYMBOLS_ROUND_3 = LrotateString(SYMBOLS_ROUND_3, (ControlNum + 3) / 2);
  }
  RoundFlip++;
}

function RoundReset() {
  RoundFlip = 0;
  RoundControl = new Array(32);
  LETTERS_ROUND_1 = "abcdefghijklmnopqrstuvwxyz";
  LETTERS_ROUND_2 = "tdgxnvyscmahlqwopjzeiurbfk"; //手动随机打乱的乱序轮
  LETTERS_ROUND_3 = "abcdefghijklmnopqrstuvwxyz";

  NUMBERS_ROUND_1 = "1234567890";
  NUMBERS_ROUND_2 = "3709641852"; //手动随机打乱的乱序轮
  NUMBERS_ROUND_3 = "1234567890";

  SYMBOLS_ROUND_1 = "+=_-/?.>,<|`~!@#$%^&*(){}[];: \n\t";
  SYMBOLS_ROUND_2 = "@,$\t~&<[%{`#:|/*(=]?\n+.;>} _)-!^"; //手动随机打乱的乱序轮
  SYMBOLS_ROUND_3 = "+=_-/?.>,<|`~!@#$%^&*(){}[];: \n\t";
}

function RoundControlInit(key) {
  let KeyHash = CryptoJS.SHA256(key);
  let HashArray = wordArrayToUint8Array(KeyHash);

  RoundControl = HashArray;
}

export class PreCheckResult {
  constructor(output, isUnNormal = false, isEncrypted = false) {
    this.output = output;
    this.isUnNormal = isUnNormal;
    this.isEncrypted = isEncrypted;
  }
}

export function preCheck(inp) {
  let input = String(inp);
  let size = input.length; //第一次遍历字符数组的函数，负责判断给定的输入类型。
  let temp, temp2, group;
  let isUnNormal = false; // 判断是否含有特殊符号(表外内容)
  let isEncrypted = false; //判定该文本是否为加密文本

  let isJPFound = false; //如果检查出一个日语标志位，则标记为真
  let isCNFound = false; //如果检查出一个汉字标志位，则标记为真
  for (let i = 0; i < size; i++) {
    temp = input[i];

    if (i != size - 1) {
      //一次遍历两个字符，遇到倒数第一个的时候防止越界
      temp2 = input[i + 1];
    } else {
      temp2 = NULL_STR;
    }
    group = temp + temp2;

    //idx = Normal_Characters.find(temp);
    if (Normal_Characters.indexOf(temp) == -1) {
      //如果在表内找不到某个字符
      isUnNormal = true; //判断含有特殊符号

      //判断这个符号是不是标识符，标识符用空字符进行占位操作
      if (SIG_DECRYPT_JP.indexOf(temp) != -1) {
        input = setCharOnIndex(input, i, NULL_STR);
        isJPFound = true;
        continue;
      }
      if (SIG_DECRYPT_CN.indexOf(temp) != -1) {
        input = setCharOnIndex(input, i, NULL_STR);
        isCNFound = true;
        continue;
      }
    }
  }

  if (isJPFound && isCNFound) {
    isEncrypted = true;
  }
  let Result = new PreCheckResult(
    stringToUint8Array(input),
    isUnNormal,
    isEncrypted
  );
  return Result;
}

export function enMap(input, l, key) {
  //input.output Uint8Array
  RoundReset();
  RoundControlInit(key);

  let OriginalData = new Uint8Array();
  OriginalData = input.output;
  let TempS;
  TempS = Uint8ArrayTostring(OriginalData);

  if (l) {
    OriginalData = stringToUint8Array(getLinkCryptText(encodeURI(TempS)));
    let TempArray = new Uint8Array(OriginalData.byteLength + 3);
    TempArray.set(OriginalData, 0);
    TempArray.set([1, 1, 1], OriginalData.byteLength);
    OriginalData = TempArray;
  } else {
    let TempArray = new Uint8Array(OriginalData.byteLength + 3);
    TempArray.set(OriginalData, 0);
    TempArray.set([2, 2, 2], OriginalData.byteLength);
    OriginalData = TempArray;
  }
  OriginalData = AES_256_CTR_E(OriginalData, key);

  let OriginStr = Base64.fromUint8Array(OriginalData);

  let TempStr1 = "",
    temp = "",
    temp2 = "",
    group = "";

  let size = OriginStr.length;
  RoundKey();
  for (let i = 0; i < size; i++) {
    temp = OriginStr[i];
    if (i != size - 1) {
      //一次遍历两个字符，遇到倒数第一个的时候防止越界
      temp2 = OriginStr[i + 1];
    } else {
      temp2 = NULL_STR;
    }
    group = temp + temp2;

    TempStr1 = TempStr1 + getCryptText(temp); //把加密字符加到结果字符串的后面
    RoundKey();
  }

  //第一个循环结束后，TempStr1应当是完全的密文，但是缺少标志位
  let RandIndex, RandIndex2;
  let Avoid = new Array();
  for (let q = 0; q < 2; q++) {
    //分两次大循环
    let PosToInset = new Array();
    let size = TempStr1.length;
    for (let i = 0; i < size; i++) {
      PosToInset.push(i);
    }
    if (q == 0) {
      //第一次大循环插入JP
      RandIndex = PosToInset[GetRandomIndex(PosToInset.length)];
      RandIndex2 = GetRandomIndex(Map_Obj["special"]["DECRYPT"]["JP"].length);
      let stemp = Map_Obj["special"]["DECRYPT"]["JP"][RandIndex2];
      TempStr1 = insertStringAtIndex(TempStr1, stemp, RandIndex);
      for (let z = RandIndex + 1; z < RandIndex + stemp.length; z++) {
        Avoid.push(z);
      }
    } else if (q == 1) {
      //第二次大循环插入CN;
      let AvailPos = new Array();
      AvailPos = difference(PosToInset, Avoid);

      RandIndex = AvailPos[GetRandomIndex(AvailPos.length)];
      RandIndex2 = GetRandomIndex(Map_Obj["special"]["DECRYPT"]["CN"].length);
      TempStr1 = insertStringAtIndex(
        TempStr1,
        Map_Obj["special"]["DECRYPT"]["CN"][RandIndex2],
        RandIndex
      );
    }
  }
  RoundReset();
  return TempStr1;
}

export function deMap(input, key) {
  RoundReset();
  RoundControlInit(key);
  let OriginStr = Uint8ArrayTostring(input.output);
  let TempStr1 = "",
    TempStrz = "";
  let temp = "",
    temp2 = "",
    group = "",
    findtemp = "";
  let size = OriginStr.length;
  for (let i = 0; i < size; i++) {
    temp = OriginStr[i];
    if (temp == NULL_STR) {
      //如果这是空字符
      continue;
    } else {
      //如果不是
      TempStrz = TempStrz + temp; //加上
      continue;
    }
  }
  size = TempStrz.length;
  OriginStr = TempStrz;
  RoundKey();
  for (let i = 0; i < size; ) {
    temp = OriginStr[i];
    if (i != size - 1) {
      //一次遍历两个字符，遇到倒数第一个的时候防止越界
      temp2 = OriginStr[i + 1];
    } else {
      temp2 = NULL_STR;
    }
    group = temp + temp2;

    findtemp = findOriginText(temp); //查找第一个字符的原文
    if (findtemp == "BIG") {
      //如果这是一个大写标志位
      findtemp = findOriginText(temp2).toUpperCase(); //那么找第二个字符的原文
      TempStr1 = TempStr1 + findtemp; //把找到的原文增加到字符串上
      RoundKey(); //轮换密钥
      i = i + 2;
      continue;
    } else {
      TempStr1 = TempStr1 + findtemp; //把找到的原文增加到字符串上
      RoundKey(); //轮换密钥
      i++;
      continue;
    }
  }
  //到这儿应该能还原出AES加密之后的Base64 TempStr1
  let TempStr2Int = new Uint8Array();
  try {
    TempStr2Int = Base64.toUint8Array(TempStr1);
    TempStr2Int = AES_256_CTR_E(TempStr2Int, key);
  } catch (err) {
    throw "Error Decoding. Bad Input or Incorrect Key.";
  }

  if (
    TempStr2Int.at(TempStr2Int.byteLength - 1) == 1 &&
    TempStr2Int.at(TempStr2Int.byteLength - 2) == 1 &&
    TempStr2Int.at(TempStr2Int.byteLength - 3) == 1
  ) {
    TempStr2Int = TempStr2Int.subarray(0, TempStr2Int.byteLength - 3);

    let OriginStr2 = Uint8ArrayTostring(TempStr2Int);
    size = OriginStr2.length;
    let TempStr3 = new String();
    for (let i = 0; i < size; ) {
      temp = OriginStr2[i];
      findtemp = findLinkOrigin(temp); //查找第一个字符的原文
      TempStr3 = TempStr3 + findtemp; //把找到的原文增加到字符串上
      RoundKey(); //轮换密钥
      i++;
      continue;
    }
    TempStr2Int = stringToUint8Array(TempStr3);
  } else if (
    TempStr2Int.at(TempStr2Int.byteLength - 1) == 2 &&
    TempStr2Int.at(TempStr2Int.byteLength - 2) == 2 &&
    TempStr2Int.at(TempStr2Int.byteLength - 3) == 2
  ) {
    TempStr2Int = TempStr2Int.subarray(0, TempStr2Int.byteLength - 3);
  } else {
    throw "Error Decrypting. Incorrect key.";
  }

  //到此，TempStr2Int 就是解密的结果，形式为字节码。
  let Res = new Object();

  Res.output = Uint8ArrayTostring(TempStr2Int);
  Res.output_B = TempStr2Int;

  RoundReset();
  return Res;
}

export function getLinkCryptText(text) {
  let s = String(text); //源文本
  let s1, s2;
  let RandIndex;

  for (let key in Map_Obj["link"]) {
    if (Map_Obj["link"].hasOwnProperty(key) && s.indexOf(key) != -1) {
      RandIndex = GetRandomIndex(Map_Obj["link"][key].length);
      s2 = Map_Obj["link"][key][RandIndex];
      s = s.replaceAll(key, s2);
    }
  }
  return s;
}

export function getCryptText(text) {
  let letter = String(text); //源文本
  let idx, idx2, idx3, idx4;

  idx = LETTERS.indexOf(letter); //是否是小写字母
  idx2 = BIG_LETTERS.indexOf(letter); //是否是大写字母
  idx3 = NUMBERS.indexOf(letter); //是否是数字
  idx4 = SYMBOLS.indexOf(letter); //是否是符号
  let RandIndex, RandIndex2;

  //判断给定字符的类型
  if (idx != -1 || idx2 != -1) {
    for (let key in Map_Obj["basic"]["alphabet"]) {
      if (Map_Obj["basic"]["alphabet"].hasOwnProperty(key)) {
        if (key == letter) {
          RandIndex = GetRandomIndex(
            Map_Obj["basic"]["alphabet"][RoundKeyMatch(key)].length
          );
          let s2 = Map_Obj["basic"]["alphabet"][RoundKeyMatch(key)][RandIndex];
          return s2;
        } else if (key.toUpperCase() == letter) {
          RandIndex = GetRandomIndex(
            Map_Obj["basic"]["alphabet"][RoundKeyMatch(key)].length
          );
          let s2 = String(
            Map_Obj["basic"]["alphabet"][RoundKeyMatch(key)][RandIndex]
          );

          RandIndex2 = GetRandomIndex(Map_Obj["special"]["BIG"].length);
          let s = String(Map_Obj["special"]["BIG"][RandIndex2]);

          return s + s2;
        }
      }
    }
  } else if (idx3 != -1) {
    for (let key in Map_Obj["basic"]["number"]) {
      if (Map_Obj["basic"]["number"].hasOwnProperty(key)) {
        if (key == letter) {
          RandIndex = GetRandomIndex(
            Map_Obj["basic"]["number"][RoundKeyMatch(key)].length
          );
          let s2 = Map_Obj["basic"]["number"][RoundKeyMatch(key)][RandIndex];
          return s2;
        }
      }
    }
  } else if (idx4 != -1) {
    for (let key in Map_Obj["basic"]["symbol"]) {
      if (Map_Obj["basic"]["symbol"].hasOwnProperty(key)) {
        if (key == letter) {
          RandIndex = GetRandomIndex(
            Map_Obj["basic"]["symbol"][RoundKeyMatch(key)].length
          );
          let s2 = Map_Obj["basic"]["symbol"][RoundKeyMatch(key)][RandIndex];
          return s2;
        }
      }
    }
  }
  return NULL_STR;
}

export function findOriginText(text) {
  let letter = String(text);
  let res;
  let res2;
  Map_Obj["special"]["BIG"].forEach((item) => {
    if (letter == item) {
      res2 = "BIG";
    }
  });
  if (res2) {
    return res2;
  }
  for (let key in Map_Obj["basic"]["alphabet"]) {
    Map_Obj["basic"]["alphabet"][key].forEach((item) => {
      if (letter == item) {
        res = DRoundKeyMatch(key);
      }
    });
  }
  for (let key in Map_Obj["basic"]["number"]) {
    Map_Obj["basic"]["number"][key].forEach((item) => {
      if (letter == item) {
        res = DRoundKeyMatch(key);
      }
    });
  }
  for (let key in Map_Obj["basic"]["symbol"]) {
    Map_Obj["basic"]["symbol"][key].forEach((item) => {
      if (letter == item) {
        res = DRoundKeyMatch(key);
      }
    });
  }
  if (res) {
    return res;
  } else {
    return NULL_STR;
  }
}

function findLinkOrigin(text) {
  let letter = String(text);
  let res;
  for (let key in Map_Obj["link"]) {
    Map_Obj["link"][key].forEach((item) => {
      if (letter == item) {
        res = key;
      }
    });
  }
  if (res) {
    return res;
  } else {
    return text;
  }
}
