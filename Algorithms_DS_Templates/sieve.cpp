#include<bits/stdc++.h>
using namespace std;

vector<bool> prime;

void sieve(int n)
{
    for(int i=0;i<=n;++i)
    {
        prime.push_back(true);
    }
    prime[0]=false;
    prime[1]=false;
    for(long long i=2;i*i<=n;++i)
    {
        if(prime[i])
        {
            for(int j=i*i;j<=n;j=j+i)
            {
                prime[j]=false;
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
}