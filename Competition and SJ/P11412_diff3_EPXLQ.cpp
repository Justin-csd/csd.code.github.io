#include <iostream>      // for cin, cout
#include <vector>        // for TrieNode::records
#include <string>        // for Trie::insert
#include <unordered_map> // for TrieNode::children
using namespace std;

// 字典树节点结构
struct TrieNode
{
    unordered_map<char, TrieNode *> children;
    vector<pair<int, int>> records; // 存储(depth, value)对

    TrieNode() {}

    ~TrieNode()
    {
        for (auto &p : children)
        {
            delete p.second;
        }
    }
};

// 字典树类
class Trie
{
private:
    TrieNode *root;

public:
    Trie()
    {
        root = new TrieNode();
    }

    ~Trie()
    {
        delete root;
    }

    // 插入字符串及其对应的深度和价值
    void insert(const string &s, int depth, int value)
    {
        TrieNode *node = root;
        for (char c : s)
        {
            if (!node->children.count(c))
            {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
            node->records.emplace_back(depth, value);
        }
    }

    // 查询给定前缀和深度限制下的价值总和
    long long query(const string &prefix, int max_depth)
    {
        TrieNode *node = root;
        for (char c : prefix)
        {
            if (!node->children.count(c))
            {
                return 0;
            }
            node = node->children[c];
        }

        long long sum = 0;
        for (const auto &record : node->records)
        {
            if (record.first <= max_depth)
            {
                sum += record.second;
            }
        }
        return sum;
    }
};

// 快速输入
inline void read(int &x)
{
    x = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    }
}

int main(int argc, char **argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    Trie trie;

    // 读入n条记忆
    for (int i = 0; i < n; i++)
    {
        int r, v;
        string s;
        cin >> r >> v >> s;
        trie.insert(s, r, v);
    }

    // 处理m次查询
    for (int i = 0; i < m; i++)
    {
        int d;
        string q;
        cin >> d >> q;
        cout << trie.query(q, d) << "\n";
    }

    return 0;
}