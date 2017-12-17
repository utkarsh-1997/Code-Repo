//Reference: https://blog.anudeep2011.com/heavy-light-decomposition/

#include<bits/stdc++.h>

using namespace std;

//Everything is 0-based indexing

#define MAXN 100003
#define LOGMAXN 18

vector<int> graph[MAXN];

bool visited[MAXN];

int depth[MAXN], parent[MAXN], subtree_size[MAXN];

int dp[MAXN][LOGMAXN];

int chain_no, chain_head[MAXN], chain_pos[MAXN], chain_ind[MAXN], chain_size[MAXN];


void DFS(int node, int dpth)
{
	subtree_size[node] = 1;
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
	for(int i = 0 ; i < graph[node].size(); i++)
	{
		if(parent[graph[node][i]] == node)
			subtree_size[node]+=subtree_size[graph[node][i]];
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

//Now we will do HLD of the tree

void preprocess_hld()
{
	for(int i = 0 ; i < MAXN; i++)
		chain_head[i] = -1;
}

void hld(int node)
{
	if(chain_head[chain_no] == -1)
		chain_head[chain_no] = node;
	chain_ind[node] = chain_no;
	chain_pos[node] = chain_size[chain_no];
	chain_size[chain_no]++;
	int index = -1, max_size = -1;
	for(int i = 0 ; i < graph[node].size(); i++)
	{
		if(parent[graph[node][i]] == node)
		{
			if(subtree_size[graph[node][i]]>max_size)
			{
				max_size=subtree_size[graph[node][i]];	
				index = i;
			}
		}
	}
	if(index >= 0)
		hld(graph[node][index]);
	for(int i = 0 ; i < graph[node].size(); i++)
	{
		if(i != index && parent[graph[node][i]] == node)
		{
			chain_no++;
			hld(graph[node][i]);
		}
	}
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
	preprocess_hld();
	hld(0);
	return 0;
}
