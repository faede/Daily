/*只有一堆n个物品,两个人轮流从这堆物品中取物,规定每次至少取一个,最多取m个.最后取光的人赢
n = k * (m+1) + r
先手取走r个,后手无论拿走(1~m)个,先手的人只要拿的数目和为 m + 1 那么先手就必赢.
反之若n = k * (m + 1),那么先手的无论怎么样都会输
*/ 
if(n % (m+1))
	return false;
else
	return true;