#include<bits/stdc++.h>

using namespace std;

//Everything is 0-based indexing

#define MAXN 100003
#define LOGMAXN 18

vector<int> graph[MAXN];

bool visited[MAXN];

int depth[MAXN], parent[MAXN];

int dp[MAXN][LOGMAXN];

void DFS(int node, int dpth)
{
	visited[node] = 1;
	depth[node] = dpth;
	for(int i = 0 ; i < graph[node].size(); i++)
	{
		if(!visited[graph[node][i]])
		{
			parent[graph[node][i]] = node;
			DFS(graph[node][i], dpth+1);
		}
	}
}


void process_tree()
{
	parent[0] = -1;
	DFS(0, 0);
}


void preprocess_lca(int N)
{
	//Initialize DP. DP[i][j] stores the parent of node i at height 2^i from node.
	for(int i = 0 ; i < N ; i++)
	{
		for(int j = 0 ; (1<<j) < N; j++)
		{
			dp[i][j] = -1;
		}
	}
	//At height 2^0 = 1, DP[node][0] = parent[node]
	for(int i = 0; i < N ; i ++)
	{
		dp[i][0] = parent[i];
	}
	//Now start computing
	for(int j = 1; (1<<j) < N; j++)
	{
		for(int i = 0 ; i < N ; i++)
			if(dp[i][j-1] != -1)
				dp[i][j] = dp[dp[i][j-1]][j-1];
	}
}

int lca(int u, int v)
{
	u--, v--;
	if(depth[u] < depth[v])
		swap(u, v);
	int log = 0;
	//First, bring u to same level as that of v
	while((1 << log) <= depth[u]) //for "<", log will exceed unless 1<<log == depth[u], and needs to be decreased eventually
		log++;
	log--;
	for(int i = log; i>=0; i--)
		if(depth[u] - (1<<i) >= depth[v])
			u = dp[u][i];
	//now ensured same level
	if(u == v)
		return u;
	//now start going up
	for(int i = log; i>=0; i--)
	{
		if (dp[u][i] != -1 && dp[u][i] != dp[v][i])
   	    	u = dp[u][i], v = dp[v][i];
	}
	return parent[u];
}

int main()
{
	int N;
	cin>>N;
	int u, v;
	for(int i = 0 ; i < N-1 ; i++)
	{
		cin>>u>>v;
		u--, v--;
		graph[v].push_back(u);
		graph[u].push_back(v);
	}
	process_tree();
	preprocess_lca(N);
	cout<<"Enter u and v whose LCA you want to find."<<endl;
	cin>>u>>v;
	cout<<(lca(u, v)+1)<<endl;
}
