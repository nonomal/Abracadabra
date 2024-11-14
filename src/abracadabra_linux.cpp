#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <codecvt>
#include <random>
#include <ctime>
#include <cstdint>
#include <iomanip>
#include <sstream>

#include <nlohmann/json.hpp>
#include <cppcodec/base64_rfc4648.hpp>
#include <CLI11.hpp>
#include <tinyaes/aes.hpp>
#include <tinyaes/aes.c>
#include <picosha2.h>

using namespace std;
using json = nlohmann::json;
using base64 = cppcodec::base64_rfc4648;

const string Map = "{\"basic\":{\"alphabet\":{\"a\":[\"请\",\"上\",\"中\",\"之\",\"等\",\"人\",\"到\",\"年\",\"个\",\"将\"],\"b\":[\"得\",\"可\",\"并\",\"发\",\"过\",\"协\",\"曲\",\"闭\",\"斋\",\"峦\"],\"c\":[\"页\",\"于\",\"而\",\"被\",\"无\",\"挽\",\"裕\",\"斜\",\"绪\",\"镜\"],\"d\":[\"由\",\"把\",\"好\",\"从\",\"会\",\"帕\",\"莹\",\"盈\",\"敬\",\"粒\"],\"e\":[\"的\",\"在\",\"了\",\"是\",\"为\",\"有\",\"和\",\"我\",\"一\",\"与\"],\"f\":[\"站\",\"最\",\"号\",\"及\",\"能\",\"迟\",\"鸭\",\"呈\",\"玻\",\"据\"],\"g\":[\"着\",\"很\",\"此\",\"但\",\"看\",\"浩\",\"附\",\"侃\",\"汐\",\"绸\"],\"h\":[\"名\",\"呢\",\"又\",\"图\",\"啊\",\"棉\",\"畅\",\"蒸\",\"玫\",\"添\"],\"i\":[\"对\",\"地\",\"您\",\"给\",\"这\",\"下\",\"网\",\"也\",\"来\",\"你\"],\"j\":[\"更\",\"天\",\"去\",\"用\",\"只\",\"矽\",\"萌\",\"镁\",\"芯\",\"夸\"],\"k\":[\"第\",\"者\",\"所\",\"两\",\"里\",\"氢\",\"羟\",\"纽\",\"夏\",\"春\"],\"l\":[\"自\",\"做\",\"前\",\"二\",\"他\",\"氦\",\"汀\",\"兰\",\"竹\",\"捷\"],\"m\":[\"家\",\"点\",\"路\",\"至\",\"十\",\"锂\",\"羧\",\"暑\",\"夕\",\"振\"],\"n\":[\"区\",\"想\",\"向\",\"主\",\"四\",\"铍\",\"烃\",\"惠\",\"芳\",\"岩\"],\"o\":[\"就\",\"新\",\"吗\",\"该\",\"不\",\"多\",\"还\",\"要\",\"让\",\"大\"],\"p\":[\"小\",\"如\",\"成\",\"位\",\"其\",\"硼\",\"酞\",\"褔\",\"苑\",\"笋\"],\"q\":[\"吧\",\"每\",\"机\",\"几\",\"总\",\"碳\",\"铂\",\"涓\",\"绣\",\"悦\"],\"r\":[\"起\",\"它\",\"内\",\"高\",\"次\",\"氮\",\"铵\",\"奏\",\"鲤\",\"淳\"],\"s\":[\"非\",\"元\",\"类\",\"五\",\"使\",\"氧\",\"醇\",\"迷\",\"霁\",\"琅\"],\"t\":[\"首\",\"进\",\"即\",\"没\",\"市\",\"氖\",\"酯\",\"琳\",\"绫\",\"濑\"],\"u\":[\"后\",\"三\",\"本\",\"都\",\"时\",\"月\",\"或\",\"说\",\"已\",\"以\"],\"v\":[\"种\",\"快\",\"那\",\"篇\",\"万\",\"钠\",\"炔\",\"柯\",\"睿\",\"琼\"],\"w\":[\"长\",\"按\",\"报\",\"比\",\"信\",\"硅\",\"烷\",\"静\",\"欣\",\"束\"],\"x\":[\"再\",\"带\",\"才\",\"全\",\"呀\",\"磷\",\"烯\",\"柔\",\"雪\",\"冰\"],\"y\":[\"业\",\"却\",\"版\",\"美\",\"们\",\"硫\",\"桉\",\"寒\",\"冻\",\"玖\"],\"z\":[\"像\",\"走\",\"文\",\"各\",\"当\",\"氯\",\"缬\",\"妃\",\"琉\",\"璃\"]},\"number\":{\"0\":[\"卡\",\"风\",\"水\",\"放\",\"花\",\"钾\",\"宏\",\"谊\",\"探\",\"棋\"],\"1\":[\"需\",\"头\",\"话\",\"曾\",\"楼\",\"钙\",\"吾\",\"恋\",\"菲\",\"遥\"],\"2\":[\"连\",\"系\",\"门\",\"力\",\"量\",\"钛\",\"苗\",\"氛\",\"鹤\",\"雀\"],\"3\":[\"书\",\"亿\",\"跟\",\"深\",\"方\",\"钒\",\"鸳\",\"鸯\",\"纸\",\"鸢\"],\"4\":[\"若\",\"低\",\"谈\",\"明\",\"百\",\"铬\",\"羯\",\"尧\",\"舜\",\"兆\"],\"5\":[\"关\",\"客\",\"读\",\"双\",\"回\",\"锰\",\"熙\",\"瀚\",\"渊\",\"灯\"],\"6\":[\"较\",\"品\",\"嘛\",\"单\",\"价\",\"钴\",\"阑\",\"珊\",\"雁\",\"鹂\"],\"7\":[\"山\",\"西\",\"动\",\"厂\",\"热\",\"锌\",\"鹃\",\"鸠\",\"昆\",\"仑\"],\"8\":[\"言\",\"笑\",\"度\",\"易\",\"身\",\"镓\",\"乾\",\"坤\",\"澈\",\"饺\"],\"9\":[\"份\",\"星\",\"千\",\"仍\",\"办\",\"锗\",\"彗\",\"聪\",\"慧\",\"磋\"]},\"symbol\":{\"+\":[\"集\",\"费\",\"传\",\"室\",\"拉\",\"瑞\",\"琴\",\"森\",\"辉\"],\"/\":[\"难\",\"界\",\"指\",\"管\",\"具\",\"善\",\"智\",\"蔬\",\"缎\"],\"?\":[\"相\",\"儿\",\"李\",\"早\",\"拿\"],\"-\":[\"科\",\"白\",\"段\",\"飞\",\"住\"],\".\":[\"利\",\"红\",\"板\",\"光\",\"约\"],\"(\":[\"变\",\"款\",\"林\",\"夹\",\"院\"],\")\":[\"服\",\"句\",\"声\",\"务\",\"游\"],\"[\":[\"股\",\"南\",\"社\",\"阿\",\"远\"],\"]\":[\"意\",\"换\",\"些\",\"必\",\"赛\"],\"<\":[\"届\",\"完\",\"乐\",\"彩\",\"讲\"],\">\":[\"展\",\"帮\",\"且\",\"物\",\"班\"],\",\":[\"何\",\"流\",\"密\",\"某\",\"房\"],\"|\":[\"语\",\"亚\",\"常\",\"除\",\"装\"],\"=\":[\"极\",\"载\",\"题\",\"刚\",\"气\",\"程\",\"舒\",\"雅\",\"益\"],\"@\":[\"米\",\"影\",\"德\",\"世\",\"坐\"],\"#\":[\"北\",\"招\",\"短\",\"活\",\"斯\"],\"!\":[\"值\",\"店\",\"树\",\"哪\",\"余\"],\"~\":[\"盘\",\"速\",\"座\",\"求\",\"创\"],\"`\":[\"梦\",\"足\",\"半\",\"视\",\"安\"],\"$\":[\"空\",\"歌\",\"派\",\"顶\",\"登\"],\"%\":[\"夜\",\"云\",\"感\",\"啦\",\"欲\"],\"^\":[\"边\",\"工\",\"眼\",\"街\",\"奖\"],\"&\":[\"获\",\"占\",\"理\",\"任\",\"实\"],\"*\":[\"知\",\"掉\",\"色\",\"讯\",\"克\"],\"_\":[\"直\",\"评\",\"往\",\"层\",\"园\"],\"{\":[\"留\",\"靠\",\"亦\",\"罗\",\"营\"],\"}\":[\"合\",\"尚\",\"产\",\"诚\",\"汨\"],\":\":[\"曱\",\"朩\",\"杉\",\"杸\",\"歩\"],\";\":[\"毋\",\"氕\",\"気\",\"氘\",\"氙\"],\" \":[\"叧\",\"叺\",\"叻\",\"叾\",\"吅\",\"叿\",\"吙\",\"呡\",\"呤\",\"呮\",\"呭\",\"呾\",\"呟\",\"吂\",\"吤\"],\"\\t\":[\"圠\",\"圡\",\"圢\",\"圤\",\"圥\",\"圦\",\"坆\",\"夨\",\"夨\",\"夬\",\"夳\",\"夶\",\"奀\",\"夻\",\"夼\"],\"\\n\":[\"孒\",\"孖\",\"尐\",\"尛\",\"尢\",\"尣\",\"巛\",\"巜\",\"幷\",\"弐\",\"彑\",\"彡\",\"彳\",\"忄\",\"扖\"]}},\"link\":{\"http\":[\"贴\",\"则\",\"老\",\"生\",\"达\"],\"://\":[\"商\",\"行\",\"周\",\"证\",\"经\"],\"magnet\":[\"事\",\"场\",\"同\",\"化\",\"找\"],\"udp\":[\"建\",\"手\",\"道\",\"间\",\"式\"],\"tcp\":[\"特\",\"城\",\"型\",\"定\",\"接\"],\"ftp\":[\"局\",\"问\",\"重\",\"叫\",\"通\"],\":?xt=urn:btih:\":[\"件\",\"少\",\"面\",\"金\",\"近\"],\"torrent\":[\"买\",\"听\",\"学\",\"见\",\"称\"],\"www\":[\"写\",\"选\",\"片\",\"体\",\"组\"],\"mailto\":[\"先\",\"仅\",\"别\",\"表\",\"现\"]},\"special\":{\"BIG\":[\"未\",\"哦\",\"部\",\"项\",\"谁\",\"分\",\"转\",\"字\",\"数\",\"心\",\"子\",\"处\",\"作\",\"因\",\"设\",\"环\",\"青\",\"雨\",\"泊\",\"注\",\"织\",\"赴\",\"茶\"],\"DECRYPT\":{\"JP\":[\"桜\",\"込\",\"凪\",\"雫\",\"実\",\"沢\"],\"CN\":[\"汢\",\"垈\",\"玊\",\"欤\",\"瞐\",\"囧\"]}}}"; //字符串映射表
const json Map_Obj = json::parse(Map); //JSON字符串映射表对象

