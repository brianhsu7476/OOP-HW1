#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <cassert>
#include <optional>
using namespace std;

class dsu{
	vector<int> p;
public:
	void reset(int i){
		assert((int)p.size()>i);
		p[i]=i;
	}
	void init(int n){
		p.resize(n);
		for(int i=0; i<n; ++i)reset(i);
	}
	int Find(int x){
		if(x==p[x])return x;
		p[x]=Find(p[x]);
		return p[x];
	}
	bool Union(int x, int y){
		if(Find(x)==Find(y))return false;
		p[Find(x)]=Find(y);
		return true;
	}
};

class graph{
	int n, m;
	vector<vector<int>> G, Component;
	vector<int> inComponent, vertexChosen, deg;
	vector<string> s;
	dsu d;
public:
	void addEdge(int u, int v){
		G[u].push_back(v), G[v].push_back(u);
		d.Union(u, v);
	}
	bool isClique(int i){
		for(int j:Component[i])if(G[j].size()+1!=Component[i].size())return false;
		return true;
	}
	bool isSun(int i){
		for(int j:Component[i])if(G[j].size()+1==Component[i].size())return true;
		return false;
	}
	int componentsCount(){
		int cnt=0;
		for(int i=0; i<n; ++i)if(Component[i].size())++cnt;
		return cnt;
	}
	void initFromInput(){
		cin>>n;
		s.resize(n), G.resize(n), Component.resize(n), inComponent.resize(n), vertexChosen.resize(n), deg.resize(n);
		for(string &x:s)cin>>x;
		d.init(n);
		for(int i=0; i<n; ++i)for(int j=i+1; j<n; ++j)if(s[i][j]=='1')addEdge(i, j);
		for(int i=0; i<n; ++i)inComponent[i]=d.Find(i);
		for(int i=0; i<n; ++i)Component[inComponent[i]].push_back(i);
	}
	void chooseVertices(){
		for(int i=0; i<n; ++i)if(Component[i].size()){
			if(isClique(i)){
				vertexChosen[i]=-1;
				continue;
			}
			if(isSun(i)){
				for(int j:Component[i])if(G[j].size()+1!=Component[i].size()){
					vertexChosen[i]=j;
					break;
				}
				continue;
			}
			for(int j:Component[i])d.reset(j), deg[j]=0;
			for(int j:Component[i])for(int k:G[j])if(d.Union(j, k))++deg[j], ++deg[k];
			for(int j:Component[i])if(deg[j]==1){
				vertexChosen[i]=j; break;
			}
		}
	}
	void output(){
		int cnt=componentsCount();
		if(cnt==1){
			cout<<"0\n";
			return;
		}
		{
			optional<int> result;
			for(int i=0; i<n; ++i)if(!Component[i].empty()&&vertexChosen[i]!=-1){result=vertexChosen[i]; break;}
			if(result){
				cout<<"1\n"<<result.value()+1<<endl;
				return;
			}
		}
		pair<int,int> result={INT_MAX, 0};
		auto &[size, id]=result;
		for(int i=0; i<n; ++i)if(!Component[i].empty())result=min(result, {(int)Component[i].size(), i});
		if(size>=3&&cnt>=3){
			int i=0;
			for(; i<n; ++i)if(!Component[i].empty())break;
			int j=i+1;
			for(; j<n; ++j)if(!Component[j].empty())break;
			cout<<"2\n"<<Component[i][0]+1<<' '<<Component[j][0]+1<<endl;
			return;
		}
		cout<<size<<endl;
		for(int i:Component[id])cout<<i+1<<' ';
		cout<<endl;
	}
};

void solve(){
	graph g;
	dsu d;
	g.initFromInput();
	g.chooseVertices();
	g.output();
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	int T; cin>>T;
	while(T--)solve();
}
