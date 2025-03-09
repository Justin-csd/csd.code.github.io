#include <cstdio>
#include <algorithm>

#define N 100005
#define rep(i, a, b) for (int i = a; i <= b; i++)

using namespace std;

// Global variables
int n, m, k; // n: number of elements, m: number of swaps, k: number of operations
int p[N];    // Array to hold the current permutation of elements
int v[N];    // Array to track visited elements
int a[N];    // Result array to store the final arrangement
int sta[N];  // Stack to hold the current cycle of elements during DFS
int tp;      // Top pointer for the stack

// Depth First Search (DFS) to identify the cycle of elements
void dfs(int x)
{
    sta[tp++] = x; // Push current index onto the stack
    v[x] = 1;      // Mark this index as visited
    if (!v[p[x]])  // Check if the next index in the permutation has been visited
        dfs(p[x]); // Recursively call DFS on the next index
}

// Function to perform the transformation based on the swaps
void work()
{
    rep(i, 1, n)
    { // Iterate over all elements
        if (!v[i])
        {                      // For unvisited elements
            tp = 0;            // Reset top pointer for the stack
            dfs(i);            // Find the cycle using DFS
            int step = k % tp; // Calculate effective steps to rotate
            rep(j, 0, tp - 1)
            {
                // Rotate the elements in the cycle
                a[sta[j]] = sta[(j + step) % tp];
            }
            // The following commented-out code can be used for debugging:
            // cout << sta[j] << " ";
            // cout << endl;
        }
    }
}

int main()
{
    // Uncomment these lines to read input from files if needed
    // freopen("swap.in", "r", stdin);
    // freopen("swap.out", "w", stdout);

    // Read the number of elements, number of swaps, and number of operations
    scanf("%d %d %d", &n, &m, &k);

    // Initialize the permutation array
    rep(i, 1, n) p[i] = i;

    // Read and execute the swap operations
    rep(i, 1, m)
    {
        int l, r;
        scanf("%d %d", &l, &r);
        rep(j, l, (l + r) >> 1) // Swap elements from l to r
            swap(p[j], p[r - j + l]);
    }

    // Perform the transformation on the permutation
    work();

    // Output the final arrangement after all operations
    rep(i, 1, n) printf("%d\n", a[i]);

    return 0;
}