int RoundFlip = 0; //标志现在到哪了
uint8_t RoundControl[32]; //一个数组，用密钥哈希来控制轮转的行为
const string Normal_Characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+=_-/?.>,<|`~!@#$%^&*(){}[];: \n\t1234567890"; //表内有映射的所有字符组成的字符串
const string LETTERS = "abcdefghijklmnopqrstuvwxyz";
string LETTERS_ROUND_1 = "abcdefghijklmnopqrstuvwxyz";
string LETTERS_ROUND_2 = "abcdefghijklmnopqrstuvwxyz";
string LETTERS_ROUND_3 = "abcdefghijklmnopqrstuvwxyz";
const string BIG_LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string NUMBERS = "1234567890";
string NUMBERS_ROUND_1 = "1234567890";
string NUMBERS_ROUND_2 = "1234567890";
string NUMBERS_ROUND_3 = "1234567890";
const string SYMBOLS = "+=_-/?.>,<|`~!@#$%^&*(){}[];: \n\t";
string SYMBOLS_ROUND_1 = "+=_-/?.>,<|`~!@#$%^&*(){}[];: \n\t";
string SYMBOLS_ROUND_2 = "+=_-/?.>,<|`~!@#$%^&*(){}[];: \n\t";
string SYMBOLS_ROUND_3 = "+=_-/?.>,<|`~!@#$%^&*(){}[];: \n\t";

