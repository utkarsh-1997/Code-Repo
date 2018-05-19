// Constructs a segment tree. Leaf node stores values of array A
// Query: Find the sum of integers in range [L, R] (1-based indexing).
// Point updates: Update A[i] = some_new_value

// No referral, wrote it myself

#include<bits/stdc++.h>

using namespace std;

#define MAXN 100003

int A[MAXN], tree[4*MAXN];

//To build the tree
void build(int node, int start, int end)
{
	if(start == end)
	{
		tree[node] = A[start];
	}
	else
	{
		int mid = (start+end)/2;
		build(2*node, start, mid);
		build(2*node+1, mid+1, end);
		tree[node] = tree[2*node] + tree[2*node+1];
	}
}

// This query functions returns the sum of integers in range [L, R] (1-based indexing).
int query(int node, int start, int end, int L, int R)
{
	if(start > end || L > end || R < start)
		return 0;

	if(L<=start && R>=end)
	{
		return tree[node];
	}
	else
	{
		int mid = (start+end)/2;
		return query(2*node, start, mid, L, R) + query(2*node+1, mid+1, end, L, R);
	}
}

//To make point updates
void update(int node, int start, int end, int val, int idx)
{
	if(start == end)	//will also be == idx
		tree[node] = val;
	else
	{
		int mid = (start+end)/2;
		if(idx <= mid)
			update(2*node, start, mid, val, idx);
		else
			update(2*node+1, mid+1, end, val, idx);
		tree[node] = tree[2*node] + tree[2*node+1];
	}
}

int main()
{
	int N;
	cin>>N;
	for(int i = 0; i < N; i++)
		cin>>A[i];
	build(1, 0, N-1);
	
	int val, idx;
	cin>>val>>idx;
	update(1, 0, N-1, val, idx);

	int L, R;
	cin>>L>>R;
	cout<<query(1, 0, N-1, L-1, R-1)<<endl;
	return 0;
}