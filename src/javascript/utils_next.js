/*
 * Copyright (C) 2024 SheepChef (a.k.a. Haruka Hokuto)
 *
 * This program is free software:
 * you can redistribute it and/or modify it under the terms of
 * as published by the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <https://www.gnu.org/licenses/>.
 *
 */

/*
 * DISCLAIMER OF UNISHOX2
 *
 * This project uses Unishox2 as a compress library.
 * Some of its code need to be altered in order to achieve certain purposes.
 * Unishox2 was Licensed under the Apache License, Version 2.0.
 * Copyright (C) 2020 Siara Logics (cc)
 *
 */

import { Base64 } from "js-base64";
import CryptoJS from "crypto-js";
import pako from "pako";
import * as Unishox from "./unishox2.js";
import "pako";

const Map ='{\"Actual\":{\"N\":{\"alphabet\":{\"a\":\"人\",\"b\":\"镜\",\"c\":\"鸭\",\"d\":\"曲\",\"e\":\"务\",\"f\":\"绸\",\"g\":\"裳\",\"h\":\"路\",\"i\":\"岩\",\"j\":\"笋\",\"k\":\"鲤\",\"l\":\"月\",\"m\":\"雪\",\"n\":\"冰\",\"o\":\"局\",\"p\":\"字\",\"q\":\"褔\",\"r\":\"铃\",\"s\":\"琴\",\"t\":\"家\",\"u\":\"天\",\"v\":\"韵\",\"w\":\"桨\",\"x\":\"莺\",\"y\":\"铁\",\"z\":\"雨\",\"A\":\"文\",\"B\":\"猫\",\"C\":\"水\",\"D\":\"花\",\"E\":\"风\",\"F\":\"棋\",\"G\":\"楼\",\"H\":\"鹤\",\"I\":\"鸢\",\"J\":\"灯\",\"K\":\"雁\",\"L\":\"星\",\"M\":\"声\",\"N\":\"树\",\"O\":\"茶\",\"P\":\"竹\",\"Q\":\"兰\",\"R\":\"苗\",\"S\":\"心\",\"T\":\"纸\",\"U\":\"礼\",\"V\":\"梦\",\"W\":\"园\",\"X\":\"柯\",\"Y\":\"驿\",\"Z\":\"烛\"},\"numbersymbol\":{\"0\":\"森\",\"1\":\"夏\",\"2\":\"光\",\"3\":\"林\",\"4\":\"物\",\"5\":\"云\",\"6\":\"夜\",\"7\":\"城\",\"8\":\"春\",\"9\":\"苑\",\"+\":\"雀\",\"/\":\"鹂\",\"=\":\"鸳\"}},\"V\":{\"alphabet\":{\"a\":\"闭\",\"b\":\"挽\",\"c\":\"呈\",\"d\":\"添\",\"e\":\"用\",\"f\":\"成\",\"g\":\"走\",\"h\":\"达\",\"i\":\"行\",\"j\":\"称\",\"k\":\"见\",\"l\":\"学\",\"m\":\"听\",\"n\":\"买\",\"o\":\"作\",\"p\":\"设\",\"q\":\"写\",\"r\":\"定\",\"s\":\"谈\",\"t\":\"动\",\"u\":\"客\",\"v\":\"易\",\"w\":\"度\",\"x\":\"惦\",\"y\":\"筑\",\"z\":\"选\",\"A\":\"建\",\"B\":\"指\",\"C\":\"换\",\"D\":\"探\",\"E\":\"放\",\"F\":\"描\",\"G\":\"报\",\"H\":\"事\",\"I\":\"泊\",\"J\":\"现\",\"K\":\"闪\",\"L\":\"彰\",\"M\":\"需\",\"N\":\"飞\",\"O\":\"游\",\"P\":\"求\",\"Q\":\"御\",\"R\":\"航\",\"S\":\"歌\",\"T\":\"读\",\"U\":\"办\",\"V\":\"登\",\"W\":\"任\",\"X\":\"留\",\"Y\":\"砌\",\"Z\":\"系\"},\"numbersymbol\":{\"0\":\"知\",\"1\":\"至\",\"2\":\"内\",\"3\":\"去\",\"4\":\"图\",\"5\":\"说\",\"6\":\"进\",\"7\":\"信\",\"8\":\"取\",\"9\":\"问\",\"+\":\"笑\",\"/\":\"约\",\"=\":\"敬\"}},\"MV\":[\"欲\",\"应\",\"可\",\"能\",\"将\",\"请\",\"想\",\"必\",\"当\"],\"A\":{\"alphabet\":{\"a\":\"莹\",\"b\":\"畅\",\"c\":\"新\",\"d\":\"高\",\"e\":\"静\",\"f\":\"美\",\"g\":\"金\",\"h\":\"祥\",\"i\":\"善\",\"j\":\"橘\",\"k\":\"瀚\",\"l\":\"明\",\"m\":\"早\",\"n\":\"宏\",\"o\":\"飒\",\"p\":\"遥\",\"q\":\"难\",\"r\":\"慧\",\"s\":\"绚\",\"t\":\"绮\",\"u\":\"寒\",\"v\":\"冻\",\"w\":\"银\",\"x\":\"皎\",\"y\":\"热\",\"z\":\"北\",\"A\":\"旺\",\"B\":\"南\",\"C\":\"萌\",\"D\":\"捷\",\"E\":\"骏\",\"F\":\"益\",\"G\":\"雅\",\"H\":\"舒\",\"I\":\"智\",\"J\":\"谜\",\"K\":\"彩\",\"L\":\"余\",\"M\":\"短\",\"N\":\"诚\",\"O\":\"乐\",\"P\":\"怡\",\"Q\":\"瑞\",\"R\":\"惠\",\"S\":\"最\",\"T\":\"淳\",\"U\":\"悦\",\"V\":\"迷\",\"W\":\"特\",\"X\":\"少\",\"Y\":\"近\",\"Z\":\"重\"},\"numbersymbol\":{\"0\":\"远\",\"1\":\"极\",\"2\":\"安\",\"3\":\"聪\",\"4\":\"熙\",\"5\":\"老\",\"6\":\"浩\",\"7\":\"盈\",\"8\":\"快\",\"9\":\"首\",\"+\":\"后\",\"/\":\"夕\",\"=\":\"坚\"}}},\"Virtual\":{\"zhi\":[\"之\"],\"hu\":[\"乎\"],\"zhe\":[\"者\"],\"ye\":[\"也\"],\"for\":[\"为\"],\"ba\":[\"把\"],\"le\":[\"了\"],\"er\":[\"而\"],\"this\":[\"此\",\"斯\"],\"still\":[\"仍\"],\"with\":[\"与\",\"同\"],\"also\":[\"亦\",\"也\"],\"is\":[\"是\",\"乃\"],\"not\":[\"未\",\"莫\"],\"or\":[\"或\"],\"more\":[\"更\"],\"make\":[\"使\",\"将\",\"让\"],\"and\":[\"和\",\"与\",\"同\"],\"anti\":[\"非\",\"不\"],\"why\":[\"为何\",\"奈何\"],\"but\":[\"但\",\"却\",\"则\",\"而\",\"况\",\"且\"],\"like\":[\"似\",\"如\",\"若\"],\"if\":[\"若\",\"倘\"],\"int\":[\"哉\",\"呼\",\"噫\"],\"self\":[\"自\"],\"by\":[\"以\",\"于\"]},\"Sentences\":{\"Begin\":[\"1/N/曰\",\"2/A/N/曰\",\"2/N/anti/在/A\",\"3/初，/N/V/by/N\",\"3/夫/N/anti/V/by/N\",\"3/A/V/zhi/谓/A\",\"3/V/而/V/zhi/zhi/谓/A\",\"3/N/，/N/zhi/N/ye\",\"6/A/N/by/N/zhi/N/V/N\",\"9/A/N/V/zhi/而不/V/zhi/、亦/make/A/N/er/复/V/A/N/ye\"],\"Main\":[\"1/anti/MV/V/ye\",\"2/N/make/N/zhi\",\"2/MV/N/zhe/A\",\"2/有/N/则/A\",\"2/V/zhe/V/zhi\",\"2/but/MV/A/zhe/A\",\"3/N/with/N/V\",\"3/N/曰，何/A/zhi/V\",\"4/A/N/A/V\",\"4/V/N/以/V/N\",\"5/今/V/N/以/V/A/N\",\"5/N/乃/V/V/N/zhi/N\",\"7/anti/V/A/by/N/，/N/，/N/，/N/，/N/ye\"],\"End\":[\"1/anti/N/ye\",\"2/唯/N/V/zhi\",\"2/V/by/N\",\"2/其/also/A/hu/其/V/ye\",\"3/V/在/A/N\",\"4/V/N/zhi/N/by/N\",\"5/请/V/N/zhi/N/中/，/是/N/zhi/N\",\"8/何必/V/N/V/N/，/V/N/zhi/N/N/哉\"]}}'

