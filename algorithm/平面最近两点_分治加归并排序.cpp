#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
using namespace std;
// ********************* 算法证明 ***********************
//
// 我们可以采取分治的策略，将坐标按照横坐标排序，取中点 mid
// 分治：
// min_len = solve(left_part,right_part);
// 此时情况被分成三种：
// [mid - ans, mid]      mid       [mid, mid + ans] 
// 左边、右边任意两点间距离 >= min_len 这点我们可以由分治算法得到
// 对于 交叉的情况，我们在左半边取一点p(x_p,y_p)，寻找右半边中和p距离小于min_len
// 的点q。
// 那么p就可以将右半部分进一步框成纵坐标中点为 y_p 长度为 2*min_len 宽度为 min_len 
// 的矩形。要与p距离小于min_len ，q显然要落在矩形中，
// 我们将矩形分成六份 每个长为2/3*min_len 宽度为1/2*min_len 
// 那么我们有小矩形的对角线长度为5/6*min_len 
// 注意到矩形中任意两点都是右半部分的，那么他们任意两点间的距离显然要超过或等于min_len 
// 也就是他们不能在同一个小矩形中，那么由鸽巢原理，右半边矩形用的点数最多只有6个 
// 我们只需要枚举这六个点，用它们和p点之间的距离更新答案 
//
// ********************* 算法证明 ***********************



// 代码源自：https://blog.csdn.net/weixin_44176696/article/details/105821366
typedef struct Point
{
	int x,y;
	Point(){}
	Point(int _x,int _y) : x(_x),y(_y){}
	bool operator == (const Point & other)const{
		return x == other.x && y == other.y;
	}
	bool operator != (const Point & other)const{
		return *this == other;
	}
}Point;

double lfmin(double a,double b){
	return a < b ? a : b;
}

bool compx(const Point & p1, const Point & p2){
	if(p1.x == p2.x)
		return p1.y < p2.y;
	return p1.x < p2.x;
}

bool compy(const Point & p1, const Point & p2){
	return p1.y < p2.y;
}


double dis(const Point & p1, const Point & p2){
	return sqrt((double)(p1.x - p2.x)*(p1.x - p2.x) + (double)((p1.y - p2.y)*(p1.y - p2.y)));
}


double disX(const Point & p1, const Point &p2){
	double ans = (double)p1.x - (double)p2.x;
	if(ans < 0)
		return ans * (-1);
	return ans;
}

double Solve(vector<Point> & points, int l, int r)
{
	if(l >= r)
		return (double)INT_MAX;
	if(l + 1 == r)
		return dis(points[l],points[r]);
	int mid = (l + r) >> 1;
	// 找到左右两边两点间距离最小值
	double d = lfmin(Solve(points,l,mid),Solve(points,mid+1,r));
	double ans = d;
	double left = mid, right = mid;
	vector<Point> left_part,right_part;
	while(l <= left){
		left_part.push_back(points[left]);
		left--;
	}
	while(right <= r){
		right_part.push_back(points[right]);
		right++;
	}
	sort(left_part.begin(), left_part.end(), compy);
	sort(right_part.begin(), right_part.end(), compy);

	int h = 0;
	for(int i = 0; i < left_part.size(); ++i){
		while(h < right_part.size() && right_part[h].y < left_part[i].y - d){
			h++;
		}
		h = min((int)right_part.size(),h);
		for(int j = h; j < min((int)right_part.size(), h+6); ++j){
			if(left_part[i] != right_part[j])
				ans = min(ans , dis(left_part[i],right_part[j]));
		}
	}
	return lfmin(ans,d);
}




double Solve2(vector<Point>& points, int l, int r)
{
	if(l >=r ) 
		return (double)INT_MAX;
	if(l + 1 == r) 
	{
		if(compy(points[r], points[l])) 
			swap(points[l], points[r]);
		return dis(points[l], points[r]);
	}
	int mid=(l+r)/2;
	Point midp = points[mid];

	double d=lfmin(Solve2(points, l, mid), Solve2(points, mid+1, r)), ans=d;

	inplace_merge(points.begin()+l, points.begin()+mid+1, points.begin()+r+1, compy);

	vector<Point> left_part, right_part;
	for(int i = l; i <= r; ++i)
	{
		if(midp.x>=points[i].x && disX(midp, points[i])<=d) 
			left_part.push_back(points[i]);

		if(midp.x<=points[i].x && disX(midp, points[i])<=d) 
			right_part.push_back(points[i]);
	}

	int h = 0;
	for(int i = 0; i < left_part.size(); ++i)
	{
		while(h<right_part.size() && right_part[h].y+d<left_part[i].y) 
			h++; 
		h = min((int)right_part.size(), h);

		for(int j = h; j < min((int)right_part.size(), h+6); ++j)
			if(left_part[i] != right_part[j]) 
				ans=lfmin(ans, dis(left_part[i], right_part[j])); 
	}
	return lfmin(ans, d);
}



int main(){

}