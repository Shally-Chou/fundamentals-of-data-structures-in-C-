#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <queue>
#include <set>

using namespace std;

// 產生graph
void generateRandomGraph(int n, int e, vector<vector<int>>& adjMatrix, vector<vector<int>>& adjList) {    //二維 用引用的 才不用再複製一份 修改結果才會反映給呼叫者
    srand(time(0));    //time(0)回傳的是現在的秒數 這樣每次執行時產生的亂數序列都不一樣
    set<pair<int, int>> edgeSet;    //set表集合 pair就是晚點a,d為edge一組成線 且用set可快速確認這個組合有無出現過

    while ((int)edgeSet.size() < e) {    //int顯式轉型 有時候回傳的是size_t（無號整數） 在生成的邊<e之前都要跑
        int u = rand() % n;    //設vertex 範圍:0 ~ n-1
        int v = rand() % n;
        if (u != v) {    //確保不是自己走到自己
            int a = min(u, v), b = max(u, v);    //a會是兩者中小的那個 b反之 因為上面用set所以不用擔心重複出現的問題
            if (edgeSet.count({a, b}) == 0) {    //如果這條路還沒被記錄到(==0就是沒紀錄過)
                edgeSet.insert({a, b});    //加進去
                adjMatrix[a][b] = adjMatrix[b][a] = 1;    //設矩陣 a,b=b,a 無向圖 長度一律設為1
                adjList[a].push_back(b);    //a有個鄰居是b
                adjList[b].push_back(a);    //b有個鄰居是a
            }
        }
    }
}

// 匯出CSV file
void exportEdgeList(const vector<vector<int>>& graph, const string& filename) {    //const保證這個函式裡不會改到引用的內容 保護措施
    ofstream file(filename);
    file << "Vertex 1,Vertex 2\n";    //寫入file的第一行
    int n = graph.size();    //共有幾個節點
    for (int u = 0; u < n; ++u) {    //歷遍串列
        for (int v : graph[u]) {    //graph[u]這個vector裡的每個元素v都執行一次
            if (u < v) file << u << "," << v << "\n";    //避免邊出現重複
        }
    }
    file.close();    //開完要記得關 反正是個好習慣
}

// DFS 遍歷
void dfs(int u, vector<bool>& visited, const vector<vector<int>>& graph, vector<vector<int>>& tree) {    
    visited[u] = true;    //標記為走過 grey
    for (int v : graph[u]) {    //
        if (!visited[v]) {    //如果連到的點有沒走過的 white
            tree[u].push_back(v);    //u走到v
            tree[v].push_back(u);    //v也可以走到u 無向圖嘛
            dfs(v, visited, graph, tree);    //重跑dfs u變成v=從v開始往後走
        }
    }
}

// BFS 遍歷
void bfs(int start, vector<bool>& visited, const vector<vector<int>>& graph, vector<vector<int>>& tree) {    
    queue<int> q;    //建一個列 放等等要尋訪的東西 像是看1把2,3放進去 看2序列變成3,4,5
    q.push(start);    //把起始點放到列裡面 top是1就把1放進去
    visited[start] = true;    //標記為走過 grey

    while (!q.empty()) {    //當列不為空時就一直跑
        int u = q.front(); q.pop();    //最前面的值給u 然後把他從列中刪掉
        for (int v : graph[u]) {    //graph[u]這個vector裡的每個元素v都執行一次=看鄰居
            if (!visited[v]) {    //如果連到的點有沒走過的 white
                visited[v] = true;    //過去 標為走過 grey
                tree[u].push_back(v);    
                tree[v].push_back(u);    
                q.push(v);    //把v放到列中
            }
        }
    }
}

// 印出鄰接矩陣
void printAdjMatrix(const vector<vector<int>>& matrix) {    //const保證這個函式裡不會改到引用的內容 保護措施
    int n = matrix.size();    //這是取得矩陣的大小=節點數n 如果有5個點那矩陣大小就是5x5 matrix.size()就是5
    cout << "    ";
    for (int i = 0; i < n; ++i) cout << i << "  ";    //有幾個數字就印到多少 阿從0開始
    cout << endl;
    for (int i = 0; i < n; ++i) {
        cout << " " << i << " ";
        for (int j = 0; j < n; ++j) {
            cout << " " << matrix[i][j] << " ";    //有連到就1 沒線就0
        }
        cout << endl;
    }
}

// 印出鄰接串列
void printAdjList(const vector<vector<int>>& adjList) {    
    for (int i = 0; i < adjList.size(); ++i) {    //遍歷所有節點 0到n-1(adjList.size-1)
        cout << i << " : ";
        for (int j : adjList[i]) cout << j << " ";    //順序看adjList[u].push_back(v) 先push的會先被印出來
        cout << endl;    
    }
}

int main() {
    int n, e;
    cout << "請輸入節點數 n：";
    cin >> n;
    int maxEdge = n * (n - 1) / 2;
    cout << "請輸入邊數 e（最大為 C(n,2) = " << maxEdge << "）：";
    cin >> e;

    if (e > maxEdge) {
        cout << "邊數超過最大可能值，請重新輸入。" << endl;
        return 0;    //
    }

    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));    //每個元素是int的二維 前一個代表橫的總共建n個 後面則是裡面總共放n個0(現在都沒邊初始設0)
    vector<vector<int>> adjList(n);    //二維 總共有n個節點所以橫的要建n個
    generateRandomGraph(n, e, adjMatrix, adjList);    

    cout << "\n鄰接矩陣 :" << endl;
    printAdjMatrix(adjMatrix);    

    cout << "\n鄰接串列 :" << endl;
    printAdjList(adjList);    

    // 匯出graph
    exportEdgeList(adjList, "graph_edges.csv");    

    // DFS Tree
    vector<vector<int>> dfs_tree(n);    
    vector<bool> visited(n, false);    //用來記錄是否走過 共有n個vertex 因為用bool所以用false(都還沒走過初始為0)
    for (int i = 0; i < n; ++i)    //每個點都要過一遍 可能有不連通的
        if (!visited[i]) dfs(i, visited, adjList, dfs_tree);    //if white 做dfs
    exportEdgeList(dfs_tree, "dfs_tree_edges.csv");    //全部都走過就輸出

    // BFS Tree
    vector<vector<int>> bfs_tree(n);
    fill(visited.begin(), visited.end(), false);    //因為剛剛上面用過 所以把起點到終點所有點都恢復原廠設定
    for (int i = 0; i < n; ++i)    //確保大家都會走到 超貼心欸幹
        if (!visited[i]) bfs(i, visited, adjList, bfs_tree);    //if white 做bfs
    exportEdgeList(bfs_tree, "bfs_tree_edges.csv");    //全部都走過就輸出

    // 印出 DFS/BFS Tree 的鄰接串列
    cout << "\nDFS Tree 的鄰接串列:" << endl;
    printAdjList(dfs_tree);

    cout << "\nBFS Tree 的鄰接串列:" << endl;
    printAdjList(bfs_tree);

    cout << "\n圖與 DFS/BFS Tree 已輸出成 CSV！" << endl;

    return 0;
}
