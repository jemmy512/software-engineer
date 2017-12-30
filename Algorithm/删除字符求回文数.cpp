
//给定一个字符串s，你可以从中删除一些字符，使得剩下的串是一个回文串。如何删除才能使得回文串最长呢？
//输出需要删除的字符个数

#include <bits/stdc++.h>
using namespace std;

const int MAXN=1010;
int dp[MAXN][MAXN];

class Solution
{
public:
   int solve(string &s)
   {
       return s.length()-getLCS(s);
   }

   int getLCS(string &s1)
   {
       string s2(s1);
       reverse(s2.begin(),s2.end());
       int len=s1.length();
       memset(dp,0,sizeof dp);
       for(int i=0;i<len;++i)
       {
           for(int j=0;j<len;++j)
           {
               if(s1[i]==s2[j])
                   dp[i+1][j+1]=dp[i][j]+1;
               else dp[i+1][j+1]=max(dp[i][j+1],dp[i+1][j]);
           }
       }
       return dp[len][len];
   }
};

int main()
{
   string s;
   while(cin>>s)
   {
       Solution solution;
       cout<<solution.solve(s)<<endl;
   }
   return 0;
}