var RoundFlip = 0; //标志现在到哪了
var RoundControl = new Uint8Array(32); //一个数组，用密钥哈希来控制轮转的行为
const Normal_Characters =
  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+/=1234567890"; //表内有映射的所有字符组成的字符串
const LETTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
var LETTERS_ROUND_1 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
var LETTERS_ROUND_2 = "FbPoDRStyJKAUcdahfVXlqwnOGpHZejzvmrBCigQILxkYMuWTEsN"; //手动随机打乱的乱序轮
var LETTERS_ROUND_3 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const BIG_LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const NUMBERS = "1234567890";
const SYMBOLS = "+/=";
const NUMBERSYMBOL = "1234567890+/=";
var NUMBERSYMBOL_ROUND_1 = "1234567890+/=";
var NUMBERSYMBOL_ROUND_2 = "5=0764+389/12"; //手动随机打乱的乱序轮
var NUMBERSYMBOL_ROUND_3 = "1234567890+/=";


//const SIG_DECRYPT_JP = "桜込凪雫実沢";
//const SIG_DECRYPT_CN = "玚俟玊欤瞐珏";
const NULL_STR = "孎"; //默认忽略的占位字符，一个生僻字。

const CHINESE_WEBPAN_LIB = [
  "https://",
  "lanzou",
  "pan.quark.cn",
  "pan.baidu.com",
  "aliyundrive.com",
  "123pan.com",
];
const INTER_WEBPAN_LIB = [
  "https://",
  "mypikpak.com",
  "mega.nz",
  "drive.google.com",
  "sharepoint.com",
  "1drv.ms",
];
const CHINESE_WEBSITE_LIB = [
  "https://",
  "baidu.com",
  "b23.tv",
  "bilibili.com",
  "weibo.com",
  "weixin.qq.com",
];
const INTER_WEBSITE_LIB = [
  "https://",
  "google.com",
  "youtube.com",
  "x.com",
  "twitter.com",
  "telegra.ph",
];
const INTER_WEBSITE_LIB_2 = [
  "https://",
  "wikipedia.org",
  "github.com",
  "pages.dev",
  "github.io",
  "netlify.app",
];
const JAPAN_WEBSITE_LIB = [
  "https://",
  "pixiv.net",
  "nicovideo.jp",
  "dlsite.com",
  "line.me",
  "dmm.com",
];
const PIRACY_WEBSITE_LIB = [
  "https://",
  "nyaa.si",
  "bangumi.moe",
  "thepiratebay.org",
  "e-hentai.org",
  "exhentai.org",
];
const GENERIC_TLINK_LIB = [
  "https://",
  "magnet:?xt=urn:btih:",
  "magnet:?xt=urn:sha1:",
  "ed2k://",
  "thunder://",
  "torrent",
];
const GENERIC_LINK_LIB_1 = ["https://", ".cn", ".com", ".net", ".org", ".xyz"];
const GENERIC_LINK_LIB_2 = ["https://", ".info", ".moe", ".cc", ".co", ".dev"];
const GENERIC_LINK_LIB_3 = ["https://", ".io", ".us", ".eu", ".jp", ".de"];

