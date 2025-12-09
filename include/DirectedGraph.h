#include "common.h"

#pragma once

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
Status initGraph(GraphMat &G); // 初始化邻接矩阵
Status initGraphTable(GraphTable &GT); // 初始化邻接表
Status insertNode(GraphMat &G, char node); // 向邻接矩阵中插入节点
Status insertArc(GraphMat &G, char from, char to); // 向邻接矩阵中插入边
Status removeArc(GraphMat &G, char from, char to); // 从邻接矩阵中删除边
Status removeNode(GraphMat &G, char node); // 从邻接矩阵中删除
int getNodeInDegree(const GraphMat &G, char node); // 获取节点的入度
int getNodeOutDegree(const GraphMat &G, char node); // 获取节点的出度
int getNodeDegree(const GraphMat &G, char node); // 获取节点的度
void BFS(const GraphTable &GT, char start);    // 广度优先搜索
void DFS(const GraphTable &GT, char start);    // 深度优先搜索
Status migrateToTable(const GraphMat &G, GraphTable &GT); // 将邻接矩阵转换为邻接表
void printGraphMat(const GraphMat &G); // 打印邻接矩阵
void printGraphTable(const GraphTable &GT); // 打印邻接表
Boolean findPathFromTo(const GraphTable &GT, char from, char to);    // 查找从 from 到 to 的路径是否存在
char getFirstNeighbor(const GraphTable &GT, char node); // 获取节点的第一个邻居
char getNextNeighbor(const GraphTable &GT, char node, char cur);  // 获取节点的下一个邻居
void printGraphNodes(const GraphMat &G); // 打印图的所有节点
void printGraphArcs(const GraphMat &G); // 打印图的所有边