const string SIG_DECRYPT_JP = "桜込凪雫実沢";
const string SIG_DECRYPT_CN = "汢垈玊欤瞐囧";
const string NULL_STR = "孎"; //默认忽略的占位字符，一个生僻字。

random_device rd;
mt19937 generator(rd());
uniform_int_distribution<int> distribution(0, 10000);

struct PreCheckResult { // 专门用来打包传递预检的结果
    vector<uint8_t> output;
    bool isUnNormal = false; // 判断是否含有特殊符号(表外内容)
    bool isEncrypted = false;
};

struct DemapResult { // 专门用来打包解密的结果
    string output;
    vector<uint8_t> output_B;
};


string enMap(PreCheckResult input,bool l,string key);
DemapResult deMap(PreCheckResult input,string key,bool g);
string FindOriginText(string letter);
string GetCryptedText(string letter);
string GetLinkCryptedText(string text);
string FindLinkOrigin(string letter);
int GetRandomIndex(int length);
string UrlEncode(const string& szToEncode);
std::string GbkToUtf8(const char* src_str);
std::vector<uint8_t> readFile(const char* filename);
PreCheckResult preCheck(vector<uint8_t> Input);
void rotateString(std::string& str);
void LrotateString(std::string& str);
inline string RoundKeyMatch(string keyIn);
inline string DRoundKeyMatch(string keyIn);
inline void RoundKey();

std::vector<uint8_t> String2Uint8T(const std::string& str);
std::vector<uint8_t> AES_256_CTR(string key,vector<uint8_t> data);
vector<uint8_t> SHA256(vector<uint8_t> data);


