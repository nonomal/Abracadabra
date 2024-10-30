const Map =
  '{"basic":{"alphabet":{"a":["请","上","中","之","等","人","到","年","个","将"],"b":["得","可","并","发","过"],"c":["页","于","而","被","无"],"d":["由","把","好","从","会"],"e":["的","在","了","是","为","有","和","我","一","与"],"f":["站","最","号","及","能"],"g":["着","很","此","但","看"],"h":["名","呢","又","图","啊"],"i":["对","地","您","给","这","下","网","也","来","你"],"j":["更","天","去","用","只"],"k":["第","者","所","两","里"],"l":["自","做","前","二","他"],"m":["家","点","路","至","十"],"n":["区","想","向","主","四"],"o":["就","新","吗","该","不","多","还","要","让","大"],"p":["小","如","成","位","其"],"q":["吧","每","机","几","总"],"r":["起","它","内","高","次"],"s":["非","元","类","五","使"],"t":["首","进","即","没","市"],"u":["后","三","本","都","时","月","或","说","已","以"],"v":["种","快","那","篇","万"],"w":["长","按","报","比","信"],"x":["再","带","才","全","呀"],"y":["业","却","版","美","们"],"z":["像","走","文","各","当"]},"number":{"0":["卡","风","水","放","花"],"1":["需","头","话","曾","楼"],"2":["连","系","门","力","量"],"3":["书","亿","跟","深","方"],"4":["若","低","谈","明","百"],"5":["关","客","读","双","回"],"6":["较","品","嘛","单","价"],"7":["山","西","动","厂","热"],"8":["言","笑","度","易","身"],"9":["份","星","千","仍","办"]},"symbol":{"+":["集","费","传","室","拉","瑞","琴","森","辉"],"/":["难","界","指","管","具","善","智","蔬","缎"],"?":["相","儿","李","早","拿"],"-":["科","白","段","飞","住"],".":["利","红","板","光","约"],"(":["变","款","林","夹","院"],")":["服","句","声","务","游"],"[":["股","南","社","阿","远"],"]":["意","换","些","必","赛"],"<":["届","完","乐","彩","讲"],">":["展","帮","且","物","班"],",":["何","流","密","某","房"],"|":["语","亚","常","除","装"],"=":["极","载","题","刚","气","程","舒","雅","益"],"@":["米","影","德","世","坐"],"#":["北","招","短","活","斯"],"!":["值","店","树","哪","余"],"~":["盘","速","座","求","创"],"`":["梦","足","半","视","安"],"$":["空","歌","派","顶","登"],"%":["夜","云","感","啦","欲"],"^":["边","工","眼","街","奖"],"&":["获","占","理","任","实"],"*":["知","掉","色","讯","克"],"_":["直","评","往","层","园"],"{":["留","靠","亦","罗","营"],"}":["合","尚","产","诚","汨"],":":["曱","朩","杉","杸","歩"],";":["毋","氕","気","氘","氙"]," ":["叧","叺","叻","叾","吅","叿","吙","呡","呤","呮","呭","呾","呟","吂","吤"],"\\t":["圠","圡","圢","圤","圥","圦","坆","夨","夨","夬","夳","夶","奀","夻","夼"],"\\n":["孒","孖","尐","尛","尢","尣","巛","巜","幷","弐","彑","彡","彳","忄","扖"]}},"link":{"http":["贴","则","老","生","达"],"://":["商","行","周","证","经"],"magnet":["事","场","同","化","找"],"udp":["建","手","道","间","式"],"tcp":["特","城","型","定","接"],"ftp":["局","问","重","叫","通"],":?xt=urn:btih:":["件","少","面","金","近"],"torrent":["买","听","学","见","称"],"www":["写","选","片","体","组"],"mailto":["先","仅","别","表","现"]},"special":{"BIG":["未","哦","部","项","谁","分","转","字","数","心","子","处","作","因","设","环","青","雨","泊","注","织","赴","茶"],"TYPE":{"LINK":["应畑","的凪","开辺","录込","飞飴","应仮","的実","开雫","录気","飞抜","应杁"],"NORMAL":["钟込","均桜","错桜","妳桜","钟飴","均仮","错実","妳雫","钟気","均抜","错杁"],"BASE64":["奂込","妍桜","姾凪","娂辺","奂飴","妍仮","姾実","娂雫","奂気","妍抜","姾杁"],"DECRYPT":["飞込","电桜","亖凪","冇辺","亖飴","电仮","飞実","冇雫","亖気","电抜","飞杁"]}}}';

