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

> [!important]
>
> 所有的函数实现都在 `src/DirectedGraph.cpp` 文件中

### 核心操作函数

这些函数直接对底层的邻接矩阵 `GraphMat` 进行操作，是图数据管理的基础

- `Status initGraph(GraphMat &G)`
  - **功能**: 初始化一个邻接矩阵图，将其置为空图状态
  - **参数**:
    - `GraphMat &G`: 需要被初始化的图对象的引用
  - **返回**: 总是返回 `SUCCESS`

- `Status insertNode(GraphMat &G, char node)`
  - **功能**: 向图中添加一个新的节点
  - **参数**:
    - `GraphMat &G`: 目标图对象的引用
    - `char node`: 需要插入的节点字符
  - **返回**: 如果节点已存在，返回 `ERROR`；否则返回 `SUCCESS`

- `Status insertArc(GraphMat &G, char from, char to)`
  - **功能**: 在两个已存在的节点 `from` 和 `to` 之间添加一条有向边
  - **参数**:
    - `GraphMat &G`: 目标图对象的引用
    - `char from`: 边的起始节点
    - `char to`: 边的终点节点
  - **返回**: 如果任一节点不存在，返回 `ERROR`；否则返回 `SUCCESS` (如果有对应的边也返回 SUCCESS)

- `Status removeNode(GraphMat &G, char node)`
  - **功能**: 从图中删除一个节点以及所有与之相关的入边和出边
  - **参数**:
    - `GraphMat &G`: 目标图对象的引用
    - `char node`: 需要删除的节点字符
  - **返回**: 如果节点不存在，返回 `ERROR`；否则返回 `SUCCESS`

- `Status removeArc(GraphMat &G, char from, char to)`
  - **功能**: 删除从节点 `from` 到节点 `to` 的有向边
  - **参数**:
    - `GraphMat &G`: 目标图对象的引用
    - `char from`: 边的起始节点
    - `char to`: 边的终点节点
  - **返回**: 如果任一节点不存在，返回 `ERROR`；否则返回 `SUCCESS`

### 查询与打印函数

- `int getNodeInDegree(const GraphMat &G, char node)`
  - **功能**: 计算并返回指定节点的入度（指向该节点的边的数量）
  - **参数**:
    - `const GraphMat &G`: 目标图对象的常量引用
    - `char node`: 需要查询的节点字符
  - **返回**: 节点的入度值。如果节点不存在，返回 `-1`

- `int getNodeOutDegree(const GraphMat &G, char node)`
  - **功能**: 计算并返回指定节点的出度（从该节点出发的边的数量）
  - **参数**:
    - `const GraphMat &G`: 目标图对象的常量引用
    - `char node`: 需要查询的节点字符
  - **返回**: 节点的出度值。如果节点不存在，返回 `-1`

- `int getNodeDegree(const GraphMat &G, char node)`
  - **功能**: 计算并返回指定节点的总度数
  - **参数**:
    - `const GraphMat &G`: 目标图对象的常量引用
    - `char node`: 需要查询的节点字符
  - **返回**: 节点的总度数。如果节点不存在，返回 `-1`

- `void printGraphNodes(const GraphMat &G)`
  - **功能**: 打印图中当前存在的所有节点及其总数
  - **参数**:
    - `const GraphMat &G`: 需要打印的图对象的常量引用

- `void printGraphArcs(const GraphMat &G)`
  - **功能**: 打印图中当前存在的所有边及其总数
  - **参数**:
    - `const GraphMat &G`: 需要打印的图对象的常量引用

- `void printGraphMat(const GraphMat &G)`
  - **功能**: 以矩阵的形式打印图的邻接矩阵
  - **参数**:
    - `const GraphMat &G`: 需要打印的图对象的常量引用

### 算法与邻接表相关函数

这些函数大多依赖于邻接表 `GraphTable` 以获得更好的算法效率

- `Status migrateToTable(const GraphMat &G, GraphTable &GT)`
  - **功能**: 将邻接矩阵 `G` 的结构转换并存储到一个新的邻接表 `GT` 中。采用了从后往前的列遍历和头插法，以保证邻接表中的邻居顺序与节点编号顺序一致
  - **参数**:
    - `const GraphMat &G`: 作为数据源的邻接矩阵
    - `GraphTable &GT`: 用于接收结果的邻接表
  - **返回**: 如果内存分配失败，返回 `OVERFLOW`；否则返回 `SUCCESS`

- `void DFS(const GraphTable &GT, char start_node)`
  - **功能**: 从指定的 `start_node` 开始，对图进行深度优先遍历并打印遍历序列。该函数会处理非连通图的情况
  - **参数**:
    - `const GraphTable &GT`: 需要遍历的图（以邻接表形式）
    - `char start_node`: 遍历的起始节点

- `void BFS(const GraphTable &GT, char start_node)`
  - **功能**: 从指定的 `start_node` 开始，对图进行广度优先遍历并打印遍历序列
  - **参数**:
    - `const GraphTable &GT`: 需要遍历的图（以邻接表形式）
    - `char start_node`: 遍历的起始节点

- `Boolean findPathFromTo(const GraphTable &GT, char from, char to)`
  - **功能**: 使用基于栈的深度优先搜索策略，查找是否存在从节点 `from` 到节点 `to` 的路径
  - **参数**:
    - `const GraphTable &GT`: 需要查找的图（以邻接表形式）
    - `char from`: 路径的起始节点
    - `char to`: 路径的目标节点
  - **返回**: 如果路径存在，返回 `TRUE`；否则返回 `FALSE`

- `char getFirstNeighbor(const GraphTable &GT, char node)`
  - **功能**: 获取指定节点在邻接表中的第一个邻居节点
  - **参数**:
    - `const GraphTable &GT`: 目标图（以邻接表形式）
    - `char node`: 需要查询的节点
  - **返回**: 第一个邻居的字符。如果节点不存在或没有邻居，返回 `\0`

- `char getNextNeighbor(const GraphTable &GT, char node, char cur)`
  - **功能**: 已知节点 `node` 和它的一个当前邻居 `cur`，获取 `cur` 在邻接表链中的下一个邻居
  - **参数**:
    - `const GraphTable &GT`: 目标图（以邻接表形式）
    - `char node`: 起始节点
    - `char cur`: 当前邻居节点
  - **返回**: 下一个邻居的字符。如果没有下一个邻居，返回 `\0`

- `void printGraphTable(const GraphTable &GT)`
  - **功能**: 打印图的邻接表表示
  - **参数**:
    - `const GraphTable &GT`: 需要打印的邻接表
