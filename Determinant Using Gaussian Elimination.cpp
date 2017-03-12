/* 
   Author: Utkarsh Singh
   This code computes the determinant of any N*N matrix, using Gaussian Elimination.
   Worst case time complexity: O(N^3)
   Space complexity: O(N^2)
*/

#include<iostream>
 
using namespace std;


int main() 
{
	int N;
	cin>>N;
	cin>>N;
	long double M[N+1][N+1];
	for(int i=1; i<=N; i++)
	{
	    for(int j=1; j<=N; j++)
	    {
	        cin>>M[i][j];
	    }
	}
	bool found=1;
	for(int k=1; k<=N-1; k++)
	{
	    if(M[k][k]==0)
	    {
	        for(int i=k+1; i<=N; i++)
	        {
	            if(M[k][i]!=0)
	            {
	                for(int j=1; j<=N; j++)
	                {
	                    int temp=M[k][j];
	                    M[k][j]=M[i][j];
	                    M[i][j]=temp;
	                }
	                break;
	            }
	        }
	    }
	    if(M[k][k]==0)
	    {
	        cout<<0<<endl;
	        found=false;
	        break;
	    }
	    for(int i=k+1; i<=N; i++)
	    {
	        long double factor=(long double)(M[i][k])/M[k][k];
	        for(int j=1; j<=N; j++)
	        {
	            M[i][j]-=factor*M[k][j];
	        }
	        //cout<<endl;
	    }
	}
	if(found)
	{
	    long double prod=1;
	    for(int i=1; i<=N; i++)
	        prod*=M[i][i];
	    cout<<prod<<endl;
	}
	return 0;
}