const Map_Obj = JSON.parse(Map);


function AES_256_CTR_E(Uint8attr, key, RandomBytes) {
  let KeyHash = CryptoJS.SHA256(key);
  let HashArray = wordArrayToUint8Array(KeyHash);

  let TempArray = new Uint8Array(HashArray.byteLength + 2);
  TempArray.set(HashArray, 0);
  TempArray.set([RandomBytes[0], RandomBytes[1]], HashArray.byteLength);
  HashArray = TempArray;

  let HashWithRandom = CryptoJS.lib.WordArray.create(HashArray);
  let KeyHashHash = CryptoJS.SHA256(HashWithRandom); //密钥两次哈希,附加两字节随机数
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

function GZIP_COMPRESS(Data) {
  let DataOutput = pako.gzip(Data);

  if (DataOutput.byteLength >= Data.byteLength) {
    return Data;
  }
  return DataOutput;
}
function GZIP_DECOMPRESS(Data) {
  const firstTwoBytes = new Uint8Array(Data.buffer, 0, 2);
  if (firstTwoBytes[0] === 0x1f && firstTwoBytes[1] === 0x8b) {
    // Likely compressed with gzip
    let DataOutput = pako.ungzip(Data);
    return DataOutput;
  } else {
    return Data;
  }
}
function UNISHOX_COMPRESS(Data) {
  let CompressedStrCharArray = new Uint8Array(2048);
  let Datastr = Uint8ArrayTostring(Data);
  let libmark = 255;

  for (let i = 1; i < 6; i++) {
    if (Datastr.indexOf(CHINESE_WEBPAN_LIB[i]) != -1) {
      libmark = 254;
      break;
    }
    if (Datastr.indexOf(INTER_WEBPAN_LIB[i]) != -1) {
      libmark = 245;
      break;
    }
  }
  if (libmark == 255) {
    for (let i = 1; i < 6; i++) {
      if (Datastr.indexOf(CHINESE_WEBSITE_LIB[i]) != -1) {
        libmark = 253;
        break;
      }
      if (Datastr.indexOf(INTER_WEBSITE_LIB[i]) != -1) {
        libmark = 252;
        break;
      }
      if (Datastr.indexOf(INTER_WEBSITE_LIB_2[i]) != -1) {
        libmark = 244;
        break;
      }
      if (Datastr.indexOf(JAPAN_WEBSITE_LIB[i]) != -1) {
        libmark = 251;
        break;
      }
      if (Datastr.indexOf(PIRACY_WEBSITE_LIB[i]) != -1) {
        libmark = 250;
        break;
      }
    }
  }
  if (libmark == 255) {
    for (let i = 1; i < 6; i++) {
      if (Datastr.indexOf(GENERIC_TLINK_LIB[i]) != -1) {
        libmark = 249;
        break;
      }
      if (Datastr.indexOf(GENERIC_LINK_LIB_1[i]) != -1) {
        libmark = 248;
        break;
      }
      if (Datastr.indexOf(GENERIC_LINK_LIB_2[i]) != -1) {
        libmark = 247;
        break;
      }
      if (Datastr.indexOf(GENERIC_LINK_LIB_3[i]) != -1) {
        libmark = 246;
        break;
      }
    }
  }

  let Outlen;
  switch (libmark) {
    case 255:
      Outlen = Unishox.unishox2_compress_simple(
        Data,
        Data.byteLength,
        CompressedStrCharArray
      );
      break;
    case 254:
      Outlen = Unishox.unishox2_compress_simple(
        Data,
        Data.byteLength,
        CompressedStrCharArray,
        CHINESE_WEBPAN_LIB
      );
      break;
    case 245:
      Outlen = Unishox.unishox2_compress_simple(
        Data,
        Data.byteLength,
        CompressedStrCharArray,
        INTER_WEBPAN_LIB
      );
      break;
    case 253:
      Outlen = Unishox.unishox2_compress_simple(
        Data,
        Data.byteLength,
        CompressedStrCharArray,
        CHINESE_WEBSITE_LIB
      );
      break;
    case 252:
      Outlen = Unishox.unishox2_compress_simple(
        Data,
        Data.byteLength,
        CompressedStrCharArray,
        INTER_WEBSITE_LIB
      );
      break;
    case 244:
      Outlen = Unishox.unishox2_compress_simple(
        Data,
        Data.byteLength,
        CompressedStrCharArray,
        INTER_WEBSITE_LIB_2
      );
      break;
    case 251:
      Outlen = Unishox.unishox2_compress_simple(
        Data,
        Data.byteLength,
        CompressedStrCharArray,
        JAPAN_WEBSITE_LIB
      );
      break;
    case 250:
      Outlen = Unishox.unishox2_compress_simple(
        Data,
        Data.byteLength,
        CompressedStrCharArray,
        PIRACY_WEBSITE_LIB
      );
      break;
    case 249:
      Outlen = Unishox.unishox2_compress_simple(
        Data,
        Data.byteLength,
        CompressedStrCharArray,
        GENERIC_TLINK_LIB
      );
      break;
    case 248:
      Outlen = Unishox.unishox2_compress_simple(
        Data,
        Data.byteLength,
        CompressedStrCharArray,
        GENERIC_LINK_LIB_1
      );
      break;
    case 247:
      Outlen = Unishox.unishox2_compress_simple(
        Data,
        Data.byteLength,
        CompressedStrCharArray,
        GENERIC_LINK_LIB_2
      );
      break;
    case 246:
      Outlen = Unishox.unishox2_compress_simple(
        Data,
        Data.byteLength,
        CompressedStrCharArray,
        GENERIC_LINK_LIB_3
      );
      break;
  }

  let ResStrCharArray = CompressedStrCharArray.subarray(0, Outlen);
  if (ResStrCharArray.byteLength >= Data.byteLength) {
    return Data;
  }

  let TempArray = new Uint8Array(ResStrCharArray.byteLength + 2);
  TempArray.set(ResStrCharArray, 0);
  TempArray.set([libmark, 255], ResStrCharArray.byteLength);
  ResStrCharArray = TempArray;

  return ResStrCharArray;
}
function UNISHOX_DECOMPRESS(Data) {
  const lastElement = Data[Data.byteLength - 1];
  const secondLastElement = Data[Data.byteLength - 2];

  if (
    lastElement != 255 ||
    secondLastElement < 244 ||
    secondLastElement > 255
  ) {
    return Data;
  }
  let libmark = secondLastElement;
  let NewData = Data.subarray(0, Data.byteLength - 2);

  let DecompressedStrCharArray = new Uint8Array(2048);

  let Outlen;
  switch (libmark) {
    case 255:
      Outlen = Unishox.unishox2_decompress(
        NewData,
        NewData.byteLength,
        DecompressedStrCharArray,
        Unishox.USX_HCODES_DFLT,
        Unishox.USX_HCODE_LENS_DFLT,
        Unishox.USX_FREQ_SEQ_DFLT,
        Unishox.USX_TEMPLATES
      );
      break;
    case 254:
      Outlen = Unishox.unishox2_decompress(
        NewData,
        NewData.byteLength,
        DecompressedStrCharArray,
        Unishox.USX_HCODES_DFLT,
        Unishox.USX_HCODE_LENS_DFLT,
        CHINESE_WEBPAN_LIB,
        Unishox.USX_TEMPLATES
      );
      break;
    case 245:
      Outlen = Unishox.unishox2_decompress(
        NewData,
        NewData.byteLength,
        DecompressedStrCharArray,
        Unishox.USX_HCODES_DFLT,
        Unishox.USX_HCODE_LENS_DFLT,
        INTER_WEBPAN_LIB,
        Unishox.USX_TEMPLATES
      );
      break;
    case 253:
      Outlen = Unishox.unishox2_decompress(
        NewData,
        NewData.byteLength,
        DecompressedStrCharArray,
        Unishox.USX_HCODES_DFLT,
        Unishox.USX_HCODE_LENS_DFLT,
        CHINESE_WEBSITE_LIB,
        Unishox.USX_TEMPLATES
      );
      break;
    case 252:
      Outlen = Unishox.unishox2_decompress(
        NewData,
        NewData.byteLength,
        DecompressedStrCharArray,
        Unishox.USX_HCODES_DFLT,
        Unishox.USX_HCODE_LENS_DFLT,
        INTER_WEBSITE_LIB,
        Unishox.USX_TEMPLATES
      );
      break;
    case 244:
      Outlen = Unishox.unishox2_decompress(
        NewData,
        NewData.byteLength,
        DecompressedStrCharArray,
        Unishox.USX_HCODES_DFLT,
        Unishox.USX_HCODE_LENS_DFLT,
        INTER_WEBSITE_LIB_2,
        Unishox.USX_TEMPLATES
      );
      break;
    case 251:
      Outlen = Unishox.unishox2_decompress(
        NewData,
        NewData.byteLength,
        DecompressedStrCharArray,
        Unishox.USX_HCODES_DFLT,
        Unishox.USX_HCODE_LENS_DFLT,
        JAPAN_WEBSITE_LIB,
        Unishox.USX_TEMPLATES
      );
      break;
    case 250:
      Outlen = Unishox.unishox2_decompress(
        NewData,
        NewData.byteLength,
        DecompressedStrCharArray,
        Unishox.USX_HCODES_DFLT,
        Unishox.USX_HCODE_LENS_DFLT,
        PIRACY_WEBSITE_LIB,
        Unishox.USX_TEMPLATES
      );
      break;
    case 249:
      Outlen = Unishox.unishox2_decompress(
        NewData,
        NewData.byteLength,
        DecompressedStrCharArray,
        Unishox.USX_HCODES_DFLT,
        Unishox.USX_HCODE_LENS_DFLT,
        GENERIC_TLINK_LIB,
        Unishox.USX_TEMPLATES
      );
      break;
    case 248:
      Outlen = Unishox.unishox2_decompress(
        NewData,
        NewData.byteLength,
        DecompressedStrCharArray,
        Unishox.USX_HCODES_DFLT,
        Unishox.USX_HCODE_LENS_DFLT,
        GENERIC_LINK_LIB_1,
        Unishox.USX_TEMPLATES
      );
      break;
    case 247:
      Outlen = Unishox.unishox2_decompress(
        NewData,
        NewData.byteLength,
        DecompressedStrCharArray,
        Unishox.USX_HCODES_DFLT,
        Unishox.USX_HCODE_LENS_DFLT,
        GENERIC_LINK_LIB_2,
        Unishox.USX_TEMPLATES
      );
      break;
    case 246:
      Outlen = Unishox.unishox2_decompress(
        NewData,
        NewData.byteLength,
        DecompressedStrCharArray,
        Unishox.USX_HCODES_DFLT,
        Unishox.USX_HCODE_LENS_DFLT,
        GENERIC_LINK_LIB_3,
        Unishox.USX_TEMPLATES
      );
      break;
  }
  let ResStrCharArray = DecompressedStrCharArray.subarray(0, Outlen);
  return ResStrCharArray;
}

function GetLuhnBit(Data) {
  let Digit = new Array();
  let num, digit;
  for (let i = 0; i < Data.byteLength; i++) {
    num = Data[i];
    while (num > 0) {
      digit = num % 10;
      Digit.push(digit);
      num = Math.floor(num / 10);
    }
  }

  // Digit应当是一个数位构成的数组。
  let sum = 0;
  let Check = 0;

  for (let i = 0; i < Digit.length; i++) {
    if (i % 2 != 0) {
      Digit[i] = Digit[i] * 2;
      if (Digit[i] >= 10) {
        Digit[i] = (Digit[i] % 10) + Math.floor(Digit[i] / 10); //计算数字之和
      }
    }
    sum = sum + Digit[i];
  }

  Check = 10 - (sum % 10);

  return Check;
}

function CheckLuhnBit(Data) {
  let DCheck = Data[Data.byteLength - 1];
  let Check = GetLuhnBit(Data.subarray(0, Data.byteLength - 1));

  if (Check == DCheck) {
    return true;
  } else {
    return false;
  }
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
  let idx1, idx2;
  let idx1_1, idx2_1;
  let idx1_2, idx2_2;

  idx1 = LETTERS.indexOf(keyIn);
  idx2 = NUMBERSYMBOL.indexOf(keyIn);

  idx1_1 = LETTERS.indexOf(LETTERS_ROUND_1[idx1]);
  idx2_1 = NUMBERSYMBOL.indexOf(NUMBERSYMBOL_ROUND_1[idx2]);

  idx1_2 = LETTERS.indexOf(LETTERS_ROUND_2[idx1_1]);
  idx2_2 = NUMBERSYMBOL.indexOf(NUMBERSYMBOL_ROUND_2[idx2_1]);

  if (idx1 != -1) {
    //判断给定字符的类型
    return LETTERS_ROUND_3[idx1_2];
  } else if (idx2 != -1) {
    return NUMBERSYMBOL_ROUND_3[idx2_2];
  }
  return NULL_STR;
}

function DRoundKeyMatch(keyIn) {
  //查询轮换密钥的键值
  let idx1, idx2;
  let idx1_1, idx2_1;
  let idx1_2, idx2_2;

  idx1 = LETTERS_ROUND_3.indexOf(keyIn);
  idx2 = NUMBERSYMBOL_ROUND_3.indexOf(keyIn);

  idx1_1 = LETTERS_ROUND_2.indexOf(LETTERS[idx1]);
  idx2_1 = NUMBERSYMBOL_ROUND_2.indexOf(NUMBERSYMBOL[idx2]);

  idx1_2 = LETTERS_ROUND_1.indexOf(LETTERS[idx1_1]);
  idx2_2 = NUMBERSYMBOL_ROUND_1.indexOf(NUMBERSYMBOL[idx2_1]);

  if (idx1 != -1) {
    //判断给定字符的类型
    return LETTERS[idx1_2];
  } else if (idx2 != -1) {
    return NUMBERSYMBOL[idx2_2];
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
    LETTERS_ROUND_1 = rotateString(LETTERS_ROUND_1, 6); //将第一个密钥轮向右轮6位
    NUMBERSYMBOL_ROUND_1 = rotateString(NUMBERSYMBOL_ROUND_1, 6);

    LETTERS_ROUND_2 = LrotateString(LETTERS_ROUND_2, ControlNum); //将第二个密钥轮向左轮ControlNum*2位
    NUMBERSYMBOL_ROUND_2 = LrotateString(NUMBERSYMBOL_ROUND_2, ControlNum);

    LETTERS_ROUND_3 = rotateString(LETTERS_ROUND_3, ControlNum / 2 + 1); //将第三个密钥轮向右轮ControlNum/2+1位
    NUMBERSYMBOL_ROUND_3 = rotateString(
      NUMBERSYMBOL_ROUND_3,
      ControlNum / 2 + 1
    );
  } else {
    //操作数是奇数
    LETTERS_ROUND_1 = LrotateString(LETTERS_ROUND_1, 3); //将第一个密钥轮向左轮3位
    NUMBERSYMBOL_ROUND_1 = LrotateString(NUMBERSYMBOL_ROUND_1, 3);

    LETTERS_ROUND_2 = rotateString(LETTERS_ROUND_2, ControlNum); //将第二个密钥轮向右轮ControlNum位
    NUMBERSYMBOL_ROUND_2 = rotateString(NUMBERSYMBOL_ROUND_2, ControlNum);

    LETTERS_ROUND_3 = LrotateString(LETTERS_ROUND_3, (ControlNum + 7) / 2); //将第三个密钥轮向左轮(ControlNum+5)/2位
    NUMBERSYMBOL_ROUND_3 = LrotateString(
      NUMBERSYMBOL_ROUND_3,
      (ControlNum + 7) / 2
    );
  }
  RoundFlip++;
}

function RoundReset() {
  RoundFlip = 0;
  RoundControl = new Array(32);
  LETTERS_ROUND_1 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  LETTERS_ROUND_2 = "FbPoDRStyJKAUcdahfVXlqwnOGpHZejzvmrBCigQILxkYMuWTEsN"; //手动随机打乱的乱序轮
  LETTERS_ROUND_3 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  NUMBERSYMBOL_ROUND_1 = "1234567890+/=";
  NUMBERSYMBOL_ROUND_2 = "5=0764+389/12"; //手动随机打乱的乱序轮
  NUMBERSYMBOL_ROUND_3 = "1234567890+/=";
}

function RoundControlInit(key) {
  let KeyHash = CryptoJS.SHA256(key);
  let HashArray = wordArrayToUint8Array(KeyHash);

  RoundControl = HashArray;
}

function distributeInteger(num) {
  if (num <= 3) {
    // 如果 num 小于等于 3，则无法满足每个元素都大于 0 的要求
    return []; // 返回空数组，表示无法分配
  }

  const maxPart = Math.floor(num * 0.2); // 计算每个部分的最大值
  let remaining = num - 2 * maxPart; // 计算剩余部分

  if (remaining <= 0) {
    // 如果剩余部分小于等于 0，则调整最大值，确保每个元素都大于 0
    maxPart = Math.floor((num - 2) / 3); // 调整 maxPart 的计算方式
    remaining = num - 2 * maxPart;

    if (remaining <= 0) {
      return []; // 如果调整后仍然无法满足要求，则返回空数组
    }
  }

  const result = [maxPart, remaining, maxPart]; // 创建包含三个整数的数组

  return result;
}

export class PreCheckResult {
  constructor(output, isEncrypted = false) {
    this.output = output;
    this.isEncrypted = isEncrypted;
  }
}


export function selectSentence(PayloadLength,RandomIndex){ //句式选择算法
  //RandomIndex 随机指数，越大，给出的句式越随机，最大100。
  let selectRand;

  let DividedPayload = distributeInteger(PayloadLength);//把Payload平均分配给三个部分。
  
  let ElementResult = []; //最终要返回的语素序列 

  for(let i=0;i<3;i++){ //第一重循环，选择Payload

    let Payload = DividedPayload[i];
    if(i == 0){ //在Begin句式库中选择。

      for(let a=0 ;a < Payload;){ //第二重循环，用算法选择句式，满足载荷
        selectRand = GetRandomIndex(101) + RandomIndex;
        let PossiblePayload = [];
        for(let b = 1;b < Payload - a;b++){ //三重，求取所有可能载荷。
          if(b == 9){ //最大为9
            PossiblePayload.push(b);
            break;
          }
          PossiblePayload.push(b);
        }
        //这里给出的可能载荷数组应当是从小到大的。
        let TargetPayload;
        if(selectRand <= 100){ //选择贪心最优解
          TargetPayload = PossiblePayload.pop(); //目标Payload，参照这个去库里寻句式。
        }else if(selectRand > 100 && selectRand <= 200){ //随机选择一个，不一定是最优解
          TargetPayload = PossiblePayload[GetRandomIndex(PossiblePayload.length)];
        }

        let PossibleSentences = []; //所有挑选出来的可能句式，选择时任选其一。
        for(let c = 0;c<Map_Obj["Sentences"]["Begin"].length;c++){ //开始选择句式
          let Sentence = Map_Obj["Sentences"]["Begin"][c].split("/"); //Sentence是列表，按照/分割的句式
          if(parseInt(Sentence[0]) == TargetPayload){
            PossibleSentences.push(Sentence.slice(1));
          }
        }

        let TargetSentence = PossibleSentences[GetRandomIndex(PossibleSentences.length)];
        ElementResult.push(TargetSentence);

        a = a + TargetPayload;

      }
    }else if(i == 1){
      for(let a=0 ;a < Payload;){ //第二重循环，用算法选择句式，满足载荷
        selectRand = GetRandomIndex(101) + RandomIndex;
        let PossiblePayload = [];
        for(let b = 1;b < Payload - a;b++){ //三重，求取所有可能载荷。
          if(b == 9){ //最大为9
            PossiblePayload.push(b);
            break;
          }
          PossiblePayload.push(b);
        }
        //这里给出的可能载荷数组应当是从小到大的。
        let TargetPayload;
        if(selectRand <= 100){ //选择贪心最优解
          TargetPayload = PossiblePayload.pop(); //目标Payload，参照这个去库里寻句式。
        }else if(selectRand > 100 && selectRand <= 200){ //随机选择一个，不一定是最优解
          TargetPayload = PossiblePayload[GetRandomIndex(PossiblePayload.length)];
        }

        let PossibleSentences = []; //所有挑选出来的可能句式，选择时任选其一。
        for(let c = 0;c<Map_Obj["Sentences"]["Main"].length;c++){ //开始选择句式
          let Sentence = Map_Obj["Sentences"]["Main"][c].split("/"); //Sentence是列表，按照/分割的句式
          if(parseInt(Sentence[0]) == TargetPayload){
            PossibleSentences.push(Sentence.slice(1));
          }
        }

        let TargetSentence = PossibleSentences[GetRandomIndex(PossibleSentences.length)];
        ElementResult.push(TargetSentence);

        a = a + TargetPayload;
  
      }

    }else if(i == 2){

      for(let a=0 ;a < Payload;){ //第二重循环，用算法选择句式，满足载荷
        selectRand = GetRandomIndex(101) + RandomIndex;
        let PossiblePayload = [];
        for(let b = 1;b < Payload - a;b++){ //三重，求取所有可能载荷。
          if(b == 9){ //最大为9
            PossiblePayload.push(b);
            break;
          }
          PossiblePayload.push(b);
        }
        //这里给出的可能载荷数组应当是从小到大的。
        let TargetPayload;
        if(selectRand <= 100){ //选择贪心最优解
          TargetPayload = PossiblePayload.pop(); //目标Payload，参照这个去库里寻句式。
        }else if(selectRand > 100 && selectRand <= 200){ //随机选择一个，不一定是最优解
          TargetPayload = PossiblePayload[GetRandomIndex(PossiblePayload.length)];
        }

        let PossibleSentences = []; //所有挑选出来的可能句式，选择时任选其一。
        for(let c = 0;c<Map_Obj["Sentences"]["End"].length;c++){ //开始选择句式
          let Sentence = Map_Obj["Sentences"]["End"][c].split("/"); //Sentence是列表，按照/分割的句式
          if(parseInt(Sentence[0]) == TargetPayload){
            PossibleSentences.push(Sentence.slice(1));
          }
        }

        let TargetSentence = PossibleSentences[GetRandomIndex(PossibleSentences.length)];
        ElementResult.push(TargetSentence);

        a = a + TargetPayload;
  
      }

    }
  }

  return ElementResult;
}


/*export function preCheck(inp) {
  let input = String(inp);
  let size = input.length; //第一次遍历字符数组的函数，负责判断给定的输入类型。
  let temp, temp2, group;
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

  if (isJPFound && isCNFound) {
    isEncrypted = true;
  }
  let Result = new PreCheckResult(stringToUint8Array(input), isEncrypted);
  return Result;
}*/

export function enMap(input, key, q) {
  //input.output Uint8Array
  RoundReset();
  RoundControlInit(key);

  let OriginalData = new Uint8Array();
  OriginalData = input.output;
  let TempS;
  TempS = Uint8ArrayTostring(OriginalData);

  let TempArray = new Uint8Array(OriginalData.byteLength + 1);
  TempArray.set(OriginalData, 0);

  TempArray.set([GetLuhnBit(OriginalData)], OriginalData.byteLength);

  OriginalData = TempArray;

  if (OriginalData.byteLength <= 1024) {
    let SizeBefore = OriginalData.byteLength;
    OriginalData = UNISHOX_COMPRESS(OriginalData);

    if (OriginalData.byteLength == SizeBefore) {
      OriginalData = GZIP_COMPRESS(OriginalData);
    }
  } else {
    OriginalData = GZIP_COMPRESS(OriginalData);
  }

  let RandomBytes = new Array();
  RandomBytes.push(GetRandomIndex(256));
  RandomBytes.push(GetRandomIndex(256));

  OriginalData = AES_256_CTR_E(OriginalData, key, RandomBytes);

  TempArray = new Uint8Array(OriginalData.byteLength + 2);
  TempArray.set(OriginalData, 0);
  TempArray.set(RandomBytes, OriginalData.byteLength);
  OriginalData = TempArray;

  let OriginStr = Base64.fromUint8Array(OriginalData);

  let TempStr1 = "",
    temp = "",
    temp2 = "",
    group = "";

  let size = OriginStr.length;

  //从这里开始做文章。。
  
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

  if (q) {
    RoundReset();
    return TempStr1;
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
    if (temp == NULL_STR || temp == " " || temp == "\n" || temp == "\t") {
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
    if (findtemp == NULL_STR) {
      throw "Bad Input. Try force encrypt if intended.";
    }
    TempStr1 = TempStr1 + findtemp; //把找到的原文增加到字符串上
    RoundKey(); //轮换密钥
    i++;
  }
  //到这儿应该能还原出AES加密之后的Base64 TempStr1
  let TempStr2Int = new Uint8Array();
  let RandomBytes = new Array(2);
  if (!Base64.isValid(TempStr1)) {
    throw "Error Decoding. Bad Input or Incorrect Key.";
  }
  try {
    TempStr2Int = Base64.toUint8Array(TempStr1);
    RandomBytes[1] = TempStr2Int.at(TempStr2Int.byteLength - 1);
    RandomBytes[0] = TempStr2Int.at(TempStr2Int.byteLength - 2);

    TempStr2Int = TempStr2Int.subarray(0, TempStr2Int.byteLength - 2);

    TempStr2Int = AES_256_CTR_E(TempStr2Int, key, RandomBytes);
    TempStr2Int = GZIP_DECOMPRESS(TempStr2Int);
    TempStr2Int = UNISHOX_DECOMPRESS(TempStr2Int);
  } catch (err) {
    throw "Error Decoding. Bad Input or Incorrect Key.";
  }

  if (!CheckLuhnBit(TempStr2Int)) {
    if (
      TempStr2Int.at(TempStr2Int.byteLength - 1) == 2 &&
      TempStr2Int.at(TempStr2Int.byteLength - 2) == 2 &&
      TempStr2Int.at(TempStr2Int.byteLength - 3) == 2
    ) {
      TempStr2Int = TempStr2Int.subarray(0, TempStr2Int.byteLength - 3);
    } else {
      throw "Error Decrypting. Checksum Mismatch.";
    }
  } else {
    TempStr2Int = TempStr2Int.subarray(0, TempStr2Int.byteLength - 1);
  }

  //到此，TempStr2Int 就是解密的结果，形式为字节码。
  let Res = new Object();

  Res.output = Uint8ArrayTostring(TempStr2Int);
  Res.output_B = TempStr2Int;

  RoundReset();
  return Res;
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
            Map_Obj["basic"]["alphabet"][RoundKeyMatch(key.toUpperCase())]
              .length
          );
          let s2 = String(
            Map_Obj["basic"]["alphabet"][RoundKeyMatch(key.toUpperCase())][
              RandIndex
            ]
          );
          return s2;
        }
      }
    }
  } else if (idx3 != -1 || idx4 != -1) {
    for (let key in Map_Obj["basic"]["numbersymbol"]) {
      if (Map_Obj["basic"]["numbersymbol"].hasOwnProperty(key)) {
        if (key == letter) {
          RandIndex = GetRandomIndex(
            Map_Obj["basic"]["numbersymbol"][RoundKeyMatch(key)].length
          );
          let s2 =
            Map_Obj["basic"]["numbersymbol"][RoundKeyMatch(key)][RandIndex];
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
  for (let key in Map_Obj["basic"]["alphabet"]) {
    Map_Obj["basic"]["alphabet"][key].forEach((item) => {
      if (letter == item) {
        res = DRoundKeyMatch(key);
      }
    });
  }
  if (res) {
    return res;
  }
  for (let key in Map_Obj["basic"]["numbersymbol"]) {
    Map_Obj["basic"]["numbersymbol"][key].forEach((item) => {
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
