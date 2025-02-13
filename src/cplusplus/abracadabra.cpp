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
 * ACKNOWLEDGEMENT
 *
 * This project uses code from Unishox2 as a compression library,
 * with certain modifications made to achieve specific purposes.
 *
 * Unishox2 is licensed under the Apache License, Version 2.0.
 * Copyright (C) 2020 Siara Logics (cc)
 *
 * Special thanks to Arundale Ramanathan, the author of Unishox2,
 * who genuinely answered my enquiries and helped me to debug.
 *
 */

#include <iostream> //Basic Libs
#include <fstream>

#ifdef _WIN32
#include <String.h>
#include <Windows.h>
#elif defined(__linux__)
#include <string.h>
#endif

#include <stdio.h>
#include <cstdlib>
#include <random>
#include <ctime>
#include <cstdint>
#include <vector>

#include <nlohmann/json.hpp> //JSON processing
#include <cppcodec/base64_rfc4648.hpp> //Base64 Proccessing
#include <CLI11.hpp> //CLI Support
#include <tinyaes/aes.hpp> //AES Support
#include <tinyaes/aes.c>
#include <picosha2.h> //SHA256 Support

#include <gzip/compress.hpp> //Compression Support
#include <gzip/decompress.hpp>
#include <gzip/utils.hpp>
#include "unishox2.c" //Alternated Unishox Lib

#define USX_HCODES_DFLT (const unsigned char[]) {0x00, 0x40, 0x80, 0xC0, 0xE0}
#define USX_HCODE_LENS_DFLT (const unsigned char[]) {2, 2, 2, 3, 3}

using namespace std;
using json = nlohmann::json;
using base64 = cppcodec::base64_rfc4648;