const Normal_Characters =
  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+=_-/?.>,<|`~!@#$%^&*(){}[];: \n\t1234567890"; //表内有映射的所有字符组成的字符串
const LETTERS = "abcdefghijklmnopqrstuvwxyz";
const BIG_LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const NUMBERS = "1234567890";
const SYMBOLS = "+=_-/?.>,<|`~!@#$%^&*(){}[];: \n\t";
const SIG_LINK = "应畑,的凪,开辺,录込,飞飴,应仮,的実,开雫,录気,飞抜,应杁"; //链接类型的标志位列表
const SIG_NORMAL = "钟込,均桜,错桜,妳桜,钟飴,均仮,错実,妳雫,钟気,均抜,错杁"; //普通类型的标志位列表
const SIG_BASE64 = "奂込,妍桜,姾凪,娂辺,奂飴,妍仮,姾実,娂雫,奂気,妍抜,姾杁"; //Base64类型的标志位列表
const SIG_DECRYPT = "飞込,电桜,亖凪,冇辺,亖飴,电仮,飞実,冇雫,亖気,电抜,飞杁"; //加密字符串的标志位列表
const NULL_STR = "孎"; //默认忽略的占位字符，一个生僻字。

const Map_Obj = JSON.parse(Map);

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

export class PreCheckResult {
  constructor(
    output,
    isUnNormal = false,
    isLink = false,
    isNormal = false,
    isBase64 = false,
    isEncrypted = false
  ) {
    this.output = output;
    this.isUnNormal = isUnNormal;
    this.isLink = isLink;
    this.isNormal = isNormal;
    this.isBase64 = isBase64;
    this.isEncrypted = isEncrypted;
  }
}

export function preCheck(inp) {
  let input = String(inp);
  let size = input.length; //第一次遍历字符数组的函数，负责判断给定的输入类型。
  let temp, temp2, group;
  let isUnNormal = false; // 判断是否含有特殊符号(表外内容)
  let isLink = false;
  let isNormal = false; //如果检查出这个标志位，则默认是未经Base64处理后加密的密文
  let isBase64 = false;
  let isEncrypted = false; //如果检查出这个标志位，那么默认这是一串加密之后的密文
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
      if (SIG_LINK.indexOf(group) != -1) {
        input = setCharOnIndex(input, i, NULL_STR);
        input = setCharOnIndex(input, i + 1, NULL_STR);
        isLink = true;
        continue;
      }
      if (SIG_NORMAL.indexOf(group) != -1) {
        input = setCharOnIndex(input, i, NULL_STR);
        input = setCharOnIndex(input, i + 1, NULL_STR);
        isNormal = true;
        continue;
      }
      if (SIG_BASE64.indexOf(group) != -1) {
        input = setCharOnIndex(input, i, NULL_STR);
        input = setCharOnIndex(input, i + 1, NULL_STR);
        isBase64 = true;
        continue;
      }
      if (SIG_DECRYPT.indexOf(group) != -1) {
        input = setCharOnIndex(input, i, NULL_STR);
        input = setCharOnIndex(input, i + 1, NULL_STR);
        isEncrypted = true;
        continue;
      }
    }
  }
  let Result = new PreCheckResult(
    input,
    isUnNormal,
    isLink,
    isNormal,
    isBase64,
    isEncrypted
  );

  return Result;
}

