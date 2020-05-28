# Puzzle 1:You Will All comfrom

## question：

每个人都是知道他们的号码，从0开始，一群人排队，带着帽子，朝向前或后，你可以选定一个人反转帽子，或者让一个区间的人反转帽子。最终使得队列中所有人的帽子朝向一个方向。min操作次数

0 1 2 3 4 5 6 7 8 9 10

F B B F B F F B B B F

1 to 2 (inclusive) flip

4 flip

7 to 9 filp

forward [0,0] [3,3] [5 ,6] [10,10] : 4

backword [1,2] [4,4] [7,9] :3 <—-少的

## answer A：遍历序列，找出所有连续的序列分为先前和向后两列，反转区间多的。（两次遍历，第一次统计，第二次输出）

因为每一个连续的F或者B总是被一起反转的，因为最终的朝向相同，所以显然一次反转更优。

并且每次反转只会有F，B，假如某次反转中有F和B，（显然会出现在中央）不妨设为FFFBF，要将它反转为B，

那么第一次BBBFB，第二次BBBBB，假如有两个FBFBF,第一次BFBFB,BBBFB,BBBBB。需要三次反转，这与只反转F是相同的。

## answerB（只需要遍历一次）:

加一个 ‘end’作为结尾，

加a[0]作为结尾。

你会发现与第0个人方向不同的间隔个数，最多与和第一个人方向相同的人的间隔数相同。

两个人显然成立。

下面证明任意人都成立：

否则考虑序列T，开头是F，那么要让B的间隔数目多于F的间隔数目。那么只能加B，并且前一个是F（否则就会被归为前一个连续的操作），但是当T的开头和结尾都为F时，连续（或单个）的F分开了B，此时F的间隔个数 = B的间隔个数+1，加上新增的间隔数，此时F，B的间隔数相同。

所以只需要将于开头不同方向的连续的人反转。

当a[i] != a[i-1]时反转，并判断当前字符是否与开头相同，输出。

优化的算法只需要一次遍历，增加尾哨兵节点a[0]，就可以不用处理特殊情况。

# Puzzle 2:The Best Time To The Party

## question：

你有参加一张参加聚会的票，这张票的时间是灵活的，在你离开之前，你要和其他人交流，你可以选择你去交流的时间，你有一张时间表，表上记录了参加聚会的人的时间，选择固定的时间（1）最大化交流的人数。

Celeb | Comes | Gones

Beyonce 6 7 [ 6,7)

Talyor 7 9

Brad 10 11

Kaly 10 12

Tom 8 10

Drake 9 11

Allua 6 8

## A

朴素，区间改，查询最大值。O(n*n)

## B

sort进入时间，离开时间。

看到人就+1，出去-1

O(nlogn)

(感觉桶排O(n) ?)

进一步，最优总产生在有人进入的时间、，因为总是在进入时增加，而不可能选择出去的时间。

# Puzzle 3: You Can Read Minds

## question：

52张牌。

B会读心术，5个人每个人从52个扑克牌，各自选择一个，然后B助手的向B展示4张：（比如第一张是红心K，…..)然后B就可以猜出第五张是什么
问：
B如何做到的?助手是会配合B的。

## A

5张牌，鸽巢原理一定有一张牌花色相同。所以第一张牌代表隐藏的花色。

这时还剩下12种选择，剩余可以利用的还有三张牌，三张牌不同的顺序有3!=6种可能，不够。注意到，选出来代表花色的牌上也是有数字的。对于一个循环有13个数字围成一个环（J是10Q是11K是12A是1），我们恰当的选择隐藏的数字就可以做到，其中一个数字与另一个数字的距离不会超过6（假定都是顺时针），这样就可以用剩余三张牌来编码（数字和花色同时利用），就可以确定第5张牌。



#  Puzzle 4: Please Do Break the Crystal

你在128层的大厦上，你可以在某一层丢下求，求出最高层使求丢下去不会坏作为硬度系数。

1）只有一个球。

枚举

2）多个。

考虑最坏情况。

1 个 128

2个：

64丢 63次最坏

16 间隔 check 128 ：  8 + 15 = 23

k,2k,3k,...(n/k-1) * k ,(n/k )* k

一直没破  drops = n/k

search [(n/k-1) * k,n - 1], [n-k+1,n-1]

k-1 drops

minimize n/k + k - 1   =>2 sqrt(n) - 1   [sqrt(128)] = 11

d个：

d -digit numbers 

r - radix

choose r : r ^ d > n

n = 128 ,d = 4

choose r = 4

0000        1233          3333

(0)             (111)         (255)

first   1000 (64) does not break

​             2000 (128) breaks

​             [1001,1333]   ([65,127])

second :

​			1100 (96) not

​            1200 (112)

(其实就是倍增思想)

(r - 1 )d worst

all n < r ^d

# Puzzle 5:Keep Those Queens Apart

在8*8棋盘上放8和皇后，不会相互攻击

水平，垂直，对角线(斜着)。

斜着正方形，看增量

# Puzzle 6: A Profusion of Queens

普通n皇后问题

# Puzzle 7: Tile That Courtyard Please

## question

8*8 的院子，2^n * 2^n 

L-shaoped tile。   （trominoe）3个方格