const string Map = "{\"basic\":{\"alphabet\":{\"a\":[\"请\",\"上\",\"中\",\"之\",\"等\",\"人\",\"到\",\"年\",\"个\",\"将\"],\"b\":[\"得\",\"可\",\"并\",\"发\",\"过\",\"协\",\"曲\",\"闭\",\"斋\",\"峦\"],\"c\":[\"页\",\"于\",\"而\",\"被\",\"无\",\"挽\",\"裕\",\"斜\",\"绪\",\"镜\"],\"d\":[\"由\",\"把\",\"好\",\"从\",\"会\",\"帕\",\"莹\",\"盈\",\"敬\",\"粒\"],\"e\":[\"的\",\"在\",\"了\",\"是\",\"为\",\"有\",\"和\",\"我\",\"一\",\"与\"],\"f\":[\"站\",\"最\",\"号\",\"及\",\"能\",\"迟\",\"鸭\",\"呈\",\"玻\",\"据\"],\"g\":[\"着\",\"很\",\"此\",\"但\",\"看\",\"浩\",\"附\",\"侃\",\"汐\",\"绸\"],\"h\":[\"名\",\"呢\",\"又\",\"图\",\"啊\",\"棉\",\"畅\",\"蒸\",\"玫\",\"添\"],\"i\":[\"对\",\"地\",\"您\",\"给\",\"这\",\"下\",\"网\",\"也\",\"来\",\"你\"],\"j\":[\"更\",\"天\",\"去\",\"用\",\"只\",\"矽\",\"萌\",\"镁\",\"芯\",\"夸\"],\"k\":[\"第\",\"者\",\"所\",\"两\",\"里\",\"氢\",\"羟\",\"纽\",\"夏\",\"春\"],\"l\":[\"自\",\"做\",\"前\",\"二\",\"他\",\"氦\",\"汀\",\"兰\",\"竹\",\"捷\"],\"m\":[\"家\",\"点\",\"路\",\"至\",\"十\",\"锂\",\"羧\",\"暑\",\"夕\",\"振\"],\"n\":[\"区\",\"想\",\"向\",\"主\",\"四\",\"铍\",\"烃\",\"惠\",\"芳\",\"岩\"],\"o\":[\"就\",\"新\",\"吗\",\"该\",\"不\",\"多\",\"还\",\"要\",\"让\",\"大\"],\"p\":[\"小\",\"如\",\"成\",\"位\",\"其\",\"硼\",\"酞\",\"褔\",\"苑\",\"笋\"],\"q\":[\"吧\",\"每\",\"机\",\"几\",\"总\",\"碳\",\"铂\",\"涓\",\"绣\",\"悦\"],\"r\":[\"起\",\"它\",\"内\",\"高\",\"次\",\"氮\",\"铵\",\"奏\",\"鲤\",\"淳\"],\"s\":[\"非\",\"元\",\"类\",\"五\",\"使\",\"氧\",\"醇\",\"迷\",\"霁\",\"琅\"],\"t\":[\"首\",\"进\",\"即\",\"没\",\"市\",\"氖\",\"酯\",\"琳\",\"绫\",\"濑\"],\"u\":[\"后\",\"三\",\"本\",\"都\",\"时\",\"月\",\"或\",\"说\",\"已\",\"以\"],\"v\":[\"种\",\"快\",\"那\",\"篇\",\"万\",\"钠\",\"炔\",\"柯\",\"睿\",\"琼\"],\"w\":[\"长\",\"按\",\"报\",\"比\",\"信\",\"硅\",\"烷\",\"静\",\"欣\",\"束\"],\"x\":[\"再\",\"带\",\"才\",\"全\",\"呀\",\"磷\",\"烯\",\"柔\",\"雪\",\"冰\"],\"y\":[\"业\",\"却\",\"版\",\"美\",\"们\",\"硫\",\"桉\",\"寒\",\"冻\",\"玖\"],\"z\":[\"像\",\"走\",\"文\",\"各\",\"当\",\"氯\",\"缬\",\"妃\",\"琉\",\"璃\"],\"A\":[\"贴\",\"则\",\"老\",\"生\",\"达\",\"商\",\"行\",\"周\",\"证\",\"经\"],\"B\":[\"事\",\"场\",\"同\",\"化\",\"找\",\"建\",\"手\",\"道\",\"间\",\"式\"],\"C\":[\"特\",\"城\",\"型\",\"定\",\"接\",\"局\",\"问\",\"重\",\"叫\",\"通\"],\"D\":[\"件\",\"少\",\"面\",\"金\",\"近\",\"买\",\"听\",\"学\",\"见\",\"称\"],\"E\":[\"写\",\"选\",\"片\",\"体\",\"组\",\"先\",\"仅\",\"别\",\"表\",\"现\"],\"F\":[\"雨\",\"泊\",\"注\",\"织\",\"赴\",\"茶\",\"因\",\"设\",\"环\",\"青\"],\"G\":[\"数\",\"心\",\"子\",\"处\",\"作\",\"项\",\"谁\",\"分\",\"转\",\"字\"],\"H\":[\"砂\",\"妥\",\"鹦\",\"课\",\"栗\",\"霞\",\"鹉\",\"翌\",\"蕴\",\"憩\"],\"I\":[\"畔\",\"珑\",\"咫\",\"瑞\",\"玲\",\"郊\",\"蛟\",\"昱\",\"祉\",\"菁\"],\"J\":[\"铁\",\"宙\",\"耕\",\"琴\",\"铃\",\"瑰\",\"旬\",\"茉\",\"砺\",\"莅\"],\"K\":[\"钇\",\"莉\",\"筱\",\"森\",\"曳\",\"苹\",\"踵\",\"晰\",\"砥\",\"舀\"],\"L\":[\"锆\",\"粟\",\"魄\",\"辉\",\"谜\",\"馅\",\"醋\",\"甄\",\"韶\",\"泪\"],\"M\":[\"钌\",\"倘\",\"祥\",\"善\",\"泉\",\"惦\",\"铠\",\"骏\",\"韵\",\"泣\"],\"N\":[\"铑\",\"筑\",\"铿\",\"智\",\"禀\",\"磊\",\"桨\",\"檀\",\"荧\",\"铭\"],\"O\":[\"钯\",\"骐\",\"烛\",\"蔬\",\"凛\",\"溯\",\"困\",\"炯\",\"酿\",\"瑕\"],\"P\":[\"银\",\"榻\",\"驿\",\"缎\",\"澟\",\"绒\",\"莺\",\"萤\",\"桅\",\"枕\"],\"Q\":[\"镉\",\"赞\",\"瑾\",\"程\",\"怡\",\"漱\",\"穗\",\"湍\",\"栀\",\"皆\"],\"R\":[\"碘\",\"礼\",\"饴\",\"舒\",\"芷\",\"麟\",\"沥\",\"描\",\"锄\",\"墩\"],\"S\":[\"锡\",\"彰\",\"瞻\",\"雅\",\"贮\",\"喵\",\"翊\",\"闪\",\"翎\",\"婉\"],\"T\":[\"钨\",\"咨\",\"涌\",\"益\",\"嵩\",\"御\",\"饶\",\"纺\",\"栩\",\"稔\"],\"U\":[\"铋\",\"骆\",\"橘\",\"未\",\"泰\",\"频\",\"琥\",\"囍\",\"浣\",\"裳\"],\"V\":[\"钕\",\"飒\",\"浇\",\"哦\",\"途\",\"瓢\",\"珀\",\"涨\",\"仓\",\"棠\"],\"W\":[\"祁\",\"蓬\",\"灿\",\"部\",\"涧\",\"舫\",\"曙\",\"航\",\"礁\",\"渡\"],\"X\":[\"旺\",\"嫦\",\"漫\",\"佑\",\"钥\",\"谧\",\"葵\",\"咩\",\"诵\",\"绮\"],\"Y\":[\"阐\",\"译\",\"锻\",\"茜\",\"坞\",\"砌\",\"靛\",\"猫\",\"芮\",\"绚\"],\"Z\":[\"拌\",\"皎\",\"笙\",\"沃\",\"悟\",\"拓\",\"遨\",\"揽\",\"昼\",\"蔗\"]},\"numbersymbol\":{\"0\":[\"卡\",\"风\",\"水\",\"放\",\"花\",\"钾\",\"宏\",\"谊\",\"探\",\"棋\"],\"1\":[\"需\",\"头\",\"话\",\"曾\",\"楼\",\"钙\",\"吾\",\"恋\",\"菲\",\"遥\"],\"2\":[\"连\",\"系\",\"门\",\"力\",\"量\",\"钛\",\"苗\",\"氛\",\"鹤\",\"雀\"],\"3\":[\"书\",\"亿\",\"跟\",\"深\",\"方\",\"钒\",\"鸳\",\"鸯\",\"纸\",\"鸢\"],\"4\":[\"若\",\"低\",\"谈\",\"明\",\"百\",\"铬\",\"羯\",\"尧\",\"舜\",\"兆\"],\"5\":[\"关\",\"客\",\"读\",\"双\",\"回\",\"锰\",\"熙\",\"瀚\",\"渊\",\"灯\"],\"6\":[\"较\",\"品\",\"嘛\",\"单\",\"价\",\"钴\",\"阑\",\"珊\",\"雁\",\"鹂\"],\"7\":[\"山\",\"西\",\"动\",\"厂\",\"热\",\"锌\",\"鹃\",\"鸠\",\"昆\",\"仑\"],\"8\":[\"言\",\"笑\",\"度\",\"易\",\"身\",\"镓\",\"乾\",\"坤\",\"澈\",\"饺\"],\"9\":[\"份\",\"星\",\"千\",\"仍\",\"办\",\"锗\",\"彗\",\"聪\",\"慧\",\"磋\"],\"+\":[\"集\",\"费\",\"传\",\"室\",\"拉\"],\"/\":[\"难\",\"界\",\"指\",\"管\",\"具\"],\"?\":[\"相\",\"儿\",\"李\",\"早\",\"拿\"],\"-\":[\"科\",\"白\",\"段\",\"飞\",\"住\"],\".\":[\"利\",\"红\",\"板\",\"光\",\"约\"],\"(\":[\"变\",\"款\",\"林\",\"夹\",\"院\"],\")\":[\"服\",\"句\",\"声\",\"务\",\"游\"],\"[\":[\"股\",\"南\",\"社\",\"阿\",\"远\"],\"]\":[\"意\",\"换\",\"些\",\"必\",\"赛\"],\"<\":[\"届\",\"完\",\"乐\",\"彩\",\"讲\"],\">\":[\"展\",\"帮\",\"且\",\"物\",\"班\"],\",\":[\"何\",\"流\",\"密\",\"某\",\"房\"],\"|\":[\"语\",\"亚\",\"常\",\"除\",\"装\"],\"=\":[\"极\",\"载\",\"题\",\"刚\",\"气\"],\"@\":[\"米\",\"影\",\"德\",\"世\",\"坐\"],\"#\":[\"北\",\"招\",\"短\",\"活\",\"斯\"],\"!\":[\"值\",\"店\",\"树\",\"哪\",\"余\"],\"~\":[\"盘\",\"速\",\"座\",\"求\",\"创\"],\"`\":[\"梦\",\"足\",\"半\",\"视\",\"安\"],\"$\":[\"空\",\"歌\",\"派\",\"顶\",\"登\"],\"%\":[\"夜\",\"云\",\"感\",\"啦\",\"欲\"],\"^\":[\"边\",\"工\",\"眼\",\"街\",\"奖\"],\"&\":[\"获\",\"占\",\"理\",\"任\",\"实\"],\"*\":[\"知\",\"掉\",\"色\",\"讯\",\"克\"],\"_\":[\"直\",\"评\",\"往\",\"层\",\"园\"],\"{\":[\"留\",\"靠\",\"亦\",\"罗\",\"营\"],\"}\":[\"合\",\"尚\",\"产\",\"诚\",\"汨\"],\":\":[\"曱\",\"朩\",\"杉\",\"杸\",\"歩\"],\";\":[\"毋\",\"氕\",\"気\",\"氘\",\"氙\"]}},\"special\":{\"DECRYPT\":{\"JP\":[\"桜\",\"込\",\"凪\",\"雫\",\"実\",\"沢\"],\"CN\":[\"玚\",\"俟\",\"玊\",\"欤\",\"瞐\",\"珏\"]}}}"; //字符串映射表
const json Map_Obj = json::parse(Map); //JSON字符串映射表对象

