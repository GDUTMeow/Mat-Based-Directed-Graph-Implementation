#include "common.h"

#pragma once

#define MAX_LENGTH 100

typedef struct Arc {
    int target;    // 此边指向的终点的节点位置
    Arc *nextarc;    // 指向下一条边的指针
} Arc;  // 边

typedef struct Node {
    char data;  // 节点数据域
    Arc *firstarc; // 指向第一条边的指针
} Node; // 节点

typedef struct GraphMat {
    char nodes[MAX_LENGTH]; // 用于保存邻接矩阵的节点列表
    int arcs[MAX_LENGTH][MAX_LENGTH];   // 用于保存是否存在从 i 到 j 的边
    int size; // 存储节点数，邻接矩阵的大小
} GraphMat; // 邻接矩阵

typedef struct GraphTable {
    Node nodes[MAX_LENGTH]; // 用于保存邻接表的节点列表
    int node_count, arc_count; // 存储节点数和边数
} GraphTable;   // 邻接表

// 函数
// TODO 懒了，晚点再做