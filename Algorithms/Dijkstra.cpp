// Remmber that Dijkstra's algorithm works only for positive weights.

#include<bits/stdc++.h>

using namespace std;

void findShortestDistances(int N, int start_node, int shortestDistance[], vector<pair<int, int>> graph[])
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;	
	bool visited[N] = {};	// Instead of initializing distances to a "MAX" value we make use of a bool variable which checks whether the node is being visited for the first time
	visited[start_node] = 1;
	Q.push(make_pair(0, start_node));
	while(!Q.empty())
	{
		pair<int, int> P = Q.top();
		Q.pop();
		int curnode = P.second, curdistance = P.first;
		cout<<"LOL "<<curnode<<" "<<curdistance<<endl;
		for(int i = 0; i < graph[curnode].size(); i++)
		{
			int neighbour = graph[curnode][i].second, cost = graph[curnode][i].first;
			if(visited[neighbour] == 1)
			{
				if(cost + curdistance < shortestDistance[neighbour])
				{
					shortestDistance[neighbour] = cost + curdistance;
					Q.push(make_pair(shortestDistance[neighbour], neighbour));
				}
			}
			else
			{
				shortestDistance[neighbour] = cost + curdistance;
				visited[neighbour] = 1;
				Q.push(make_pair(shortestDistance[neighbour], neighbour));
			}
		}
	}
	for(int i = 0; i < N; i++)
	{
		if(!visited[i])
			shortestDistance[i] = -1;	//This node wasn't reachable!
	}
}

// Undirected graph. Graph input format: First take N - number of nodes (labelled from 0 to N-1) and M - number of edges.
// Then, M lines where inputs are u, v and c, denoting an edge between u and v with weight c. 
int main()
{
	int N, M;
	cin>>N>>M;
	vector<pair<int, int>> graph[N];
	int u, v, c;
	for(int i = 0; i < M; i++)
	{
		cin>>u>>v>>c;
		graph[u].push_back(make_pair(c, v));
		graph[v].push_back(make_pair(c, u));
	}
	// The node where we will start from.
	int start_node;
	cin>>start_node;
	int shortestDistance[N];
	shortestDistance[start_node] = 0;	// Naturally
	findShortestDistances(N, start_node, shortestDistance, graph);
	cout<<"Printing the shortest distance of each node from starting node = "<<start_node<<"\n";
	for(int i = 0; i < N; i++)
		cout<<shortestDistance[i]<<" ";
	cout<<"\n";
	return 0;
}
