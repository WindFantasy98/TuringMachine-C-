#include <iostream>
#include <string>
using namespace std;
typedef struct node
{
    string k;
    char txt;
    char chtxt;
    char action;
    node *ptn;
} node;
typedef struct map
{
    string k;
    node *ptn;
    map *next;
} map;
void setk(int n, map *m)
{ //初始化链表主侧
    map *pm = m;
    string a;
    while (n--)
    {
        map *nm = new map;
        cin >> a;
        nm->k = a;
        nm->next = 0;
        nm->ptn = 0;   //new map init
        pm->next = nm; //link nm to pm
        pm = nm;       //nm to be last
    }
}
map *search(map *mp, string s)
{
    if (mp != 0)
    {
        map *pmp = mp->next; //pmp指向第一个map节点
        while (pmp != 0)
        {
            if (pmp->k == s) //核对状态是否相同
                return pmp;
            pmp = pmp->next;
        }
        return 0;
    }
    else
        return 0;
}
void buildmap(map *mp)
{
    char ch, txt1, txt2, txt3; //txt1识别字符，txt2转换字符，txt3移动字符
    node *p;
    ch = getchar();
    while (1)
    {
        if ((ch = getchar()) != 'Q')
        {
            if (ch == '#')
                break;
            cout << "输入格式错误：Q" << endl;
        } //除去Q以及检查是否退出
        map *pmp;
        if ((ch = getchar()) != '(')
            cout << "转移函数格式错误:(" << endl;
        string st;
        getline(cin, st, ',');
        pmp = search(mp, st); //找到st状态的指针
        if (!pmp)
            cout << "状态不存在" << endl;
        txt1 = getchar();
        node *nn = new node;
        if ((ch = getchar()) != ')')
            cout << "转移函数格式错误:)" << endl;
        if ((ch = getchar() != '='))
            cout << "转移函数格式错误:=" << endl;
        if ((ch = getchar()) != '(')
            cout << "转移函数格式错误:(" << endl;
        string st2;
        getline(cin, st2, ',');
        txt2 = getchar();
        if ((ch = getchar()) != ',')
            cout << "转移函数格式错误:," << endl;
        txt3 = getchar();
        nn->k = st2;
        nn->txt = txt1;
        nn->chtxt = txt2;
        nn->action = txt3;
        p = pmp->ptn;
        while (pmp->ptn && p->ptn != 0)
        { //不空则转到q1状态下邻接表的最后一个节点
            p = p->ptn;
        }
        nn->ptn = 0;
        if (!p)
            pmp->ptn = nn;
        else
            p->ptn = nn;
        p = nn;
        if ((ch = getchar() != ')'))
            cout << "转移函数格式错误:)" << endl;
        ch = getchar(); //去空格
    }
    cout << "图灵机状态转移函数输入完毕" << endl;
}
void inputtxt(int num, char txt[], char blank)
{
    for (int i = 0; i < num; i++)
        cin >> txt[i];
    for (int j = num; j < 1000; j++)
    {
        txt[j] = blank;
    }
    return;
}
void skipb(char txt[], char blank, int &i)
{ //引用传递，实现i的更新
    while (i < 1000 && txt[i] == blank)
    {
        i++;
    }
}
void transfer(map *mp, string &s1, int &i, char txt[])
{ //引用传递，否则s1、i不会同步更新
    map *pmp;
    pmp = search(mp, s1);
    node *pn = pmp->ptn;
    while (pn) //对s1所表示状态进行邻接表的搜索
    {
        if (pn->txt != txt[i])
            pn = pn->ptn;
        else
            break;
    }
    if (pn == 0)
    {
        cout << "图灵机无法正常停机，请检查图灵机设置" << endl;
        exit(0);
    }
    if (pn->txt != txt[i])
    {
        cout << "纸带无法识别" << endl;
        exit(0);
    }
    txt[i] = pn->chtxt;
    s1 = pn->k;
    if (pn->action == 'R')
        i++;
    else if (pn->action == 'L')
        i--;
    else
        i = i;
}
void deftm(map *mp, string start, string end, char txt[], char blank, int &flag)
{
    int i = 0;
    skipb(txt, blank, i);
    string s = start;
    int pi = 0; //pi作为最大执行步数以检验死循环，实际上有更好的方法
    //具体思路思路：找出纸带上涉及到的所有边，通过并查集验证end是否在集合里
    while (s != end && pi < 1000)
    {
        transfer(mp, s, i, txt);
        pi++;
    }
    if (s != end)
    {
        cout << "该图灵机无法正常停机，请选择：" << endl;
        cout << "[1]重新设置图灵机以及纸带   [2]退出程序" << endl;
        cin >> flag;
        if (flag != 1 || flag != 2)
            cout << "输入错误" << endl;
    }
    else
    {
        flag = 0;
    }
}
void gotm(map *mp, string start, string end, int num, char txt[], char blank)
{
    int i = 0;
    skipb(txt, blank, i);
    string s = start;
    cout << "图灵机步行结果：" << endl;
    while (s != end || txt[i] != blank)
    {
        transfer(mp, s, i, txt);
        for (int j = 0; j < num; j++)
        {
            cout << txt[j];
        }
        cout << endl;
    }
}
void copytxt(char txt1[], char txt2[])
{
    for (int i = 0; i < 1000; i++)
    {
        txt2[i] = txt1[i];
    }
}
int main()
{
    cout << "----------------通用图灵机----------------" << endl;
    cout << "请按任意键继续,按Q键退出" << endl;
    char in;
    while (cin >> in)
    {
        if (in == 'q' || in == 'Q')
            break;
        map *mp = new map;
        mp->next = 0;
        mp->ptn = 0;
        cout << "请输入图灵机状态数：" << endl;
        int kn;
        cin >> kn;
        cout << "请输入图灵机状态：" << endl;
        setk(kn, mp);
        cout << "请输入图灵机开始状态：" << endl;
        string start;
        cin >> start;
        cout << "请输入图灵机终止状态：" << endl;
        string end;
        cin >> end;
        cout << "请输入纸带空白符：" << endl;
        char blank;
        cin >> blank;
        cout << "请输入图灵机状态转移函数：" << endl;
        cout << "参照格式：Q(q1,1)=(q2,2,L)" << endl;
        cout << "         Q(q2,2)-(q1,2,R)" << endl;
        cout << "         # ('#'表示结束)" << endl;
        buildmap(mp);
        cout << "图灵机初始化设置完毕，请输入纸带长度：" << endl;
        int numtxt;
        cin >> numtxt;
        cout << "请输入纸带信息：" << endl;
        char itxt[1000], ttxt[1000];
        inputtxt(numtxt, itxt, blank);
        int flag = 0;
        copytxt(itxt, ttxt);
        deftm(mp, start, end, ttxt, blank, flag);
        if (flag == 0)
        {
            cout << "Congratulations!图灵机可以正常停机" << endl;
            gotm(mp, start, end, numtxt, itxt, blank);
        }
        else if (flag == 1)
            continue; //重新设置图灵机及其纸带
        else if (flag == 2)
            break; //退出该循环
        char in2;
        cout << "是否继续进行测试？Y/N"<<endl;
        while (cin >> in2)
        {
            if (in2 != 'Y' && in2 != 'y')
                break;
            cout << "请输入纸带长度：" << endl;
            int numtxt;
            cin >> numtxt;
            cout << "请输入纸带信息：" << endl;
            char itxt[1000], ttxt[1000];
            inputtxt(numtxt, itxt, blank);
            int flag = 0;
            copytxt(itxt, ttxt);
            deftm(mp, start, end, ttxt, blank, flag);
            if (flag == 0)
            {
                cout << "Congratulations!图灵机可以正常停机" << endl;
                gotm(mp, start, end, numtxt, itxt, blank);
            }
            else if (flag == 1)
                continue;
            else if (flag == 2)
                break;
            cout<<"是否继续进行测试？Y/N"<<endl;
        }
        cout << "按任意键继续，按Q键退出" << endl;
    }
    system("pause");
    return 0;
}