int main(int argc, char *argv[]){
    CLI::App app{"***Abracadabra v1.2.0***"}; //CLI11提供的命令行参数解析

    string arg1 = "";
    PreCheckResult input;
    bool l = false,e = false, d = false,g = false;
    string f = NULL_STR,o = NULL_STR,i = NULL_STR,i2 = NULL_STR,k = "ABRACADABRA";//给定的文件路径和输入
    string::size_type idx; 
    ofstream outfile;
    vector<uint8_t> inputfiledata;

    //定义命令行参数
    CLI::Option* i2flag = app.add_option("DEFAULT", i2, "Input text, if there is no given option besides.");
    CLI::Option* lflag = app.add_flag("-l", l, "Force to encrypt using url mode.");
    CLI::Option* eflag = app.add_flag("-e", e, "Force to encrypt normally.");
    CLI::Option* dflag = app.add_flag("-d", d, "Force to decrypt the given input.");
    CLI::Option* gflag = app.add_flag("-g", g, "Ignore any data checks.");
    CLI::Option* fflag = app.add_option("-f", f, "Input an arbitrary given file.");
    CLI::Option* oflag = app.add_option("-o", o, "Declare an output file to save the result.");
    CLI::Option* iflag = app.add_option("-i", i, "Input text, expected if -f is not used.");
    CLI::Option* kflag = app.add_option("-k", k, "Key to encrypt, ABRACADABRA in default.");

    i2flag
        ->take_last()
        ->excludes("-d")
        ->excludes("-e")
        ->excludes("-f")
        ->excludes("-l")
        ->excludes("-i");
    lflag
        ->take_last()
        ->excludes("-d")
        ->excludes("-e");
    dflag
        ->take_last()
        ->excludes("-l")
        ->excludes("-e");
    eflag
        ->take_last()
        ->excludes("-d")
        ->excludes("-l");
    fflag
        ->take_last()
        ->excludes("-i");
    oflag
        ->take_last();
    iflag
        ->take_last()
        ->excludes("-f");
    kflag
        ->take_last();
    try{
        CLI11_PARSE(app, argc, argv);
    }catch(...){
        cout<<"Your Command is not valid."<<endl;
        cout<<"Run with --help for more information."<<endl;
        return 0;
    }

    vector<uint8_t> KeyHashVec = SHA256(String2Uint8T(GbkToUtf8(k.c_str())));
    for(int i=0;i<32;i++){
        RoundControl[i] = KeyHashVec[i];
    }

    //这里处理所有输入的逻辑
    if (i2 != NULL_STR){//如果i2存在，即只有一个参数
        PreCheckResult Result;
        Result = preCheck(String2Uint8T(i2.c_str()));
        if(Result.isEncrypted){
            d = true;
        }
        input = Result;
    }else{
        if(i != NULL_STR){
            input = preCheck(String2Uint8T(i.c_str()));
            if(input.isEncrypted){
                d = true;
            }
        }else if(f != NULL_STR){ //指定了输入文件
            try{
                inputfiledata = readFile(f.c_str()); //读取文件，进行几次编码/类型转换
            }catch(...){
                cout<<"Error Reading File."<<endl;
                cout<<"Check your command and try again."<<endl;
                return 0;
            }
            //string RawStr(inputfiledata.begin(),inputfiledata.end()); 
            input = preCheck(inputfiledata);//预检
            if(input.isEncrypted){ //如果给定的是一个任意二进制文件，预处理函数默认将其视为字符串对待，虽然强行输出绝对是乱码。
                d = true;
            }//如果Precheck找不到标志位，那么这个文件被当作任意二进制
        }else{
            cout<<"Your Command is not valid."<<endl;
            cout<<"Run with --help for more information."<<endl;
            return 0;
        }
    }

    string Process_res; //变量用来存储处理结束后的对象
    DemapResult Res;
    vector<uint8_t> OutputData;

    if(!d || l || e){
        Process_res = enMap(input,l,k);
    }else{
        //尝试解密
        Res = deMap(input,k,g); //如果输入的是文件，解密后的“字符串”未必是字符串，只是类字符数组，若不指定输出路径，直接命令行输出必乱码
        Process_res = Res.output;
        OutputData = Res.output_B;
    }

    if(o != NULL_STR){ //如果指定了输出文件
        try{
            outfile.open(o.c_str(), ios::out | ios::trunc | ios::binary);
        }catch(...){
            cout<<"Error Creating/Openning Output File."<<endl;
            cout<<"Check your command and try again."<<endl;
            return 0;
        }
        if(OutputData.size() != 0){ //有字节码就直接写出字节码
             outfile.write(reinterpret_cast<const char*>(OutputData.data()),OutputData.size()); //输出到文件
        }else{ //没字节码才写字符串
            outfile<<Process_res;
        }
       
    }else{//如果没有指定输出，那么直接输出到命令行
        cout<<Process_res<<endl;
    }

    return 0;
}


