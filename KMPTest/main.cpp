#include<iostream>
#include<vector>
using namespace std;
/*
 * Created by rxl on 16-10-25.
 *
 * 本题目求得是模式串在原串中出现的次数。
 * 我们通过在模式串的最后一位添加一个特殊字符$当模式串走到最后一位时候退回到新的位置进行比较
 */
void NextArrayCal(string &str,vector<int> &next)
{
    int j=0,k=-1;
    next[0]=-1;
    while(j<str.size()-1)
    {
        if(k==-1||str[j]==str[k])
        {
            j++,k++;
            if(str[j]!=str[k])
                next[j]=k;
            else
                next[j]=next[k];
            next[j]=k;
        }
        else
            k=next[k];
    }
}
int KMPindex(string &str,string&pat)
{
    vector<int>next(pat.size());
    NextArrayCal(pat,next);
    int i=0,j=0;
    int res=0;
    int strsize=str.size(),patsize=pat.size();
    while(i<strsize)
    {

        if(j==-1||str[i]==pat[j])
        {
            i++;j++;

        }
        else{
            j=next[j];
        }
        if(j>=patsize-1)
        {
            ++res;
            j=next[patsize-1];

        }
    }

    return res;
}
/*
 * 样例输入:
 * 5
 *HA
 *HAHAHA
 */
int main()
{
    int tn;
    cin>>tn;
    string str;
    string pat;
    str.reserve(1000008);
    pat.reserve(10008);
    for(int ye=0;ye<tn;++ye)
    {
        cin>>pat;
        pat+="$";
        cin>>str;
        cout<< KMPindex(str,pat)<<endl;
    }
}