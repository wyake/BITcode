#include <cstdio>
#include <cstring>
using namespace std;

const long long MAX_N = 5000100;

long long lowbit(long long x) {
    return x & -x;
}

class BIT {
public:
    // node数组就是一个保存区间和的数组
    long long node[MAX_N], n;

    // 构造函数，初始化数组，以及数组的长度
    BIT(int _n) {
        memset(node, 0, sizeof(node));
        n = _n;
    }

    // 计算从1到index的区间的和
    long long sum(int index) {
        long long sum = 0;
        while (index > 0) {
            sum += node[index];
            index -= lowbit(index);
        }
        return sum;
    }

    // 对于包含 下标为index的数字的区间 都应该进行和的调整
    void add(int index, long long value) {
        while (index <= n) {
            node[index] += value;
            index += lowbit(index);
        }
    }
};

int BITMain()
{
    // https://www.luogu.com.cn/problem/P3374
    int n, m, op, x, y;
    long long value;
    scanf("%d%d", &n, &m);
    BIT tree = BIT(n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &value);
        tree.add(i, value);
    }

    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &op, &x, &y);
        if (op == 1) {
            // op==1 就是单个数字进行增加，对应的包含这个数字的区间的和也要改变
            tree.add(x, y);
        } else if (op == 2) {
            // op==2 就是求取区间的和
            printf("%lld\n", (tree.sum(y) - tree.sum(x - 1)));
        }
    }
    return 0;
}

int main()
{
    BITMain();
}