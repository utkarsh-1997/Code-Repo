// Constructs a merge sort tree. Leaf node stores values of array A

// No referral, wrote it myself

#include<bits/stdc++.h>

using namespace std;

#define MAXN 100003
#define MAXLOGN 19

int A[MAXN], tree[MAXLOGN][4*MAXN];


//To build the tree
void build(int level, int node, int start, int end)
{
	if(start == end)
	{
		tree[level][node] = A[start];
	}
	else
	{
		int mid = (start+end)/2;
		build(level+1, 2*node, start, mid);
		build(level+1, 2*node+1, mid+1, end);
		int i = start, j = mid+1;
		int k = start;
		while(i <= mid && j <= end)
		{
			if(tree[level+1][i]<tree[level+1][j])
			{
				tree[level][k] = tree[level+1][i];
				i++, k++;
			}
			else
			{
				tree[level][k] = tree[level+1][j];
				j++, k++;	
			}
		}
		while(i<=mid)
		{
			tree[level][k] = tree[level+1][i];
			i++, k++;
		}
		while(j<=end)
		{
			tree[level][k] = tree[level+1][j];
			j++, k++;
		}
	}
}

// This query functions returns the count of numbers strictly smaller than K or in range [L, R] in array A (L and R 1-based index)
int query(int level, int node, int start, int end, int K, int L, int R)
{
	if(start > end || L > end || R < start)
		return 0;

	if(L<=start && R>=end)
	{
		return lower_bound(tree[level]+start, tree[level]+end+1, K) - (tree[level]+start);	//If you want to find count of numbers <= K instead, use upper_bound
		// Similarly this function can be modified to find count of numbers in range [K1, K2]
	}
	else
	{
		int mid = (start+end)/2;
		return query(level+1, 2*node, start, mid, K, L, R)+query(level+1, 2*node+1, mid+1, end, K, L, R);
	}
}

int main()
{
	int N;
	cin>>N;
	for(int i = 0; i < N; i++)
		cin>>A[i];
	build(0, 1, 0, N-1);
	int K, L, R;	//Input L, R for 1 based indexing
	cin>>K>>L>>R;
	cout<<query(0, 1, 0, N-1, K, L-1, R-1)<<endl;
	return 0;
}