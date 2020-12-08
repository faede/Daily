//链接：https://www.zhihu.com/question/36132386/answer/712269942

/*
如果是while(l <= r) 那么终止条件是 l = r + 1
此时搜索的应该是开区间[left,right]
这样当循环跳出时 l== r+1 [r,r+1] 才是无解的,
但是这样不容易找bound

left_bound:

如果while(l < r) 那么终止条件是 l == r
此时搜索的应该是开区间[left,right)
这样当循环跳出时 l== r [l,l) 才是无解的
此时 left = mid + 1, right = mid
是因为,mid被检测之后,接下来应该去掉mid,
分成两个左闭右开的区间 [left, mid) [mid+1,right)

为什么该算法能够搜索左侧边界？
if (nums[mid] == target)
    right = mid;
可见，找到 target 时不要立即返回，而是缩小「搜索区间」的上界 right，
在区间 [left, mid) 中继续搜索，即不断向左收缩，达到锁定左侧边界的目的。

为什么没有返回 -1 的操作？如果 nums 中不存在 target 这个值，怎么办？
// 类似之前算法的处理方式
return nums[left] == target ? left : -1;

right_bound:
if (nums[mid] == target) {
    left = mid + 1;
当 nums[mid] == target 时，不要立即返回，而是增大「搜索区间」的下界 left，
使得区间不断向右收缩，达到锁定右侧边界的目的。

为什么要减一:
if (nums[mid] == target) {
    left = mid + 1;
    // 这样想: mid = left - 1

因为我们对 left 的更新必须是 left = mid + 1，就是说 while 循环结束时，
nums[left] 一定不等于 target 了，而 nums[left-1] 可能是 target。
*/


int left_bound(int[] nums, int target) {
    if (nums.length == 0) return -1;
    int left = 0;
    int right = nums.length; // 注意

    while (left < right) { // 注意
        int mid = (left + right) / 2;
        if (nums[mid] == target) {
            right = mid;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else if (nums[mid] > target) {
            right = mid; // 注意
        }
    }
    return left;
}

int right_bound(int[] nums, int target) {
    if (nums.length == 0) return -1;
    int left = 0, right = nums.length;

    while (left < right) {
        int mid = (left + right) / 2;
        if (nums[mid] == target) {
            left = mid + 1; // 注意
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else if (nums[mid] > target) {
            right = mid;
        }
    }
    return left - 1; // 注意
}




//链接：https://www.zhihu.com/question/36132386/answer/82632513

/*

acm:
check的时候,用下面的情况就好

整数二分，都是闭区间，ans返回找到的第一个满足条件的解（如找到一个有序数组中第一个大于或者等于某一个数值的数在数组中的位置），
找不到解时返回-1


*/

// 上面提到的找小的:
int search(int low, int high) {
  int ans = -1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (judge(mid)) {
      ans = mid;
      high = mid - 1;
    } else low = mid + 1;
  }
  return ans;
}

// 找大的:
int search(int low, int high) {
  int ans = -1;
  while (low <= high) {
    int mid = low + (high - low) / 2;
    if (judge(mid)) {
      ans = mid;
      low = mid + 1;
    } else high = mid - 1;
  }
  return ans;
}

// 浮点数不用说:
#define eps 1e-8

double search(double low, double high) {
  while (high - low > eps) {
    double mid = (low + high) / 2;
    if (judge(mid)) high = mid;
    else low = mid;
  }
  return (low + high) / 2;
} 
 