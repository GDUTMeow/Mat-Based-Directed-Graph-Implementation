# Mat-Based-Directed-Graph-Implementation

个人系数据结构实验课实验报告代码，做的是有向图，基于邻接矩阵的有向图操作（除非必要否则不用邻接表，问就是个人感觉没矩阵方便）

## 数据结构定义

> [!important]
> 
> 对应结构的定义都在 `include/DirectedGraph.h` 里面

```cpp
typedef struct Node {
    char data;  // 节点数据域
    Arc *firstarc; // 指向第一条边的指针
} Node; // 节点
```

- `Node` 表示有向图中的节点，其中包含以下属性
  - `char data` 节点中的数据，这里固定类型为 char，实际上可以改
  - `Arc *firstarc` 此节点中的第一条弧，或者说是邻接表中的从此点出发的第一条边

```cpp
typedef struct Arc {
    int target;    // 此边指向的终点的节点位置
    Arc *nextarc;    // 指向下一条边的指针
} Arc;  // 边
```

- `Arc` 表示有向图中的边，包含以下属性
  - `int target` 表示这条边指向的节点在节点列表中的位置
  - `Arc *nextarc` 表示在邻接表中下一条弧的指针

```cpp
typedef struct GraphMat {
    char nodes[MAX_LENGTH]; // 用于保存邻接矩阵的节点列表
    int arcs[MAX_LENGTH][MAX_LENGTH];   // 用于保存是否存在从 i 到 j 的边
    int size; // 存储节点数，邻接矩阵的大小
} GraphMat; // 邻接矩阵
```

- `GraphMat` 表示有向图的邻接矩阵，包含以下属性
  - `char nodes[MAX_LENGTH]` 保存所有的邻接矩阵节点
  - `int arcs[MAX_LENGTH][MAX_LENGTH]` 保存所有的邻接状态
  - `int size` 表示邻接矩阵的大小，同时也保存了该图中有多少节点

```cpp
typedef struct GraphTable {
    Node nodes[MAX_LENGTH]; // 用于保存邻接表的节点列表
    int node_count, arc_count; // 存储节点数和边数
} GraphTable;   // 邻接表
```

- `GraphTable` 表示有向图的邻接表，包含以下属性
  - `Node nodes[MAX_LENGTH]` 保存了邻接表的所有节点
  - `int node_count` 用于保存节点的数量（用来偷懒）
  - `int arc_count` 用于保存弧的数量（同样用来偷懒诶嘿）

## 函数定义

- `Status initGraph(GraphMat &G)` 用于初始化邻接矩阵，进行对应的置零操作
  - `GraphMat &G` 需要初始化的邻接矩阵
- `Status insertNode(GraphMat &G, char node)` 用于向邻接矩阵中插入传入的字符串节点
  - `GraphMat &G` 需要插入节点的邻接矩阵
  - `char node` 需要插入到矩阵中的新节点
- `Status insertArc(GraphMat &G, char from, char to)` 用于向邻接矩阵中插入从 from 到 to 的有向边
  - `GraphMat &G` 需要插入有向边的邻接矩阵
  - `char from` 起始节点
  - `char to` 终点节点
- `Status removeArc(GraphMat &G, char from, char to)` 用于删除邻接矩阵中从 from 到 to 的有向边
  - `GraphMat &G` 需要删除有向边的邻接矩阵
  - `char from` 起始节点
  - `char to` 终点节点
- `Status removeNode(GraphMat &G, char node)` 将传入的节点从邻接矩阵中删除
  - `GraphMat &G` 需要删除节点的邻接矩阵
  - `char node` 需要删除的节点
- `int getNodeInDegree(const GraphMat &G, char node)` 获取节点的入度
  - `const GraphMat &G` 需要获取入度的矩阵
  - `char node` 需要获取入度的节点
- `int getNodeOutDegree(const GraphMat &G, char node)` 获取节点的出度
  - `const GraphMat &G` 需要获取出度的矩阵
  - `char node` 需要获取出度的节点
- `int getNodeDegree(const GraphMat &G, char node)` 获取节点的度（其实就是上面两个一起跑）
  - `const GraphMat &G` 需要获取度的矩阵
  - `char node` 需要获取度的节点
- `void BFS(const GraphTable &GT, char start)` 从给定的 start 节点进行广度优先搜索
  - `const GraphTable &GT` 需要进行搜索遍历的矩阵
  - `char start` 起始节点
- `void DFS(const GraphTable &GT, char start)` 从给定的 start 节点进行深度优先搜索
  - `const GraphTable &GT` 需要进行搜索遍历的矩阵
  - `char start` 起始节点
- `Status migrateToTable(const GraphMat &G, GraphTable &GT)` 从给定的邻接矩阵迁移到邻接表
  - `const GraphMat &G` 需要进行迁移的邻接矩阵
  - `GraphTable &GT` 迁移后的结果邻接表
- `void printGraphMat(const GraphMat &G)` 打印邻接矩阵
  - `const GraphMat &G` 需要打印的邻接矩阵
- `void printGraphTable(const GraphTable &GT)` 打印邻接表
  - `const GraphTable &GT` 需要打印的邻接表
- `Boolean findPathFromTo(const GraphTable &GT, char from, char to)` 寻找是否存在从 from 到 to 的路径，存在返回 TRUE，否则返回 FALSE
  - `const GraphTable &GT` 需要寻找路径的邻接表
  - `char from` 起始节点
  - `char to` 目标节点
- `char getFirstNeighbor(const GraphTable &GT, char node)` 获取提供节点的第一个邻居节点
  - `const GraphTable &GT` 需要寻找节点的邻接表
  - `char node` 需要寻找邻居的节点
- `char getNextNeighbor(const GraphTable &GT, char node, char cur)` 获取当前所在的邻居节点的下一个在邻接表上的节点
  - `const GraphTable &GT` 需要寻找节点的邻接表
  - `char node` 起始节点
  - `char cur` 当前所在节点