PreCheckResult preCheck(vector<uint8_t> Input){
    string input(Input.begin(),Input.end());
    int size = input.length(); //第一次遍历字符数组的函数，负责判断给定的输入类型。
    string temp;
    string::size_type idx; 
    bool isUnNormal = false; // 判断是否含有特殊符号(表外内容)
    bool isEncrypted = false;//判定该文本是否为加密文本

    bool isJPFound = false;//如果检查出一个日语标志位，则标记为真
    bool isCNFound = false;//如果检查出一个汉字标志位，则标记为真
    for(int i=0;i<size;){

        int cplen = 1; //该死的C++，处理中文字符贼繁琐
        if((input[i] & 0xf8) == 0xf0) cplen = 4;
        else if((input[i] & 0xf0) == 0xe0) cplen = 3;
        else if((input[i] & 0xe0) == 0xc0) cplen = 2;
        if((i + cplen) > input.length()) cplen = 1;
        temp = input.substr(i, cplen);

        idx = Normal_Characters.find(temp);
        if (idx == string::npos){ //如果在表内找不到某个字符
            isUnNormal = true; //判断含有特殊符号

            //判断这个符号是不是标识符，标识符用空字符进行占位操作
            if(temp.length()<3){
               i += cplen;
               continue;
            }
            if(SIG_DECRYPT_JP.find(temp) != string::npos){

               input.replace(i, cplen ,NULL_STR);
               isJPFound = true;
               i += cplen;
               continue;
            }
            if(SIG_DECRYPT_CN.find(temp) != string::npos){

               input.replace(i, cplen ,NULL_STR);
               isCNFound = true;
               i += cplen;
               continue;
            }
        }
        i += cplen;
    }

    PreCheckResult Result;
    if(isJPFound&&isCNFound){
        isEncrypted=true;
        Result.output = String2Uint8T(input);
    }else{
        Result.output = Input;
    }
    Result.isUnNormal = isUnNormal;
    Result.isEncrypted = isEncrypted;
    return Result;
}
string enMap(PreCheckResult input,bool l,string key){

    vector<uint8_t> OriginalData = input.output;
    string TempS(input.output.begin(),input.output.end());

    if(l){ //链接模式先进行urlencode,再代换，再换回字节数组
      OriginalData = String2Uint8T(GetLinkCryptedText(UrlEncode(TempS)));
      OriginalData.push_back(1); //在末尾加入三个字节的标志位 111
      OriginalData.push_back(1);
      OriginalData.push_back(1);
    }else{
      OriginalData.push_back(2); //在末尾加入三个字节的标志位 222
      OriginalData.push_back(2);
      OriginalData.push_back(2);
    }

    OriginalData = AES_256_CTR(key,OriginalData); //AES加密
    string OriginStr = base64::encode(OriginalData); //用Base64编码AES的加密结果

    string TempStr1;
    string temp,temp2,group;
    string::size_type idx; 
    int size = OriginStr.length();

    for(int i=0;i<size;){
        int cplen = 1; //该死的C++，处理中文字符贼繁琐
        if((OriginStr[i] & 0xf8) == 0xf0) cplen = 4;
        else if((OriginStr[i] & 0xf0) == 0xe0) cplen = 3;
        else if((OriginStr[i] & 0xe0) == 0xc0) cplen = 2;
        if((i + cplen) > OriginStr.length()) cplen = 1;
        temp = OriginStr.substr(i, cplen);

        //加密操作开始
        //把加密字符加到结果字符串的后面
        TempStr1.append(GetCryptedText(temp));
        RoundKey();

        i += cplen;
    }
    //第一个循环结束后，TempStr1应当是完全的密文，但是缺少标志位

    int RandIndex,RandIndex2;
    vector<int> Avoid;
    for(int q=0;q<2;q++){//分两次大循环
        vector<int> PosToInset;
        size = TempStr1.length();
        for(int i=0;i<size;){ //这里需要确定所有插入UTF-8字符的合适位置
            int cplen = 1; //该死的C++，处理中文字符贼繁琐
            int cplen2 = 1;
            if((TempStr1[i] & 0xf8) == 0xf0) cplen = 4;
            else if((TempStr1[i] & 0xf0) == 0xe0) cplen = 3;
            else if((TempStr1[i] & 0xe0) == 0xc0) cplen = 2;
            if((i + cplen) > TempStr1.length()) cplen = 1;

            if((TempStr1[i+cplen] & 0xf8) == 0xf0) cplen2 = 4;
            else if((TempStr1[i+cplen] & 0xf0) == 0xe0) cplen2 = 3;
            else if((TempStr1[i+cplen] & 0xe0) == 0xc0) cplen2 = 2;
            if((i + cplen + cplen) > TempStr1.length()) cplen2 = 1;
            i += cplen;
            PosToInset.push_back(i);
        }
        int i;
        if(q==0){//第一次大循环插入JP
            RandIndex = PosToInset.at(GetRandomIndex(PosToInset.size()));//在所有可插入位置中随便选一个
            RandIndex2 = GetRandomIndex(Map_Obj["special"]["DECRYPT"]["JP"].size());//随机获取一个下标
            string stemp = (string)Map_Obj["special"]["DECRYPT"]["JP"][RandIndex2];
               TempStr1.insert(RandIndex,stemp);
                        for(int z = RandIndex + 1;z < RandIndex + stemp.length();z++){
                            Avoid.push_back(z);
                }
        }else if(q==1){ // 第二次大循环插入CN
            vector<int> AvailPos;
            AvailPos.resize(max(PosToInset.size(),Avoid.size()));
            vector<int>::iterator itEnd = set_difference(PosToInset.begin(), PosToInset.end(), Avoid.begin(), Avoid.end(), AvailPos.begin());
            AvailPos.erase(std::remove(AvailPos.begin(), AvailPos.end(), 0), AvailPos.end());
            RandIndex = AvailPos.at(GetRandomIndex(AvailPos.size()));//在所有可插入位置中随便选一个
            RandIndex2 = GetRandomIndex(Map_Obj["special"]["DECRYPT"]["CN"].size());//随机获取一个下标
            TempStr1.insert(RandIndex,(string)Map_Obj["special"]["DECRYPT"]["CN"][RandIndex2]);
        }
    }
 
    return TempStr1;
}
DemapResult deMap(PreCheckResult input,string key,bool g){
    string OriginStr(input.output.begin(),input.output.end());
    string TempStr1,TempStrz;
    string temp,temp2,group,findtemp;
    string::size_type idx; 
    int size = OriginStr.length();
    for(int i=0;i<size;){
        int cplen = 1; //该死的C++，处理中文字符贼繁琐
        if((OriginStr[i] & 0xf8) == 0xf0) cplen = 4;
        else if((OriginStr[i] & 0xf0) == 0xe0) cplen = 3;
        else if((OriginStr[i] & 0xe0) == 0xc0) cplen = 2;
        if((i + cplen) > OriginStr.length()) cplen = 1;
        temp = OriginStr.substr(i, cplen);

        //到这儿循环的取字部分就完成了
        //temp是前一个字，temp2是后一个字
        if(temp == NULL_STR){ //如果这是空字符
            i+=cplen; 
            continue;
        }else{//如果不是
            TempStrz.append(temp); //加上
            i+=cplen; 
            continue;
        }
    }
    //TempStrz为去除了标志位/占位符的密文
    size = TempStrz.length();
    OriginStr = TempStrz;


    for(int i=0;i<size;){
        int cplen = 1; //该死的C++，处理中文字符贼繁琐
        int cplen2 = 1;
        if((OriginStr[i] & 0xf8) == 0xf0) cplen = 4;
        else if((OriginStr[i] & 0xf0) == 0xe0) cplen = 3;
        else if((OriginStr[i] & 0xe0) == 0xc0) cplen = 2;
        if((i + cplen) > OriginStr.length()) cplen = 1;

        if((OriginStr[i+cplen] & 0xf8) == 0xf0) cplen2 = 4;
        else if((OriginStr[i+cplen] & 0xf0) == 0xe0) cplen2 = 3;
        else if((OriginStr[i+cplen] & 0xe0) == 0xc0) cplen2 = 2;
        if((i + cplen + cplen) > OriginStr.length()) cplen2 = 1;
        temp = OriginStr.substr(i, cplen);
        if(i != size - cplen2){ //一次遍历两个字符，遇到倒数第一个的时候防止越界
            temp2 = OriginStr.substr(i+cplen, cplen2);
        }else{
            temp2 = NULL_STR;
        }

        //到这儿循环的取字部分就完成了
        //temp是前一个字，temp2是后一个字
        findtemp = FindOriginText(temp); //查找第一个字符的原文
        if(findtemp == "BIG"){ //如果这是一个大写标志位
            findtemp = toupper(FindOriginText(temp2)[0]); //那么找第二个字符的原文
           
            //把找到的原文增加到字符串上
            TempStr1.append(findtemp);
                RoundKey();//轮换密钥
            i = i + cplen + cplen2; //跳过两个字段
            continue;
        }else{
            TempStr1.append(findtemp); //把找到的原文增加到字符串上
                RoundKey();//轮换密钥
            i+=cplen; 
            continue;
        }

        
    }
    //到这儿应该能还原出预先处理过的原文（肯定是个Base64）
    std::vector<uint8_t> TempStr2Int;
    try{
        TempStr2Int = base64::decode(TempStr1); //解码出来的AES加密后的字节码。
        TempStr2Int = AES_256_CTR(key,TempStr2Int); // 原字节码
    }catch(...){
        if(!g){
            cout<<"Error Decoding. Bad Input or Incorrect Key."<<endl;
            throw;
        }
    }

   if(TempStr2Int.at(TempStr2Int.size()-1) == 1 && 
      TempStr2Int.at(TempStr2Int.size()-2) == 1 && 
      TempStr2Int.at(TempStr2Int.size()-3) == 1){
    //链接
    TempStr2Int.pop_back();
    TempStr2Int.pop_back();
    TempStr2Int.pop_back();

    string OriginStr2(TempStr2Int.begin(),TempStr2Int.end()); //理应是一串Urlencode之后的，中英文夹杂的字符串
    size = OriginStr2.length();
    string TempStr3;
    for(int i=0;i<size;){
        int cplen = 1; //该死的C++，处理中文字符贼繁琐
        if((OriginStr2[i] & 0xf8) == 0xf0) cplen = 4;
        else if((OriginStr2[i] & 0xf0) == 0xe0) cplen = 3;
        else if((OriginStr2[i] & 0xe0) == 0xc0) cplen = 2;
        if((i + cplen) > OriginStr2.length()) cplen = 1;
        temp = OriginStr2.substr(i, cplen);

        findtemp = FindLinkOrigin(temp); //查找字符原文
        TempStr3.append(findtemp); //把找到的原文增加到字符串上
        i+=cplen; 
    }
    //查完表之后还原回去
    TempStr2Int = String2Uint8T(TempStr3);

   }else if(TempStr2Int.at(TempStr2Int.size()-1) == 2 && 
            TempStr2Int.at(TempStr2Int.size()-2) == 2 && 
            TempStr2Int.at(TempStr2Int.size()-3) == 2){
    TempStr2Int.pop_back();
    TempStr2Int.pop_back();
    TempStr2Int.pop_back();
   }else{
        if(!g){
            cout<<"Error Decrypting. Incorrect key."<<endl;
            throw;
        }
   }
    //到此，TempStr2Int 就是解密的结果，形式为字节码。
    DemapResult Res;
    string TempStr2(TempStr2Int.begin(),TempStr2Int.end());

    Res.output = TempStr2;
    Res.output_B = TempStr2Int;
    return Res;
}
string GetLinkCryptedText(string text){//查表，检查是否有任何预配置的关键词
    string s = text; //源文本
    string s1,s2;
    int RandIndex; 
    for (auto& el : Map_Obj["link"].items()){//遍历关键词列表
        s1 = el.key();
        if(s.find(s1) != string::npos){//找到关键词
            while(s.find(s1)<s.size()){
                //返回密本中的随机字符
                RandIndex = GetRandomIndex(el.value().size()); //随机获取一个下标
                s2 = (string)Map_Obj["link"][s1][RandIndex];
                int pos = s.find(s1);
                s.replace(pos, s1.size(), s2);
            }
        }

    }
    return s;
}
string GetCryptedText(string letter){//查表返回加密之后的字符串
    int RandIndex,RandIndex2;
    if(LETTERS.find(letter) != string::npos || BIG_LETTERS.find(letter) != string::npos){//判断给定字符的类型
        for (auto& el : Map_Obj["basic"]["alphabet"].items())
        {
            if(el.key() == letter){
                RandIndex = GetRandomIndex(Map_Obj["basic"]["alphabet"][RoundKeyMatch(el.key())].size()); //随机获取一个下标
                return Map_Obj["basic"]["alphabet"][RoundKeyMatch(el.key())][RandIndex];
            }else if(letter[0] == toupper(el.key()[0])){//碰到大写字母
                RandIndex = GetRandomIndex(Map_Obj["basic"]["alphabet"][RoundKeyMatch(el.key())].size());
                RandIndex2 = GetRandomIndex(Map_Obj["special"]["BIG"].size());
                return (string)Map_Obj["special"]["BIG"][RandIndex2] + (string)Map_Obj["basic"]["alphabet"][RoundKeyMatch(el.key())][RandIndex];
            }
        }
    }else if(NUMBERS.find(letter) != string::npos){
        for (auto& el : Map_Obj["basic"]["number"].items())
        {
            if(el.key() == letter){
                RandIndex = GetRandomIndex(Map_Obj["basic"]["number"][RoundKeyMatch(el.key())].size()); //随机获取一个下标
                return Map_Obj["basic"]["number"][RoundKeyMatch(el.key())][RandIndex];
            }
        }
    }else if(SYMBOLS.find(letter) != string::npos){
        for (auto& el : Map_Obj["basic"]["symbol"].items())
        {
            if(el.key() == letter){
                RandIndex = GetRandomIndex(Map_Obj["basic"]["symbol"][RoundKeyMatch(el.key())].size()); //随机获取一个下标
               return Map_Obj["basic"]["symbol"][RoundKeyMatch(el.key())][RandIndex];
            }
        }
    }
    return NULL_STR;
}
string FindOriginText(string letter){
    for (auto el : Map_Obj["special"]["BIG"]){
        string str = (string)el;
        if(letter == str){
            return "BIG";
        }
    }
    for (auto& el : Map_Obj["basic"]["alphabet"].items()){
        for (auto ell : el.value()){
            string str = (string)ell;
            if(letter == str){
                return DRoundKeyMatch(el.key());
            }
        }
    }
    for (auto& el : Map_Obj["basic"]["number"].items()){
        for (auto ell : el.value()){
            string str = (string)ell;
            if(letter == str){
                return DRoundKeyMatch(el.key());
            }
        }
    }
    for (auto& el : Map_Obj["basic"]["symbol"].items()){
        for (auto ell : el.value()){
            string str = (string)ell;
            if(letter == str){
                return DRoundKeyMatch(el.key());
            }
        }
    }
    return "";
}
string FindLinkOrigin(string letter){
    for (auto& el : Map_Obj["link"].items()){
        for (auto ell : el.value()){
            string str = (string)ell;
            if(letter == str){
                return el.key();
            }
        }
    }
    return letter;
}
string UrlEncode(const string& szToEncode)
{
	string src = szToEncode;
	char hex[] = "0123456789ABCDEF";
	string dst;
 
 
	for (size_t i = 0; i < src.size(); ++i)
	{
		unsigned char cc = src[i];
		if ( cc >= 'A' && cc <= 'Z' 
                 || cc >='a' && cc <= 'z'
                 || cc >='0' && cc <= '9'
                 || cc == '.'
                 || cc == '_'
                 || cc == '-'
                 || cc == '*'
                 || cc == ':'
                 || cc == '/'
                 || cc == '%'
                 || cc == '?'
                 || cc == '=')
		{
			if (cc == ' ')
			{
				dst += "+";
			}
			else
				dst += cc;
		}
		else
		{
			unsigned char c = static_cast<unsigned char>(src[i]);
			dst += '%';
			dst += hex[c / 16];
			dst += hex[c % 16];
		}
	}
	return dst;
}
std::vector<uint8_t> readFile(const char* filename)
{
    // open the file:
    std::ifstream file(filename, std::ios::binary);

    // read the data:
    return std::vector<uint8_t>((std::istreambuf_iterator<char>(file)),
                              std::istreambuf_iterator<char>());
}
void rotateString(std::string& str,int n) { //循环右移字符串
    str.append(str, 0, n); // 将字符串的前n个字符追加到字符串的末尾
    str.erase(0, n); // 从字符串开头删除前n个字符
}
void LrotateString(std::string& str,int n) { //循环左移字符串
     // 将字符串分为两部分
    int size = str.length(); 
    str.append(str.substr(0,size-n));
    str.erase(0,size-n);
}
inline string RoundKeyMatch(string keyIn){ //查询轮换密钥的键值

    size_t idx1,idx2,idx3;
    size_t idx1_1,idx2_1,idx3_1;
    size_t idx1_2,idx2_2,idx3_2;

    idx1 = LETTERS.find(keyIn);
    idx2 = NUMBERS.find(keyIn);
    idx3 = SYMBOLS.find(keyIn);

    idx1_1 = LETTERS.find(LETTERS_ROUND_1[idx1]);
    idx2_1 = NUMBERS.find(NUMBERS_ROUND_1[idx2]);
    idx3_1 = SYMBOLS.find(SYMBOLS_ROUND_1[idx3]);

    idx1_2 = LETTERS.find(LETTERS_ROUND_2[idx1_1]);
    idx2_2 = NUMBERS.find(NUMBERS_ROUND_2[idx2_1]);
    idx3_2 = SYMBOLS.find(SYMBOLS_ROUND_2[idx3_1]);

    if(idx1 != string::npos){//判断给定字符的类型
        return LETTERS_ROUND_3.substr(idx1_2,1);
    }else if(idx2 != string::npos){
        return NUMBERS_ROUND_3.substr(idx2_2,1);
    }else if(idx3 != string::npos){
        return SYMBOLS_ROUND_3.substr(idx3_2,1);
    }

    return NULL_STR;
}
inline string DRoundKeyMatch(string keyIn){ //查询轮换密钥的键值

    size_t idx1,idx2,idx3;
    size_t idx1_1,idx2_1,idx3_1;
    size_t idx1_2,idx2_2,idx3_2;

    idx1 = LETTERS_ROUND_3.find(keyIn);
    idx2 = NUMBERS_ROUND_3.find(keyIn);
    idx3 = SYMBOLS_ROUND_3.find(keyIn);

    idx1_1 = LETTERS_ROUND_2.find(LETTERS[idx1]);
    idx2_1 = NUMBERS_ROUND_2.find(NUMBERS[idx2]);
    idx3_1 = SYMBOLS_ROUND_2.find(SYMBOLS[idx3]);

    idx1_2 = LETTERS_ROUND_1.find(LETTERS[idx1_1]);
    idx2_2 = NUMBERS_ROUND_1.find(NUMBERS[idx2_1]);
    idx3_2 = SYMBOLS_ROUND_1.find(SYMBOLS[idx3_1]);

    if(idx1 != string::npos){//判断给定字符的类型
        return LETTERS.substr(idx1_2,1);
    }else if(idx2 != string::npos){
        return NUMBERS.substr(idx2_2,1);
    }else if(idx3 != string::npos){
        return SYMBOLS.substr(idx3_2,1);
    }

    return NULL_STR;
}
inline void RoundKey(){ //轮换密钥
    if(RoundFlip == 32){
        RoundFlip = 0;
    }
    int ControlNum = RoundControl[RoundFlip] % 10; //哈希字节对十取余即操作数
    if(ControlNum == 0){ //等于零就赋值为10
        ControlNum = 10;
    }

    if(ControlNum % 2 == 0){ //操作数是偶数
        rotateString(LETTERS_ROUND_1,1); //将第一个密钥轮向右轮一位
        rotateString(NUMBERS_ROUND_1,1);
        rotateString(SYMBOLS_ROUND_1,1);

        LrotateString(LETTERS_ROUND_2, ControlNum/2); //将第二个密钥轮向左轮ControlNum/2位
        LrotateString(NUMBERS_ROUND_2, ControlNum/2);
        LrotateString(SYMBOLS_ROUND_2, ControlNum/2);

        rotateString(LETTERS_ROUND_3, (ControlNum/2)+1); //将第三个密钥轮向右轮ControlNum/2+1位
        rotateString(NUMBERS_ROUND_3, (ControlNum/2)+1);
        rotateString(SYMBOLS_ROUND_3, (ControlNum/2)+1);
    }else{ //操作数是奇数
        LrotateString(LETTERS_ROUND_1,2); //将第一个密钥轮向左轮2位
        LrotateString(NUMBERS_ROUND_1,2);
        LrotateString(SYMBOLS_ROUND_1,2);

        rotateString(LETTERS_ROUND_2, ControlNum); //将第二个密钥轮向右轮ControlNum位
        rotateString(NUMBERS_ROUND_2, ControlNum);
        rotateString(SYMBOLS_ROUND_2, ControlNum);

        LrotateString(LETTERS_ROUND_3, (ControlNum+3)/2); //将第三个密钥轮向左轮(ControlNum+3)/2位
        LrotateString(NUMBERS_ROUND_3, (ControlNum+3)/2);
        LrotateString(SYMBOLS_ROUND_3, (ControlNum+3)/2);
    }
   RoundFlip++;
}
inline int GetRandomIndex(int length){
    int Rand = distribution(generator);
    return Rand % length;
}


