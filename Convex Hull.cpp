#include<bits/stdc++.h>

using namespace std;

struct Point{
	int x, y;
}; Point p0;

Point nextToTop(stack<Point> &S){
	Point p = S.top();
	S.pop();
	Point res = S.top();
	S.push(p);
	return res;
}

int swap(Point &p1, Point &p2){
	Point temp = p1;
	p1 = p2;
	p2 = temp;
}

int distSq(Point p1, Point p2){
	return ((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

int orientation(Point p, Point q, Point r){
	int val = (q.y-p.y)*(r.x-q.x)-(q.x-p.x)*(r.y-q.y);
	if(val == 0) return 0;
	if(val>0) return 1;
	return 2;
}

int compare(const void *vp1, const void *vp2){
	Point *p1 = (Point *)vp1;
	Point *p2 = (Point *)vp2;
	int o = orientation(p0, *p1, *p2);
	if(o == 0) return ((distSq(p0, *p2)) >= distSq(p0, *p1))? -1:1;
	return (o == 2)? -1: 1;
}
//Give points as input in points[], n is size of array, chull_pts is returned
void convexHull(Point points[], int n, vector<Point>&chull_pts){ 	
	int ymin = points[0].y, min = 0;
	for(int i = 1; i < n; i++){
		int y = points[i].y;
		if((y<ymin) || (ymin == y && points[i].x < points[min].x))
			ymin = points[i].y, min = i;
	}
	swap(points[0], points[min]);
	p0 = points[0];
	qsort(&points[1], n-1, sizeof(Point), compare);
	int m = 1;
	for(int i = 1; i<n; i++){
		while(i<n-1 && orientation(p0, points[i], points[i+1])==0)
			i++;
		points[m] = points[i];
		m++;
	}
	if(m < 3) return;

	stack<Point> S;
	S.push(points[0]);
	S.push(points[1]);
	S.push(points[2]);
	for(int i = 3; i<m; i++){
	while(orientation(nextToTop(S), S.top(), points[i]) != 2)  S.pop();
		S.push(points[i]);
	} //Stack S has all the points of CHull in order
	chull_pts.resize(S.size());
	int i = 0;
	while(!S.empty()){
		chull_pts[i++]=(S.top());
		S.pop();
	}
}


long long int Area(vector<Point> chull_pts){
	//returns 2*Area of the convex hull
	int sizehull = chull_pts.size(), j=chull_pts.size()-1;
    long long int area=0;
    for(int i=0; i<sizehull; i++)
    {
        area+=((chull_pts[j].x*chull_pts[i].y)-(chull_pts[i].x*chull_pts[j].y));
        j=i;
    }
    area=abs(area);
    return area;
}

int main()
{
	int N, x, y;
	cout<<setprecision(1)<<fixed;
	cin>>N;
	Point inp, points[N];
	vector<Point> perimeter_pts;
	for(int i = 0 ; i<N; i++)
	{
		cin>>x>>y;
		inp.x = x, inp.y = y;
		points[i] = inp;
	}
	convexHull(points, N, perimeter_pts);
	cout<<Area(perimeter_pts)<<endl;
	return 0;
}
