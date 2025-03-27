#include <bits/stdc++.h>
#define int long long
#define double long double
#define endl '\n'
#define rep(i,n) for(int i=0; i<(n); ++i)
#define fup(i,a,b) for(int i=(a); i<(b); ++i)
#define fdn(i,a,b) for(int i=(a); i>(b); --i)
#define vi vector<int>
#define pb push_back
#define ins insert
#define SZ(a) (int)(a).size()
#define pii pair<int, int>
#define mp(a,b) make_pair((a), (b))
using namespace std;
#define oo 1000000007
#define mod 1000000007
#define kN 4003
struct P{int x, y; P(){} P(int x, int y):x(x), y(y){}};
int n, m, a[kN], cc[kN];
string s[kN];
vector<int> G[kN], C[kN];
int cli[kN], deg[kN];
int p[kN];
void init(int n){rep(i, n)p[i]=i;}
int Find(int x){return x==p[x]?x:p[x]=Find(p[x]);}
bool Union(int x, int y){return Find(x)==Find(y)?0:(p[Find(x)]=Find(y), 1);}

signed main(){
	ios::sync_with_stdio(0), cin.tie(0);
	int T; cin>>T;
	while(T--){
		cin>>n;
		rep(i, n)cin>>s[i], G[i].clear(), C[i].clear();
		init(n);
		rep(i, n)fup(j, i+1, n)if(s[i][j]==49)G[i].pb(j), G[j].pb(i), Union(i, j);
		rep(i, n)cc[i]=Find(i);
		rep(i, n)C[cc[i]].pb(i);
		rep(i, n)if(C[i].size()){
			int m=C[i].size(), cnt=0;
			for(int j:C[i])if(G[j].size()==m-1)++cnt;
			if(cnt==m){cli[i]=-1; continue;}
			if(cnt){
				for(int j:C[i])if(G[j].size()!=m-1){cli[i]=j; break;}
				continue;
			}
			for(int j:C[i])p[j]=j, deg[j]=0;
			for(int j:C[i])for(int k:G[j])if(Union(j, k))++deg[j], ++deg[k];
			for(int j:C[i])if(deg[j]==1){cli[i]=j; break;}
		}
		int cnt=0;
		rep(i, n)if(C[i].size())++cnt;
		if(cnt==1){cout<<"0\n"; continue;}
		int ok=-1;
		rep(i, n)if(C[i].size()&&cli[i]!=-1){ok=cli[i]; break;}
		if(~ok)cout<<"1\n"<<ok+1<<endl;
		else{
			int id=-1;
			rep(i, n)if(C[i].size()&&(id==-1||C[i].size()<C[id].size()))id=i;
			if(C[id].size()>=3&&cnt>=3){
				int i=0;
				for(; i<n; ++i)if(C[i].size())break;
				int j=i+1;
				for(; j<n; ++j)if(C[j].size())break;
				cout<<"2\n"<<C[i][0]+1<<' '<<C[j][0]+1<<endl;
				continue;
			}
			cout<<C[id].size()<<endl;
			for(int i:C[id])cout<<i+1<<' ';
			cout<<endl;
			//cout<<"here\n";
		}

	}
}