std::vector<uint8_t> String2Uint8T(const std::string& str) { //把字符串拆解成字节数组
    std::vector<uint8_t> result(str.begin(), str.end());
    return result;
}

vector<uint8_t> SHA256(vector<uint8_t> data){ //计算给定字节数组的哈希
    std::vector<uint8_t> hash(picosha2::k_digest_size);
    picosha2::hash256(data.begin(), data.end(), hash.begin(), hash.end());
    return hash;
}

std::vector<uint8_t> AES_256_CTR(string key,vector<uint8_t> data){ //执行AES_256_CTR加密，返回字节码
    AES_ctx ctx;
    vector<uint8_t> KeyHashV = SHA256(String2Uint8T(key));
    vector<uint8_t> KeyHashHash = SHA256(KeyHashV); //对密钥的第二次哈希

    uint8_t* KeyHash = new uint8_t[KeyHashV.size()];
    for (size_t i = 0; i < KeyHashV.size(); ++i) {
        KeyHash[i] = KeyHashV[i];
    }

    uint8_t* iv = new uint8_t[16];
    for(int i=0;i<16;i++){
        iv[i] = KeyHashHash[i]; //初始化向量直接使用密钥两次哈希的前16字节，这么做不是最佳实践。
        //但是，本项目不会特别把初始化向量另外保存，这样会显著增加密文长度。
    }

    AES_init_ctx_iv(&ctx,KeyHash,iv);

    int size = data.size();

    uint8_t* Data = new uint8_t[size]; //开辟空间
    for(int i=0;i<size;i++){
        Data[i] = data[i];
    }

    AES_CTR_xcrypt_buffer(&ctx, Data, size);

    for(int i=0;i<size;i++){ //把字符序列反转回去
        data[i] = Data[i];
    }

    delete[] Data; //删掉开辟的空间
    delete[] KeyHash;
    delete[] iv;

    return data;
}