int RoundFlip = 0; //标志现在到哪了
uint8_t RoundControl[32]; //一个数组，用密钥哈希来控制轮转的行为
const string Normal_Characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+=_-/?.>,<|`~!@#$%^&*(){}[];:1234567890"; //表内有映射的所有字符组成的字符串
const string LETTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
string LETTERS_ROUND_1 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
string LETTERS_ROUND_2 = "FbPoDRStyJKAUcdahfVXlqwnOGpHZejzvmrBCigQILxkYMuWTEsN"; //手动随机打乱的乱序轮
string LETTERS_ROUND_3 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string BIG_LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string SYMBOLS = "+=_-/?.>,<|`~!@#$%^&*(){}[];:";
const string NUMBERS = "1234567890";
const string NUMBERSYMBOL = "1234567890+=_-/?.>,<|`~!@#$%^&*(){}[];:";
string NUMBERSYMBOL_ROUND_1 = "1234567890+=_-/?.>,<|`~!@#$%^&*(){}[];:";
string NUMBERSYMBOL_ROUND_2 = "~3{8}_-$[6(2^&#5|1*%0,<9:`+@7/?.>4=];!)"; //手动随机打乱的乱序轮
string NUMBERSYMBOL_ROUND_3 = "1234567890+=_-/?.>,<|`~!@#$%^&*(){}[];:";

const string SIG_DECRYPT_JP = "桜込凪雫実沢";
const string SIG_DECRYPT_CN = "玚俟玊欤瞐珏";
const string NULL_STR = "孎"; //默认忽略的占位字符，一个生僻字。

//搜索顺序

static const char *CHINESE_WEBPAN_LIB[] = {"https://","lanzou","pan.quark.cn","pan.baidu.com","aliyundrive.com","123pan.com"};
static const char *INTER_WEBPAN_LIB[] = {"https://","mypikpak.com","mega.nz","drive.google.com","sharepoint.com","1drv.ms"};
static const char *CHINESE_WEBSITE_LIB[] = {"https://","baidu.com","b23.tv","bilibili.com","weibo.com","weixin.qq.com"};
static const char *INTER_WEBSITE_LIB[] = {"https://","google.com","youtube.com","x.com","twitter.com","telegra.ph"};
static const char *INTER_WEBSITE_LIB_2[] = {"https://","wikipedia.org","github.com","pages.dev","github.io","netlify.app"};
static const char *JAPAN_WEBSITE_LIB[] = {"https://","pixiv.net","nicovideo.jp","dlsite.com","line.me","dmm.com"};
static const char *PIRACY_WEBSITE_LIB[] = {"https://","nyaa.si","bangumi.moe","thepiratebay.org","e-hentai.org","exhentai.org"};
static const char *GENERIC_TLINK_LIB[] = {"https://","magnet:?xt=urn:btih:","magnet:?xt=urn:sha1:","ed2k://","thunder://","torrent"};
static const char *GENERIC_LINK_LIB_1[] = {"https://",".cn", ".com",".net", ".org", ".xyz"};
static const char *GENERIC_LINK_LIB_2[] = {"https://",".info", ".moe", ".cc",".co", ".dev"};
static const char *GENERIC_LINK_LIB_3[] = {"https://",".io", ".us", ".eu",".jp", ".de"};

random_device rd;
mt19937 generator(rd());
uniform_int_distribution<int> distribution(0, 10000);

struct PreCheckResult { // 专门用来打包传递预检的结果
    vector<uint8_t> output;
    bool isEncrypted = false;
};

struct DemapResult { // 专门用来打包解密的结果
    string output;
    vector<uint8_t> output_B;
};

string enMap(PreCheckResult input,string key,bool t,bool q);
DemapResult deMap(PreCheckResult input,string key,bool g,bool t);
string FindOriginText(string& letter);
string GetCryptedText(string& letter);
int GetRandomIndex(int length);
int GetLuhnBit(vector<uint8_t>& data);
bool CheckLuhnBit(vector<uint8_t> data);
std::vector<uint8_t> readFile(const char* filename);
PreCheckResult preCheck(vector<uint8_t> Input);
void rotateString(std::string& str,int n);
void LrotateString(std::string& str,int n) ;
inline string RoundKeyMatch(const string& keyIn);
inline string DRoundKeyMatch(const string& keyIn);
inline void RoundKey();

std::vector<uint8_t> String2Uint8T(const std::string& str);
void AES_256_CTR(string& key,vector<uint8_t>& data, const int* randomByte);
vector<uint8_t> SHA256(vector<uint8_t> data);
std::vector<uint8_t> GZIP_COMPRESS(std::vector<uint8_t> Data);
std::vector<uint8_t> GZIP_DECOMPRESS(std::vector<uint8_t> Data);
std::vector<uint8_t> UNISHOX_COMPRESS(std::vector<uint8_t> Data);
std::vector<uint8_t> UNISHOX_DECOMPRESS(std::vector<uint8_t> Data);

#ifdef _WIN32
std::string GbkToUtf8(const std::string& src_str)
{
    std::string result;
    wchar_t* strSrc;
    char* szRes;
    int len = MultiByteToWideChar(CP_ACP, 0, src_str.c_str(), -1, NULL, 0);
    strSrc = new wchar_t[len + 1];
    MultiByteToWideChar(CP_ACP, 0, src_str.c_str(), -1, strSrc, len);
 
    len = WideCharToMultiByte(CP_UTF8, 0, strSrc, -1, NULL, 0, NULL, NULL);
    szRes = new char[len + 1];
    WideCharToMultiByte(CP_UTF8, 0, strSrc, -1, szRes, len, NULL, NULL);
    result = szRes;
    if (strSrc)
        delete[]strSrc;
    if (szRes)
        delete[]szRes;
    return result;
}
#endif

