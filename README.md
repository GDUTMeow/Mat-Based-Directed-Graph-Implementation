# DirectedGraphImplementation

个人系数据结构实验课实验报告代码，做的是有向图

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

- Node 表示有向图中的节点，其中包含以下属性
  - char data 节点中的数据，这里固定类型为 char，实际上可以改
  - Arc *firstarc 此节点中的第一条弧，或者说是邻接表中的从此点出发的第一条边

```cpp
typedef struct Arc {
    int target;    // 此边指向的终点的节点位置
    Arc *nextarc;    // 指向下一条边的指针
} Arc;  // 边
```

- Arc 表示有向图中的边，包含以下属性
  - int target 表示这条边指向的节点在节点列表中的位置
  - Arc *nextarc 表示在邻接表中下一条弧的指针

```cpp
typedef struct GraphMat {
    char nodes[MAX_LENGTH]; // 用于保存邻接矩阵的节点列表
    int arcs[MAX_LENGTH][MAX_LENGTH];   // 用于保存是否存在从 i 到 j 的边
    int size; // 存储节点数，邻接矩阵的大小
} GraphMat; // 邻接矩阵
```

- GraphMat 表示有向图的邻接矩阵，包含以下属性
  - char nodes[MAX_LENGTH] 保存所有的邻接矩阵节点
  - int arcs[MAX_LENGTH][MAX_LENGTH] 保存所有的邻接状态
  - int size 表示邻接矩阵的大小，同时也保存了该图中有多少节点

```cpp
typedef struct GraphTable {
    Node nodes[MAX_LENGTH]; // 用于保存邻接表的节点列表
    int node_count, arc_count; // 存储节点数和边数
} GraphTable;   // 邻接表
```

- GraphTable 表示有向图的邻接表，包含以下属性
  - Node nodes[MAX_LENGTH] 保存了邻接表的所有节点
  - int node_count 用于保存节点的数量（用来偷懒）
  - int arc_count 用于保存弧的数量（同样用来偷懒诶嘿）

