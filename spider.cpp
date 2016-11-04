#include<fstream>
#include<iostream>
#include<string>
#include<queue>
#include<unordered_set>
#include<unistd.h>
#define tr(i,l,r) for((i)=(l);(i)<=(r);++i)
using namespace std;
const int delay=0;
const int maxtags=2000;
const string pre="http://www.cplusplus.com/reference";
const string st1="<div id=\"I_content\">";
const string st2="<div id=\"CH_bb\"></div></div>";
const string st3="class=\"off\"";
const string st4="class=\"on\"";
const string st5="\"<div class=\"C_SwitchCases\">";
const string st6="<div class=\"C_SwitchCases\"><ul><li class=\"on\"><a href=\"javascript:switch1.select(1)\">C++98</a></li><li class=\"on\"><a href=\"javascript:switch1.select(2)\">C++11</a></li><li class=\"on\"><a href=\"javascript:switch1.select(3)\">C++14</a></li></ul>";
const string st7="/reference";
const string st8="</div>";
const string st9="CppReference.htm";
const string st10="<!DOCTYPE html>\n<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n<title>CppReference</title>\n<link rel=\"stylesheet\" type=\"text/css\" href=\"./main.css\">\n</head>\n<body>\n<div id=\"I_mid\">\n<div id=\"I_wrap\">";
const string st11="<h1>\n<span style=\"font-family:verdana, arial, helvetica, sans-serif;background-color:#FFFFFF;color:#E53333;\"><br><a id=\"";
const string st12="\">";
const string st13="</a></span>\n</h1>";
const string st14="<div class=\"C_ad234\">\n</div>\n<div id=\"I_midclear\"></div>\n</div>\n</div>\n</body></html>";
const string st15="<h1>\n<span style=\"font-family:verdana, arial, helvetica, sans-serif;background-color:#FFFFFF;color:#E53333;\">Content</span>\n</h1>";
const string st16="<a href=\"#";
const string st17="<br></a>";
const string st18="<PRE>";
const string st19="</PRE>";
const string st20="     ";
unordered_set<string> erg;
queue<string> q;
string tag[maxtags];
void qpush(string x)
{
    if (erg.count(x)) return ;
    erg.insert(x);
    q.push(x);
}
string transfout(string x){int i;tr(i,0,x.size()-1) if (x[i]=='/') x[i]='#'; return x;}
string rtransfout(string x){int i;tr(i,0,x.size()-1) if (x[i]=='#') x[i]='/'; return x;}
void GetHtml()
{
    string url,buff;
    int t,t2;
    while (!q.empty())
    {
        url=q.front(); q.pop();
        cout<<url;

        system(("wget -q -O temp \""+pre+url+'"').c_str());
        ifstream fin("temp");
        ofstream fout("./res/"+transfout(url));
        while(getline(fin,buff)&&buff.find(st1)==string::npos) ;
        if (buff.find(st1)==string::npos) {cout<<" ERROR!"<<endl; return ;}
        fout<<st1<<endl;
        while(getline(fin,buff)&&buff.find(st2)==string::npos)
        {
            if ((t=buff.find(st3))!=string::npos) buff.replace(t,st3.size(),st4);
            if ((t=buff.find(st5))!=string::npos) buff.replace(t,st5.size(),st6);
            fout<<buff<<endl;
        }
        fout<<st2<<st8<<endl;

        while(getline(fin,buff))
            if ((t=buff.find(st7+url))!=string::npos)
                if (buff[t2=t+(st7+url).size()]=='/'&&buff[++t2]!='"')
                    qpush(url+'/'+buff.substr(t2,buff.find('/',t2)-t2));

        fin.close(); fout.close();
        cout<<" !"<<endl;
        sleep(delay);
    }
}
string countblank(string s)
{
    int bs=0,i;
    string res="";
    tr(i,0,s.size()-1) if (s[i]=='/') bs++;
    tr(i,1,bs-1) res+=st20;
    return res;
}
void MergeHtml()
{
    string buf,buff;
    int tags=0,i;
    cout<<"MERGE";
    system("ls res>temp");
    ifstream fin("temp");
    ofstream fout(st9);
    fout<<st10<<endl<<endl<<endl;
    while(getline(fin,buf))
    {
        tags++;
        fout<<st11<<tags<<st12<<(tag[tags]=rtransfout(buf))<<st13<<endl;
        ifstream ft("./res/"+buf);
        while(getline(ft,buff)) fout<<buff<<endl;
        ft.close();
    }
    fout<<st14<<endl;
    fin.close(); fout.close();

    ofstream fcon("content");
    fcon<<st18<<st15<<endl;
    tr(i,1,tags) fcon<<st16<<i<<st12<<countblank(tag[i])<<tag[i]<<st17<<endl;
    fcon<<st19<<endl;
    fcon.close();

    cout<<" !"<<endl;
}
int main()
{
    //qpush("/cctype");
    //qpush("/cmath");
    //qpush("/cstdio");
    //qpush("/cstdlib");
    //qpush("/cstring");
    //qpush("/deque");
    //qpush("/map");
    //qpush("/queue");
    //qpush("/set");
    //qpush("/unordered_map");
    //qpush("/unordered_set");
    //qpush("/vector");
    //qpush("/ios");
    //qpush("/istream");
    //qpush("/algorithm");
    //qpush("/bitset");
    //qpush("/string");
    //GetHtml();
    MergeHtml();
    return 0;
}
