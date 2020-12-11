/*
有两堆各若干个物品,两个人轮流从任意一堆中取出至少一个,或者同时从两堆中取出相同多的物品,
规定每次至少取一个,至多不限,最后取光者胜利.
	黄金分割比; 首先求出差值, 差值*黄金分割比 == 最小值的话后手赢,否则先手赢

*/
// 理解:https://www.cnblogs.com/techflow/p/13168267.html
// 证明:https://www.cnblogs.com/zwfymqz/p/8469863.html


// 可能丢精度,或许需要高精度
double r = (sqrt(5.0) + 1)/2;
int d = abs(a-b)*r;
if(d != min(a,b))
	return true;
else
	return false;