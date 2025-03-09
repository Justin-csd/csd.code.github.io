#include <iostream> // 引入输入输出流
#include <fstream>  // 引入文件流
#include <cstring>  // 引入字符串处理库

using namespace std; // 使用标准命名空间

ifstream fin("flower.in");   // 从文件"flower.in"读取输入
ofstream fout("flower.out"); // 输出结果到文件"flower.out"

int n;           // 花的数量
int *h;          // 花的高度数组
int result = 1;  // 结果计数，初始值为1
char aFlag = -1; // aFlag标志，初始为-1

int main()
{                                        // 主函数
    cin >> n;                            // 从文件中读取花的数量n
    h = new int[n + 1];                  // 动态分配数组h，用于存储花的高度
    memset(h, 0, sizeof(int) * (n + 1)); // 将数组h所有元素初始化为0
    for (int i = 1; i <= n; i++)
    {                // 从1到n读取每朵花的高度
        cin >> h[i]; // 读取花的高度
    }
    for (int i = 1; i < n; i++)
    { // 遍历花的高度
        if (h[i] > h[i + 1] && (aFlag == 0 || aFlag == -1))
        {              // 检查下降趋势
            result++;  // 结果加1
            aFlag = 1; // 更新标志为下降
        }
        if (h[i] < h[i + 1] && (aFlag == 1 || aFlag == -1))
        {              // 检查上升趋势
            result++;  // 结果加1
            aFlag = 0; // 更新标志为上升
        }
    }
    cout << result; // 将结果写入输出文件
    return 0;       // 返回0，表示程序正常结束
}