铺满院子，

(先讲解了归并排序)

此时无法做到，因为院子块数不是3的倍数，现增加一个雕像，占一个位置（位置任意但固定）。

此时2^(2n)-1,  给出铺满的方法（给出一种即可,不是问种数（好像唯一？））



 ## answer

要创建更小的相同的问题。

将区域分为四个象限，那么其中一个象限一定有一个雕像，很明显，此时还不能进行递归调用，因为子问题不相同，将L型砖放在原点处，凹口朝向已有砖块的位置，此时四个象限中每个象限都有一个砖块，并且问题被分解为完全相同的四个子问题（只是改变了一下雕像的位置），四个砖块时是递归基（其中一个雕像）。



## py code

```python
#Programming for the Puzzled -- Srini Devadas
#Tile that Courtyard, Please
#Given n in a 2^n x 2^n checkyard with a missing square at position (r, c), 
#find tiling of yard with trominoes (L-shaped dominoes).
#This version works directly on the given grid, and does NOT make copies
#of the grid for recursive calls.

EMPTYPIECE = -1



#This procedure is the main engine of recursive algorithm
#nextPiece is the number of next available tromino piece
#The origin coordinates of the yard are given by originR and originC
def recursiveTile(yard, size, originR, originC, rMiss, cMiss, nextPiece):

    #quadrant of missing square: 0 (upper left), 1 (upper right),
    #                            2 (lower left), 3 (lower right)
    quadMiss = 2*(rMiss >= size//2) + (cMiss >= size//2)
    
    #base case of 2x2 yard
    if size == 2: 
        piecePos = [(0,0), (0,1), (1,0), (1,1)]
        piecePos.pop(quadMiss)
        for (r, c) in piecePos:
            yard[originR + r][originC + c] = nextPiece
        nextPiece = nextPiece + 1
        return nextPiece

    #recurse on each quadrant
    
    for quad in range(4):
        #Each quadrant has a different origin
        #Quadrant 0 has origin (0, 0), Quadrant 1 has origin (0, size//2)
        #Quadrant 2 has origin (size//2, 0), Quadrant 3 has origin (size//2, size//2)
        shiftR = size//2 * (quad >= 2)
        shiftC = size//2 * (quad % 2 == 1)
        if quad == quadMiss:
            #Pass the new origin and the shifted rMiss and cMiss
            nextPiece = recursiveTile(yard, size//2, originR + shiftR,\
                originC + shiftC, rMiss - shiftR, cMiss - shiftC, nextPiece)

        else:
            #The missing square is different for each of the other 3 quadrants
            newrMiss = (size//2 - 1) * (quad < 2)
            newcMiss = (size//2 - 1) * (quad % 2 == 0)
            nextPiece = recursiveTile(yard, size//2, originR + shiftR,\
                            originC + shiftC, newrMiss, newcMiss, nextPiece)


    #place center tromino
    centerPos = [(r + size//2 - 1, c + size//2 - 1)
                 for (r,c) in [(0,0), (0,1), (1,0), (1,1)]]
    centerPos.pop(quadMiss)
    for (r,c) in centerPos: # assign tile to 3 center squares
        yard[originR + r][originC + c] = nextPiece
    nextPiece = nextPiece + 1

    return nextPiece

#This procedure is a wrapper for recursiveTile that does all the work
def tileMissingYard(n, rMiss, cMiss):
    #Initialize yard, this is the only memory that will be modified!
    yard = [[EMPTYPIECE for i in range(2**n)]
            for j in range(2**n)] 
    recursiveTile(yard, 2**n, 0, 0, rMiss, cMiss, 0)
    return yard

#This procedure prints a given tiled yard using letters for tiles
def printYard(yard):
    for i in range(len(yard)):
        row = ''
        for j in range(len(yard[0])):
            if yard[i][j] != EMPTYPIECE:
                row += chr((yard[i][j] % 26) + ord('A'))
            else:
                row += ' '
        print (row)


printYard(tileMissingYard(3, 4, 6))
printYard(tileMissingYard(4, 5, 7))

```



# Puzzle 8: You Won't Want to Play Sudoku Again

9*9 Sudoku :  1 - 9

1)每行都有所有的数字

2)每列也有所有的数字

3)每个sector出现所有数字





搜索

记忆化

# Puzzle 9: The Disorganized Handyman

## question

100个螺母、100个螺栓，每个螺栓都是不同的，螺母相对应，只能做check。

（一一对应）



## answer A

枚举

O(n^2)

## answer B

快速排序算法思想，pivoting

check后可以把螺母，螺栓都分成两组（第一次2n次check）

O（nlogn）（常规意义下）

双指针滤分开

# Puzzle 10: A Weekend To Remember

## question

nodes are friendes

Edge between nodes imples a "dislike"

2天



1)朋友要参加其中一个聚会

2）相互不喜欢的不能在一个聚会上



二分图

可以用两种颜色着色

有奇数环时不可二分

dfs

# Puzzle 11: Memory Serves You Well

你有一排的连续的面值不同硬币

最大化选择硬币的面值之和，如果选择其中一个，那么不能选择下一个



动态规划

f(n) = max (f(n-2)+value(n) , f(n-1))

