#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

const int p = 1000000007;

/*
3
2 1 2
1 1
2 2 2
1 1
2 2
2 2 2
1 1
1 2
*/

struct node
{
    int c, d;
    bool operator<(const node &x) const
    {
        if (c != x.c)
            return c < x.c;
        return d < x.d;
    }
    bool operator==(const node &x) const
    {
        return c == x.c && d == x.d;
    }
};

long long qpow(long long a, long long b)
{
    long long s = 1;
    while (b)
    {
        if (b % 2 == 1)
            s = s * a % p;
        a = a * a % p;
        b /= 2;
    }
    return s;
}

namespace IO
{
    char buf[1 << 21], *p1 = buf, *p2 = buf, obuf[1 << 21], *p3 = obuf;
    char gc()
    {
        if (p1 == p2)
        {
            p1 = buf;
            p2 = buf + fread(buf, 1, 1 << 21, stdin);
        }
        return p1 == p2 ? EOF : *p1++;
    }
    template <typename T>
    void read(T &x)
    {
        x = 0;
        char ch = gc();
        while (!isdigit(ch))
            ch = gc();
        while (isdigit(ch))
        {
            x = (x << 3) + (x << 1) + (ch ^ 48);
            ch = gc();
        }
    }
    void pc(char c)
    {
        if (p3 - obuf < (1 << 21))
            *p3++ = c;
        else
        {
            fwrite(obuf, p3 - obuf, 1, stdout);
            p3 = obuf;
            *p3++ = c;
        }
    }
    template <typename T>
    void write(T x)
    {
        if (x > 9)
            write(x / 10);
        pc(x % 10 + 48);
    }
}
using namespace IO;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("assign.in", "r", stdin);
    freopen("assign.out", "w", stdout);
#endif

    int T;
    read(T);
    while (T--)
    {
        int n, m, v;
        read(n), read(m), read(v);

        vector<node> con(m);
        for (int i = 0; i < m; i++)
        {
            read(con[i].c);
            read(con[i].d);
        }

        sort(con.begin(), con.end());

        bool valid = true;
        for (int i = 1; i < m; i++)
        {
            if (con[i].c == con[i - 1].c && con[i].d != con[i - 1].d)
            {
                valid = false;
                break;
            }
        }

        if (!valid)
        {
            write(0);
            pc('\n');
            continue;
        }

        con.erase(unique(con.begin(), con.end()), con.end());
        m = con.size();

        long long ans = qpow(v, 2 * (con[0].c - 1));
        for (int i = 1; i < m; i++)
        {
            int d = con[i].c - con[i - 1].c;
            long long cur = (qpow(v, 2 * d) + p - (1LL * (v - 1) * qpow(v, d - 1) % p)) % p;
            ans = ans * cur % p;
        }
        ans = ans * qpow(v, 2 * (n - con[m - 1].c)) % p;

        write(ans);
        pc('\n');
    }

    fwrite(IO::obuf, IO::p3 - IO::obuf, 1, stdout);
    return 0;
}
/*
Problem Explanation
The problem involves multiple test cases where each test case consists of:

An integer n representing the number of nodes.
An integer m representing the number of constraints.
An integer v representing the number of possible values each node can take.
A list of m constraints, where each constraint is a pair (c, d) indicating that node c must have value d.
The goal is to determine the number of valid assignments of values to the nodes such that all constraints are satisfied. The result should be computed modulo 1000000007.

Solution Approach
Input Reading and Initialization:

Read the number of test cases.
For each test case, read n, m, and v.
Read the list of constraints.
Sorting and Validity Check:

Sort the constraints based on the node index c.
Check for any conflicting constraints (i.e., two constraints for the same node with different values). If such a conflict exists, the number of valid assignments is 0.
Unique Constraints:

Remove duplicate constraints to ensure each node has at most one constraint.
Power Calculation:

Use modular exponentiation to calculate powers efficiently.
Calculate the Number of Valid Assignments:

Initialize the result with the number of ways to assign values to nodes before the first constrained node.
For each pair of consecutive constrained nodes, calculate the number of valid assignments for the nodes between them.
Multiply the results for each segment.
Finally, account for the nodes after the last constrained node.
Output the Result:

Print the result for each test case.
*/
/*
Explanation of Key Parts
Modular Exponentiation (qpow):

This function calculates (a^b \mod p) efficiently using the method of exponentiation by squaring.
Input/Output Optimization (IO namespace):

Custom functions for fast input and output to handle large volumes of data efficiently.
Main Logic:

Sorting and Validity Check: Sort constraints and check for conflicts.
Unique Constraints: Remove duplicate constraints.
Calculate Valid Assignments: Use modular arithmetic to calculate the number of valid assignments for each segment of nodes.
Output the Result: Print the result for each test case.
This approach ensures that the solution is both efficient and correct, handling the constraints and requirements of the problem effectively.
*/