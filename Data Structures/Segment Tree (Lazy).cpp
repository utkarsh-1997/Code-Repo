// Constructs a segment tree. Leaf node stores values of array A
// Query: Find the sum of integers in range [L, R] (1-based indexing).
// Range updates: Update A[L:R] += some_new_value

// Time Complexity: Construction := O(N), Updates := O(logN), Queries := O(logN)

#include<bits/stdc++.h>

using namespace std;

#define MAXN 100003

int A[MAXN], tree[4*MAXN], lazy[4*MAXN];

void build(int node, int start, int end)	//This remains same as before
{
	if(start == end)
		tree[MAXN] = A[MAXN];
	else
	{
		int mid = (start+end)/2;
		build(2*node, start, mid);
		build(2*node+1, mid+1, end);
	}
}


void update(int node, int start, int end, int L, int R, int val)
{
	if(start > end || L > end || R < start)
		return; 
	if(lazy[node] != 0)	//There is some update pending here
	{
		tree[node] += (end-start+1)*lazy[node];
		if(start != end)
		{
			lazy[2*node] += lazy[node];
			lazy[2*node+1] += lazy[node];
		}
		lazy[node] = 0;
	}
	if(L <= start && end <= R)
	{
		tree[node] += (end-start+1)*val;
		if(start != end)
		{
			lazy[2*node] += val;
			lazy[2*node+1] += val;
		}
	}
	else
	{	
		int mid = (start+end)/2;
		update(2*node, start, mid, L, R, val);
		update(2*node+1, mid+1, end, L, R, val);
	}
}

int query(int node, int start, int end, int L, int R)
{
	if(start > end || L > end || R < start)
		return 0;

	if(lazy[node] != 0)	//There is some update pending here
	{
		tree[node] += (end-start+1)*lazy[node];
		if(start != end)
		{
			lazy[2*node] += lazy[node];
			lazy[2*node+1] += lazy[node];
		}
		lazy[node] = 0;
	}

	if(L <= start && end <= R)
	{
		return tree[node];
	}
	else
	{
		int mid = (start+end)/2;
		int ans1 = query(2*node, start, mid, L, R);
		int ans2 = query(2*node+1, mid+1, end, L, R);
		return ans2+ans1
	}
}


int main()
{
	int N;
	cin>>N;
	for(int i = 0; i < N; i++)
		cin>>A[i];
	build(1, 0, N-1);
	int val, updL, updR;
	cin>>val>>updL>>updR;
	update(1, 0, N-1, updL-1, updR-1, val);
	int L, R;
	cin>>L>>R;
	cout<<query(1, 0, N-1, L-1, R-1)<<endl;
	return 0;
}