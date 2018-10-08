#include<bits/stdc++.h>

using namespace std;

//Algorithm for finding the edit distance between 2 strings - i.e. the minimum number of character edits 
//(insertions, deletions or substitutions) required to convert from string A to string B.

//Time and Space Complexity - O(N*M)

int LevenshteinDistance(string A, string B)
{
	//Idea: The number of edits required to convert a string of length i to string of length j will depend on whether
	//		the character we will add next to both strings are equal or not. If yes, no edit cost incurred. Else, the
	//		cost incurred is minimum of that incurred by either inserting a new character into second string, replacing
	//		a character from second string, or removing a character from the second string.
	int N = A.size(), M = B.size();
	int dp[N+1][M+1];
	for(int i = 0; i <= N; i++)
	{
		for(int j = 0; j <= M; j++)
		{
			if(i == 0)
				dp[i][j] = j;	//If A is empty, number of edits = no. of charaters in B
			else
			if(j == 0)
				dp[i][j] = i;
			else
			if(A[i-1] == B[j-1])
				dp[i][j] = dp[i-1][j-1];	//No edit case
			else
				dp[i][j] = 1 + min(dp[i][j-1], min(dp[i-1][j-1], dp[i-1][j]));
		}							//Insert        //Replace	  //Remove
	}
	return dp[N][M];
}

int main()
{
	string A, B;
	cin>>A>>B;
	cout<<LevenshteinDistance(A, B)<<endl;
	return 0;
}