export function enMap(input, forceLink, forceBase64, forceDirect, isfile) {
  let OriginStr = String(input.output);
  let TempStr1 = "",
    temp = "",
    temp2 = "",
    group = "";

  if (input.isUnNormal && forceDirect) {
    //如果给定的字符串包括特殊字符且指定不处理特殊字符，解决矛盾
    forceDirect = false;
    forceLink = false;
    forceBase64 = true;
  }
  if (forceLink) {
    //链接模式前置URLencode处理
    OriginStr = getLinkCryptText(encodeURI(input.output));
  } else if (forceBase64) {
    //Base64模式前置base64处理
    OriginStr = btoa(input.output); //注意，这里传进来的必须是字符串而不是Buffer
  } else if (input.isUnNormal) {
    //包含特殊字符，默认Base64
    OriginStr = btoa(input.output);
    forceBase64 = true;
  }
  if (isfile) {
    forceBase64 = true;
  }

  let size = OriginStr.length;
  for (let i = 0; i < size; i++) {
    temp = OriginStr[i];
    if (i != size - 1) {
      //一次遍历两个字符，遇到倒数第一个的时候防止越界
      temp2 = OriginStr[i + 1];
    } else {
      temp2 = NULL_STR;
    }
    group = temp + temp2;
    if (Normal_Characters.indexOf(temp) == -1) {
      //如果在表内找不到某个字符
      TempStr1 = TempStr1 + temp; //把这个字符加到结果字符串的后面
      continue; //直接跳过
    }
    TempStr1 = TempStr1 + getCryptText(temp); //把加密字符加到结果字符串的后面
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
      //第一次大循环插入模式标志位
      RandIndex = PosToInset[GetRandomIndex(PosToInset.length)];
      if (forceDirect) {
        //无处理特殊字符标志位
        RandIndex2 = GetRandomIndex(
          Map_Obj["special"]["TYPE"]["NORMAL"].length
        );
        let stemp = Map_Obj["special"]["TYPE"]["NORMAL"][RandIndex2];
        TempStr1 = insertStringAtIndex(TempStr1, stemp, RandIndex);
        for (let z = RandIndex + 1; z < RandIndex + stemp.length; z++) {
          Avoid.push(z);
        }
      } else if (forceLink) {
        //链接模式标志位
        RandIndex2 = GetRandomIndex(Map_Obj["special"]["TYPE"]["LINK"].length);
        let stemp = Map_Obj["special"]["TYPE"]["LINK"][RandIndex2];
        TempStr1 = insertStringAtIndex(TempStr1, stemp, RandIndex);
        for (let z = RandIndex + 1; z < RandIndex + stemp.length; z++) {
          Avoid.push(z);
        }
      } else if (forceBase64) {
        //Base64模式标志位
        RandIndex2 = GetRandomIndex(
          Map_Obj["special"]["TYPE"]["BASE64"].length
        );
        let stemp = Map_Obj["special"]["TYPE"]["BASE64"][RandIndex2];
        TempStr1 = insertStringAtIndex(TempStr1, stemp, RandIndex);
        for (let z = RandIndex + 1; z < RandIndex + stemp.length; z++) {
          Avoid.push(z);
        }
      }
    } else if (q == 1) {
      let AvailPos = new Array();
      AvailPos = difference(PosToInset, Avoid);

      RandIndex = AvailPos[GetRandomIndex(AvailPos.length)];
      RandIndex2 = GetRandomIndex(Map_Obj["special"]["TYPE"]["DECRYPT"].length);
      TempStr1 = insertStringAtIndex(
        TempStr1,
        Map_Obj["special"]["TYPE"]["DECRYPT"][RandIndex2],
        RandIndex
      );
    }
  }
  return TempStr1;
}

export function deMap() {}

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
          RandIndex = GetRandomIndex(Map_Obj["basic"]["alphabet"][key].length);
          let s2 = Map_Obj["basic"]["alphabet"][key][RandIndex];
          return s2;
        } else if (key.toUpperCase() == letter) {
          RandIndex = GetRandomIndex(Map_Obj["basic"]["alphabet"][key].length);
          let s2 = String(Map_Obj["basic"]["alphabet"][key][RandIndex]);

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
          RandIndex = GetRandomIndex(Map_Obj["basic"]["number"][key].length);
          let s2 = Map_Obj["basic"]["number"][key][RandIndex];
          return s2;
        }
      }
    }
  } else if (idx4 != -1) {
    for (let key in Map_Obj["basic"]["symbol"]) {
      if (Map_Obj["basic"]["symbol"].hasOwnProperty(key)) {
        if (key == letter) {
          RandIndex = GetRandomIndex(Map_Obj["basic"]["symbol"][key].length);
          let s2 = Map_Obj["basic"]["symbol"][key][RandIndex];
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
  for (let key in Map_Obj["basic"]["alphabet"]) {
    Map_Obj["basic"]["alphabet"][key].forEach((item) => {
      if (letter == item) {
        res = key;
      }
    });
  }
  for (let key in Map_Obj["basic"]["number"]) {
    Map_Obj["basic"]["number"][key].forEach((item) => {
      if (letter == item) {
        res = key;
      }
    });
  }
  for (let key in Map_Obj["basic"]["symbol"]) {
    Map_Obj["basic"]["symbol"][key].forEach((item) => {
      if (letter == item) {
        res = key;
      }
    });
  }
  for (let key in Map_Obj["link"]) {
    Map_Obj["link"][key].forEach((item) => {
      if (letter == item) {
        res = key;
      }
    });
  }
  if (res2) {
    return res2;
  } else if (res) {
    return res;
  } else {
    return NULL_STR;
  }
}
