/*
n堆物品,两人轮流取,每次取某堆中不少于1个,最后取完者胜.

结论: 将n堆物品数量全部异或后结果为0则必败,否则必胜.

*/
int res = 0;
for(int i = 1; i <= n; ++i)
	res = res ^arr[i];
if(res)
	return true;
else
	return false;