std::vector<uint8_t> CliString2Uint8T(const std::string& str) {
    #ifdef _WIN32
    return String2Uint8T(GbkToUtf8(str));
    #elif defined(__linux__)
    return String2Uint8T(str);
    #endif
}

int main(int argc, char *argv[]){
    #ifdef _WIN32
        // Windows 特定修正
        SetConsoleOutputCP(CP_UTF8);
    #endif

    CLI::App app{"***Abracadabra v2.7.0***"}; //CLI11提供的命令行参数解析

    string arg1 = "";
    PreCheckResult input;
    bool e = false, d = false,q = false,g = false,t = false;
    string f = NULL_STR,o = NULL_STR,i = NULL_STR,i2 = NULL_STR,k = "ABRACADABRA";//给定的文件路径和输入
    ofstream outfile;
    vector<uint8_t> inputfiledata;

    //定义命令行参数
    CLI::Option* i2flag = app.add_option("DEFAULT", i2, "Input text, if there is no given option besides.");
    CLI::Option* eflag = app.add_flag("-e", e, "Force to encrypt.");
    CLI::Option* dflag = app.add_flag("-d", d, "Force to decrypt.");
    CLI::Option* qflag = app.add_flag("-q", q, "Skip appending encrypt marks.");
    CLI::Option* gflag = app.add_flag("-g", g, "Ignore any data checks.");
    CLI::Option* tflag = app.add_flag("-t", t, "Test/Debug mode, output more informations.");
    CLI::Option* fflag = app.add_option("-f", f, "Input an arbitrary given file.");
    CLI::Option* oflag = app.add_option("-o", o, "Declare an output file to save the result.");
    CLI::Option* iflag = app.add_option("-i", i, "Input text, expected if -f is not used.");
    CLI::Option* kflag = app.add_option("-k", k, "Key to encrypt, ABRACADABRA in default.");

    i2flag
        ->take_last()
        ->excludes("-f")
        ->excludes("-i");
    dflag
        ->take_last()
        ->excludes("-e");
    eflag
        ->take_last()
        ->excludes("-d");
    qflag
        ->take_last()
        ->excludes("-d");
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
    tflag
        ->take_last();
    gflag
        ->take_last();
    try{
        CLI11_PARSE(app, argc, argv);
    }catch(...){
        cout<<"Your Command is not valid."<<endl;
        cout<<"Run with --help for more information."<<endl;
        return 0;
    }

    vector<uint8_t> KeyHashVec = SHA256(CliString2Uint8T(k));
    for(int i=0;i<32;i++){
        RoundControl[i] = KeyHashVec[i];
    }

    //这里处理所有输入的逻辑
    if (i2 != NULL_STR){//如果i2存在，即只有一个参数
        PreCheckResult Result;
        Result = preCheck(CliString2Uint8T(i2));
        if(Result.isEncrypted){
            d = true;
        }
        input = Result;
    }else{
        if(i != NULL_STR){
            input = preCheck(CliString2Uint8T(i));
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

    if(!d || e){
        Process_res = enMap(input,k,t,q);
    }else{
        //尝试解密
        Res = deMap(input,k,g,t); //如果输入的是文件，解密后的“字符串”未必是字符串，只是类字符数组，若不指定输出路径，直接命令行输出必乱码
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
    bool isEncrypted = false;//判定该文本是否为加密文本

    bool isJPFound = false;//如果检查出一个日语标志位，则标记为真
    bool isCNFound = false;//如果检查出一个汉字标志位，则标记为真
    for(int i=0;i<size;){

        int cplen = 1; //该死的C++，处理中文字符贼繁琐
        if((input[i] & 0xf8) == 0xf0) cplen = 4;
        else if((input[i] & 0xf0) == 0xe0) cplen = 3;
        else if((input[i] & 0xe0) == 0xc0) cplen = 2;
        if((i + cplen) > (int)input.length()) cplen = 1;
        temp = input.substr(i, cplen);

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
        i += cplen;
    }
    PreCheckResult Result;
    if(isJPFound&&isCNFound){
        isEncrypted=true;
        Result.output = String2Uint8T(input);
    }else{
        Result.output = Input;
    }
    Result.isEncrypted = isEncrypted;
    return Result;
}
string enMap(PreCheckResult input,string key,bool t,bool q){

    vector<uint8_t> OriginalData = input.output;
    string TempS(input.output.begin(),input.output.end());

    OriginalData.push_back(GetLuhnBit(OriginalData)); //获取校验码并压进去。
    
    std::array<int, 2> RandomByte {
        //取两个随机数作为初始化向量的随机性
        GetRandomIndex(256),
        GetRandomIndex(256),
    };

    if(OriginalData.size() <= 1024){
        unsigned int SizeBefore = OriginalData.size();
        OriginalData = UNISHOX_COMPRESS(OriginalData);

        if(OriginalData.size() == SizeBefore){
            OriginalData = GZIP_COMPRESS(OriginalData); //Gzip压缩
        }
    }else{
        OriginalData = GZIP_COMPRESS(OriginalData); //Gzip压缩
    }

    AES_256_CTR(key,OriginalData,RandomByte.data()); //AES加密
    OriginalData.push_back(RandomByte[0]); //压进最后两个比特
    OriginalData.push_back(RandomByte[1]);
    string OriginStr = base64::encode(OriginalData); //用Base64编码AES的加密结果
    if(t){
        cout<<"AES -> Base64: "<< OriginStr << endl;
    }

    string TempStr1;
    string temp,temp2,group;
    int size = OriginStr.length();
    RoundKey();
    for(int i=0;i<size;){
        int cplen = 1; //该死的C++，处理中文字符贼繁琐
        if((OriginStr[i] & 0xf8) == 0xf0) cplen = 4;
        else if((OriginStr[i] & 0xf0) == 0xe0) cplen = 3;
        else if((OriginStr[i] & 0xe0) == 0xc0) cplen = 2;
        if((i + cplen) > (int)OriginStr.length()) cplen = 1;
        temp = OriginStr.substr(i, cplen);

        //加密操作开始
        //把加密字符加到结果字符串的后面
        TempStr1.append(GetCryptedText(temp));
        RoundKey();

        i += cplen;
    }
    //第一个循环结束后，TempStr1应当是完全的密文，但是缺少标志位

    if(q){
        return TempStr1;
    }

    int RandIndex,RandIndex2;
    vector<int> Avoid;
    for(int q=0;q<2;q++){//分两次大循环
        vector<int> PosToInset;
        size = TempStr1.length();
        for(int i=0;i<size;){ //这里需要确定所有插入UTF-8字符的合适位置
            int cplen = 1; //该死的C++，处理中文字符贼繁琐
            if((TempStr1[i] & 0xf8) == 0xf0) cplen = 4;
            else if((TempStr1[i] & 0xf0) == 0xe0) cplen = 3;
            else if((TempStr1[i] & 0xe0) == 0xc0) cplen = 2;
            if((i + cplen) > (int)TempStr1.length()) cplen = 1;
            i += cplen;
            PosToInset.push_back(i);
        }
        if(q==0){//第一次大循环插入JP
            RandIndex = PosToInset.at(GetRandomIndex(PosToInset.size()));//在所有可插入位置中随便选一个
            RandIndex2 = GetRandomIndex(Map_Obj["special"]["DECRYPT"]["JP"].size());//随机获取一个下标
            string stemp = (string)Map_Obj["special"]["DECRYPT"]["JP"][RandIndex2];
            TempStr1.insert(RandIndex,stemp);
            for(int z = RandIndex + 1;z < RandIndex + (int)stemp.length();z++){
                    Avoid.push_back(z);
            }
        }else if(q==1){ // 第二次大循环插入CN
            vector<int> AvailPos;
            AvailPos.resize(max(PosToInset.size(),Avoid.size()));
            set_difference(PosToInset.begin(), PosToInset.end(), Avoid.begin(), Avoid.end(), AvailPos.begin());
            AvailPos.erase(std::remove(AvailPos.begin(), AvailPos.end(), 0), AvailPos.end());
            RandIndex = AvailPos.at(GetRandomIndex(AvailPos.size()));//在所有可插入位置中随便选一个
            RandIndex2 = GetRandomIndex(Map_Obj["special"]["DECRYPT"]["CN"].size());//随机获取一个下标
            TempStr1.insert(RandIndex,(string)Map_Obj["special"]["DECRYPT"]["CN"][RandIndex2]);
        }
    }
    
    return TempStr1;
}
DemapResult deMap(PreCheckResult input,string key,bool g,bool t){
    string OriginStr(input.output.begin(),input.output.end());
    string TempStr1,TempStrz;
    string temp,temp2,group,findtemp;
    int size = OriginStr.length();
    for(int i=0;i<size;){
        int cplen = 1; //该死的C++，处理中文字符贼繁琐
        if((OriginStr[i] & 0xf8) == 0xf0) cplen = 4;
        else if((OriginStr[i] & 0xf0) == 0xe0) cplen = 3;
        else if((OriginStr[i] & 0xe0) == 0xc0) cplen = 2;
        if((i + cplen) > (int)OriginStr.length()) cplen = 1;
        temp = OriginStr.substr(i, cplen);

        //到这儿循环的取字部分就完成了
        //temp是前一个字，temp2是后一个字
        if(temp == NULL_STR || temp == " " || temp == "\n" || temp == "\t"){ //如果这是空字符
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
    RoundKey();

    for(int i=0;i<size;){
        int cplen = 1; //该死的C++，处理中文字符贼繁琐
        int cplen2 = 1;
        if((OriginStr[i] & 0xf8) == 0xf0) cplen = 4;
        else if((OriginStr[i] & 0xf0) == 0xe0) cplen = 3;
        else if((OriginStr[i] & 0xe0) == 0xc0) cplen = 2;
        if((i + cplen) > (int)OriginStr.length()) cplen = 1;

        if((OriginStr[i+cplen] & 0xf8) == 0xf0) cplen2 = 4;
        else if((OriginStr[i+cplen] & 0xf0) == 0xe0) cplen2 = 3;
        else if((OriginStr[i+cplen] & 0xe0) == 0xc0) cplen2 = 2;
        if((i + cplen + cplen) > (int)OriginStr.length()) cplen2 = 1;
        temp = OriginStr.substr(i, cplen);
        if(i != size - cplen2){ //一次遍历两个字符，遇到倒数第一个的时候防止越界
            temp2 = OriginStr.substr(i+cplen, cplen2);
        }else{
            temp2 = NULL_STR;
        }

        //到这儿循环的取字部分就完成了
        //temp是前一个字，temp2是后一个字
        findtemp = FindOriginText(temp); //查找字符的原文
        if(findtemp == "" && !g){
            cout<<"Error Decoding. Bad Input."<<endl;
            cout<<"Try force encryption if you intended to encrypt something."<<endl; //如果有任何一个字没查到，那么考虑标志位污染
            cout<<"If you want to go on anyway, add flag -g to ignore this check."<<endl;
            throw;
        }
        TempStr1.append(findtemp); //把找到的原文增加到字符串上
        RoundKey();//轮换密钥
        i+=cplen;
        continue;
    }

    if(t){
        cout<<"Round -> Base64: " << TempStr1 << endl;
    }
    //到这儿应该能还原出预先处理过的原文（肯定是个Base64）
    std::vector<uint8_t> TempStr2Int;
    int* RandomByte = new int[2];
    try{
        TempStr2Int = base64::decode(TempStr1); //解码出来的AES加密后的字节码。
        RandomByte[1] = TempStr2Int.at(TempStr2Int.size()-1);
        RandomByte[0] = TempStr2Int.at(TempStr2Int.size()-2);
        TempStr2Int.pop_back();
        TempStr2Int.pop_back();
        AES_256_CTR(key,TempStr2Int,RandomByte); // 原字节码
        TempStr2Int = GZIP_DECOMPRESS(TempStr2Int); //解压缩
        TempStr2Int = UNISHOX_DECOMPRESS(TempStr2Int); //解压缩
    }catch(...){
        if(!g){
            cout<<"Error Decoding. Bad Input or Incorrect Key."<<endl;
            delete[] RandomByte;
            throw;
        }
    }
    delete[] RandomByte;
    if(!CheckLuhnBit(TempStr2Int)){ //如果检查LuhnBit出了问题
        if(TempStr2Int.at(TempStr2Int.size()-1) == 2 && 
            TempStr2Int.at(TempStr2Int.size()-2) == 2 && 
            TempStr2Int.at(TempStr2Int.size()-3) == 2){ //兼容性，检查旧版本的校验码
                TempStr2Int.pop_back();
                TempStr2Int.pop_back();
                TempStr2Int.pop_back();
        }else{ //如果仍然不行，丢错误出去
                if(!g){
                    cout<<"Error Decrypting. Checksum Mismatch."<<endl;
                    throw;
                }
        }
   }else{
    TempStr2Int.pop_back(); //删掉校验码
   }
    //到此，TempStr2Int 就是解密的结果，形式为字节码。
    DemapResult Res;
    string TempStr2(TempStr2Int.begin(),TempStr2Int.end());

    Res.output = TempStr2;
    Res.output_B = TempStr2Int;
    return Res;
}
string GetCryptedText(string& letter){//查表返回加密之后的字符串
    int RandIndex;
    if(LETTERS.find(letter) != string::npos){
        for (auto& el : Map_Obj["basic"]["alphabet"].items())
        {   
            if(el.key() == letter){
                RandIndex = GetRandomIndex(Map_Obj["basic"]["alphabet"][RoundKeyMatch(el.key())].size()); //随机获取一个下标
                return Map_Obj["basic"]["alphabet"][RoundKeyMatch(el.key())][RandIndex];
            }else if(letter[0] == toupper(el.key()[0])){//碰到大写字母
                string upstr = "a";
                upstr[0] = toupper(el.key()[0]);
                RandIndex = GetRandomIndex(Map_Obj["basic"]["alphabet"][RoundKeyMatch(upstr)].size());
                return Map_Obj["basic"]["alphabet"][RoundKeyMatch(upstr)][RandIndex];
            }
        }
    }else if(NUMBERSYMBOL.find(letter) != string::npos){
        if(NUMBERS.find(letter) != string::npos){ //数字正着查速度快
            for (auto& el : Map_Obj["basic"]["numbersymbol"].items())
            {
                if(el.key() == letter){
                    RandIndex = GetRandomIndex(Map_Obj["basic"]["numbersymbol"][RoundKeyMatch(el.key())].size()); //随机获取一个下标
                    return Map_Obj["basic"]["numbersymbol"][RoundKeyMatch(el.key())][RandIndex];
                }
            }
        }else{
            for (auto el =  Map_Obj["basic"]["numbersymbol"].rbegin(); el != Map_Obj["basic"]["numbersymbol"].rend(); ++el)
            {
                if(el.key() == letter){
                    RandIndex = GetRandomIndex(Map_Obj["basic"]["numbersymbol"][RoundKeyMatch(el.key())].size()); //随机获取一个下标
                    return Map_Obj["basic"]["numbersymbol"][RoundKeyMatch(el.key())][RandIndex];
                }
            }
        }
    }
    return NULL_STR;
}
string FindOriginText(string& letter){
    for (auto& el : Map_Obj["basic"]["alphabet"].items()){
        for (auto ell : el.value()){
            string str = (string)ell;
            if(letter == str){
                return DRoundKeyMatch(el.key());
            }
        }
    }
    for (auto& el : Map_Obj["basic"]["numbersymbol"].items()){
        for (auto ell : el.value()){
            string str = (string)ell;
            if(letter == str){
                return DRoundKeyMatch(el.key());
            }
        }
    }
    return "";
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
inline string RoundKeyMatch(const string& keyIn){ //查询轮换密钥的键值

    size_t idx1,idx2;
    size_t idx1_1,idx2_1;
    size_t idx1_2,idx2_2;

    idx1 = LETTERS.find(keyIn);
    idx2 = NUMBERSYMBOL.find(keyIn);

    idx1_1 = LETTERS.find(LETTERS_ROUND_1[idx1]);
    idx2_1 = NUMBERSYMBOL.find(NUMBERSYMBOL_ROUND_1[idx2]);

    idx1_2 = LETTERS.find(LETTERS_ROUND_2[idx1_1]);
    idx2_2 = NUMBERSYMBOL.find(NUMBERSYMBOL_ROUND_2[idx2_1]);

    if(idx1 != string::npos){//判断给定字符的类型
        return LETTERS_ROUND_3.substr(idx1_2,1);
    }else if(idx2 != string::npos){
        return NUMBERSYMBOL_ROUND_3.substr(idx2_2,1);
    }

    return NULL_STR;
}
inline string DRoundKeyMatch(const string& keyIn){ //查询轮换密钥的键值

    size_t idx1,idx2;
    size_t idx1_1,idx2_1;
    size_t idx1_2,idx2_2;

    idx1 = LETTERS_ROUND_3.find(keyIn);
    idx2 = NUMBERSYMBOL_ROUND_3.find(keyIn);

    idx1_1 = LETTERS_ROUND_2.find(LETTERS[idx1]);
    idx2_1 = NUMBERSYMBOL_ROUND_2.find(NUMBERSYMBOL[idx2]);

    idx1_2 = LETTERS_ROUND_1.find(LETTERS[idx1_1]);
    idx2_2 = NUMBERSYMBOL_ROUND_1.find(NUMBERSYMBOL[idx2_1]);


    if(idx1 != string::npos){//判断给定字符的类型
        return LETTERS.substr(idx1_2,1);
    }else if(idx2 != string::npos){
        return NUMBERSYMBOL.substr(idx2_2,1);
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
        rotateString(LETTERS_ROUND_1,6); //将第一个密钥轮向右轮6位
        rotateString(NUMBERSYMBOL_ROUND_1,6);

        LrotateString(LETTERS_ROUND_2, ControlNum*2); //将第二个密钥轮向左轮ControlNum*2位
        LrotateString(NUMBERSYMBOL_ROUND_2, ControlNum*2);

        rotateString(LETTERS_ROUND_3, (ControlNum/2)+1); //将第三个密钥轮向右轮ControlNum/2+1位
        rotateString(NUMBERSYMBOL_ROUND_3, (ControlNum/2)+1);
    }else{ //操作数是奇数
        LrotateString(LETTERS_ROUND_1,3); //将第一个密钥轮向左轮3位
        LrotateString(NUMBERSYMBOL_ROUND_1,3);

        rotateString(LETTERS_ROUND_2, ControlNum); //将第二个密钥轮向右轮ControlNum位
        rotateString(NUMBERSYMBOL_ROUND_2, ControlNum);

        LrotateString(LETTERS_ROUND_3, (ControlNum+7)/2); //将第三个密钥轮向左轮(ControlNum+5)/2位
        LrotateString(NUMBERSYMBOL_ROUND_3, (ControlNum+7)/2);
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

void AES_256_CTR(string& key,vector<uint8_t>& data, const int* randomByte) { //执行AES_256_CTR加密
    AES_ctx ctx;
    vector<uint8_t> KeyHashV = SHA256(String2Uint8T(key));
    vector<uint8_t> KeyHash{KeyHashV};

    KeyHashV.push_back(randomByte[0]);
    KeyHashV.push_back(randomByte[1]);
    
    vector<uint8_t> iv = SHA256(KeyHashV); //对密钥的第二次哈希
    //初始化向量直接使用密钥两次哈希的前16字节，这么做不是最佳实践。
    //但是，本项目不会特别把初始化向量另外保存，这样会显著增加密文长度。

    AES_init_ctx_iv(&ctx,KeyHash.data(),iv.data());
    AES_CTR_xcrypt_buffer(&ctx, data.data(), data.size());
}

int GetLuhnBit(vector<uint8_t>& data){ //计算数据的卢恩校验码
    vector<unsigned int> Digit;
    unsigned int num,digit;
    for(unsigned int i = 0;i<data.size();i++){ //一重循环
        num = data[i]; //取字节。
        while(num > 0){ //取字节值的每一位数字
            digit = num % 10; // 取得最低位数
            Digit.push_back(digit);
            num /= 10; //除去十
        }
    }

    // Digit应当是一个数位构成的数组。
    int sum = 0;
    int Check;
    for(unsigned int i = 0;i<Digit.size();i++){
        if( i % 2 != 0){ //从0开始的奇数位
         Digit[i] = Digit[i]*2; //奇数位乘二 , 最大18
         if(Digit[i] >= 10){ //如果大于等于十
            Digit[i] = (Digit[i] % 10) + (Digit[i] / 10); //计算数字之和
         }
        }
        sum += (int)Digit[i];
    }

    Check = 10 - (sum % 10);

    return Check;
}

bool CheckLuhnBit(vector<uint8_t> data){ //检查数据的卢恩校验码
    int DCheck = (int)data.at(data.size()-1);
    data.pop_back();
    int Check = GetLuhnBit(data);
    
    if(Check == DCheck){
        return true;
    }else{
        return false;
    }
}

std::vector<uint8_t> GZIP_COMPRESS(std::vector<uint8_t> Data){
    string RawStringData(Data.begin(),Data.end());
    string compressedData = gzip::compress(RawStringData.c_str(),RawStringData.size());

    if(RawStringData.size() < compressedData.size()){
        return Data; //如果压缩出来的东西反而更大，那么直接返回原数据。
    }
    return String2Uint8T(compressedData);
}

std::vector<uint8_t> GZIP_DECOMPRESS(std::vector<uint8_t> Data){

    string RawStringData(Data.begin(),Data.end());

    if(gzip::is_compressed(RawStringData.c_str(),RawStringData.size()) == false){
        return Data; //如果数据没压缩，那么直接原样返回回去
    }

    string compressedData = gzip::decompress(RawStringData.c_str(),RawStringData.size());
    return String2Uint8T(compressedData);
}

std::vector<uint8_t> UNISHOX_COMPRESS(std::vector<uint8_t> Data){
    string Datastr(Data.begin(),Data.end());
    const char* DataStrCharArray = Datastr.c_str();
    char* CompressedStrCharArray = new char[2048]; //此压缩法的上限是1kb, 额外1kb冗余
    unsigned int libmark = 255;
    //搜索字符串。
    for(int i=1;i<6;i++){
        if(Datastr.find(CHINESE_WEBPAN_LIB[i]) != string::npos){
            libmark = 254;
            break;
        }
        if(Datastr.find(INTER_WEBPAN_LIB[i]) != string::npos){
            libmark = 245;
            break;
        }
    }
    if(libmark == 255){
        for(int i=1;i<6;i++){
            if(Datastr.find(CHINESE_WEBSITE_LIB[i]) != string::npos){
                libmark = 253;
                break;
            }
            if(Datastr.find(INTER_WEBSITE_LIB[i]) != string::npos){
                libmark = 252;
                break;
            }
            if(Datastr.find(INTER_WEBSITE_LIB_2[i]) != string::npos){
                libmark = 244;
                break;
            }
            if(Datastr.find(JAPAN_WEBSITE_LIB[i]) != string::npos){
                libmark = 251;
                break;
            }
            if(Datastr.find(PIRACY_WEBSITE_LIB[i]) != string::npos){
                libmark = 250;
                break;
            }
        }
    }
    if(libmark == 255){
        for(int i=1;i<6;i++){
            if(Datastr.find(GENERIC_TLINK_LIB[i]) != string::npos){
                libmark = 249;
                break;
            }
            if(Datastr.find(GENERIC_LINK_LIB_1[i]) != string::npos){
                libmark = 248;
                break;
            }
            if(Datastr.find(GENERIC_LINK_LIB_2[i]) != string::npos){
                libmark = 247;
                break;
            }
            if(Datastr.find(GENERIC_LINK_LIB_3[i]) != string::npos){
                libmark = 246;
                break;
            }
        }
    }
    
    int CompressedStrCharLength;
    switch(libmark){
        case 255:
            CompressedStrCharLength = unishox2_compress_simple(DataStrCharArray ,Datastr.length(), CompressedStrCharArray);
            break;
        case 254:
            CompressedStrCharLength = unishox2_compress(DataStrCharArray,Datastr.length(),CompressedStrCharArray,USX_HCODES_DFLT,USX_HCODE_LENS_DFLT,CHINESE_WEBPAN_LIB,USX_TEMPLATES);
            break;
        case 245:
            CompressedStrCharLength = unishox2_compress(DataStrCharArray,Datastr.length(),CompressedStrCharArray,USX_HCODES_DFLT,USX_HCODE_LENS_DFLT,INTER_WEBPAN_LIB,USX_TEMPLATES);
            break;
        case 253:
            CompressedStrCharLength = unishox2_compress(DataStrCharArray,Datastr.length(),CompressedStrCharArray,USX_HCODES_DFLT,USX_HCODE_LENS_DFLT,CHINESE_WEBSITE_LIB,USX_TEMPLATES);
            break;
        case 252:
            CompressedStrCharLength = unishox2_compress(DataStrCharArray,Datastr.length(),CompressedStrCharArray,USX_HCODES_DFLT,USX_HCODE_LENS_DFLT,INTER_WEBSITE_LIB,USX_TEMPLATES);
            break;
        case 244:
            CompressedStrCharLength = unishox2_compress(DataStrCharArray,Datastr.length(),CompressedStrCharArray,USX_HCODES_DFLT,USX_HCODE_LENS_DFLT,INTER_WEBSITE_LIB_2,USX_TEMPLATES);
            break;
        case 251:
            CompressedStrCharLength = unishox2_compress(DataStrCharArray,Datastr.length(),CompressedStrCharArray,USX_HCODES_DFLT,USX_HCODE_LENS_DFLT,JAPAN_WEBSITE_LIB,USX_TEMPLATES);
            break;
        case 250:
            CompressedStrCharLength = unishox2_compress(DataStrCharArray,Datastr.length(),CompressedStrCharArray,USX_HCODES_DFLT,USX_HCODE_LENS_DFLT,PIRACY_WEBSITE_LIB,USX_TEMPLATES);
            break;
        case 249:
            CompressedStrCharLength = unishox2_compress(DataStrCharArray,Datastr.length(),CompressedStrCharArray,USX_HCODES_DFLT,USX_HCODE_LENS_DFLT,GENERIC_TLINK_LIB,USX_TEMPLATES);
            break;
        case 248:
            CompressedStrCharLength = unishox2_compress(DataStrCharArray,Datastr.length(),CompressedStrCharArray,USX_HCODES_DFLT,USX_HCODE_LENS_DFLT,GENERIC_LINK_LIB_1,USX_TEMPLATES);
            break;
        case 247:
            CompressedStrCharLength = unishox2_compress(DataStrCharArray,Datastr.length(),CompressedStrCharArray,USX_HCODES_DFLT,USX_HCODE_LENS_DFLT,GENERIC_LINK_LIB_2,USX_TEMPLATES);
            break;
        case 246:
            CompressedStrCharLength = unishox2_compress(DataStrCharArray,Datastr.length(),CompressedStrCharArray,USX_HCODES_DFLT,USX_HCODE_LENS_DFLT,GENERIC_LINK_LIB_3,USX_TEMPLATES);
            break;
    }
    
    if(CompressedStrCharLength > (int)Datastr.length()){
        return Data;
    }
    std::vector<uint8_t> DataOut;
    DataOut.reserve(CompressedStrCharLength);
    for(int i=0;i<CompressedStrCharLength;i++){
       DataOut.push_back(CompressedStrCharArray[i]); //把压缩之后的字节写进容器。
    }
    DataOut.push_back(libmark);
    DataOut.push_back(255); //2个标志位
    delete[] CompressedStrCharArray;
    return DataOut;
}

std::vector<uint8_t> UNISHOX_DECOMPRESS(std::vector<uint8_t> Data){
    if(Data.at(Data.size()-1) != 255 ||
      (Data.at(Data.size()-2) < 244 || Data.at(Data.size()-2) > 255)){ //没查到标志位即表示没有压缩。
        return Data;
    }
    unsigned int libmark = Data.at(Data.size()-2);

    Data.pop_back();
    Data.pop_back();

    string Datastr(Data.begin(),Data.end());
    const char* DataStrCharArray = Datastr.c_str();
    char* DecompressedStrCharArray = new char[2048]; //此压缩法的上限是1kb, 额外1kb冗余

    
    int DecompressedStrCharLength;
    switch(libmark){
        case 255:
            DecompressedStrCharLength = unishox2_decompress_simple(DataStrCharArray ,Datastr.length(), DecompressedStrCharArray);
            break;
        case 254:
            DecompressedStrCharLength = unishox2_decompress(DataStrCharArray,Datastr.length(),DecompressedStrCharArray,USX_HCODES_DFLT,USX_HCODE_LENS_DFLT,CHINESE_WEBPAN_LIB,USX_TEMPLATES);
            break;
        case 245:
            DecompressedStrCharLength = unishox2_decompress(DataStrCharArray,Datastr.length(),DecompressedStrCharArray,USX_HCODES_DFLT,USX_HCODE_LENS_DFLT,INTER_WEBPAN_LIB,USX_TEMPLATES);
            break;
        case 253:
            DecompressedStrCharLength = unishox2_decompress(DataStrCharArray,Datastr.length(),DecompressedStrCharArray,USX_HCODES_DFLT,USX_HCODE_LENS_DFLT,CHINESE_WEBSITE_LIB,USX_TEMPLATES);
            break;
        case 252:
            DecompressedStrCharLength = unishox2_decompress(DataStrCharArray,Datastr.length(),DecompressedStrCharArray,USX_HCODES_DFLT,USX_HCODE_LENS_DFLT,INTER_WEBSITE_LIB,USX_TEMPLATES);
            break;
        case 244:
            DecompressedStrCharLength = unishox2_decompress(DataStrCharArray,Datastr.length(),DecompressedStrCharArray,USX_HCODES_DFLT,USX_HCODE_LENS_DFLT,INTER_WEBSITE_LIB_2,USX_TEMPLATES);
            break;
        case 251:
            DecompressedStrCharLength = unishox2_decompress(DataStrCharArray,Datastr.length(),DecompressedStrCharArray,USX_HCODES_DFLT,USX_HCODE_LENS_DFLT,JAPAN_WEBSITE_LIB,USX_TEMPLATES);
            break;
        case 250:
            DecompressedStrCharLength = unishox2_decompress(DataStrCharArray,Datastr.length(),DecompressedStrCharArray,USX_HCODES_DFLT,USX_HCODE_LENS_DFLT,PIRACY_WEBSITE_LIB,USX_TEMPLATES);
            break;
        case 249:
            DecompressedStrCharLength = unishox2_decompress(DataStrCharArray,Datastr.length(),DecompressedStrCharArray,USX_HCODES_DFLT,USX_HCODE_LENS_DFLT,GENERIC_TLINK_LIB,USX_TEMPLATES);
            break;
        case 248:
            DecompressedStrCharLength = unishox2_decompress(DataStrCharArray,Datastr.length(),DecompressedStrCharArray,USX_HCODES_DFLT,USX_HCODE_LENS_DFLT,GENERIC_LINK_LIB_1,USX_TEMPLATES);
            break;
        case 247:
            DecompressedStrCharLength = unishox2_decompress(DataStrCharArray,Datastr.length(),DecompressedStrCharArray,USX_HCODES_DFLT,USX_HCODE_LENS_DFLT,GENERIC_LINK_LIB_2,USX_TEMPLATES);
            break;
        case 246:
            DecompressedStrCharLength = unishox2_decompress(DataStrCharArray,Datastr.length(),DecompressedStrCharArray,USX_HCODES_DFLT,USX_HCODE_LENS_DFLT,GENERIC_LINK_LIB_3,USX_TEMPLATES);
            break;
    }
    
    std::vector<uint8_t> DataOut;
    DataOut.reserve(DecompressedStrCharLength);
    for(int i=0;i<DecompressedStrCharLength;i++){
       DataOut.push_back(DecompressedStrCharArray[i]); //把压缩之后的字节写进容器。
    }
    delete[] DecompressedStrCharArray;
    return DataOut;
}