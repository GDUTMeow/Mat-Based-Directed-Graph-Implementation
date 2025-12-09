#include <stdlib.h>
#include <iostream>
#include "../include/DirectedGraph.h"
#include "../include/common.h"

// 私有函数
int findNodeIndex(const GraphMat &G, char node)
{
    for (int i = 0; i < G.size; i++)
    {
        if (G.nodes[i] == node)
        {
            return i; // 找到节点，返回索引
        }
    }
    return -1; // 未找到节点，返回 -1
}

int findNodeIndexFromTable(const GraphTable &GT, char node)
{
    for (int i = 0; i < GT.node_count; i++)
    {
        if (GT.nodes[i].data == node)
        {
            return i; // 找到节点，返回索引
        }
    }
    return -1; // 未找到节点，返回 -1
}

// 公共函数
Status initGraph(GraphMat &G)
{
    G.size = 0; // 初始化节点数为 0
    for (int i = 0; i < MAX_LENGTH; i++)
    {
        G.nodes[i] = '\0'; // 初始化节点列表
        for (int j = 0; j < MAX_LENGTH; j++)
        {
            G.arcs[i][j] = 0; // 初始化邻接矩阵关系
        }
    }
    return SUCCESS;
}

Status initGraphTable(GraphTable &GT)
{
    GT.node_count = 0; // 初始化节点数为 0
    GT.arc_count = 0;  // 初始化边数为 0
    for (int i = 0; i < MAX_LENGTH; i++)
    {
        GT.nodes[i].data = '\0';        // 初始化节点数据域
        GT.nodes[i].firstarc = NULLPTR; // 初始化边指针
    }
    return SUCCESS;
}

Status insertNode(GraphMat &G, char node)
{
    G.nodes[G.size++] = node; // 将节点添加到节点列表中
    return SUCCESS;
}

Status insertArc(GraphMat &G, char from, char to)
{
    int from_idx = findNodeIndex(G, from), to_idx = findNodeIndex(G, to);
    if (from_idx == -1 || to_idx == -1)
    {
        return ERROR; // 有节点不存在
    }
    G.arcs[from_idx][to_idx] = 1; // 在邻接矩阵中添加边
    return SUCCESS;
}

Status removeArc(GraphMat &G, char from, char to)
{
    int from_idx = findNodeIndex(G, from), to_idx = findNodeIndex(G, to);
    G.arcs[from_idx][to_idx] = 0; // 在邻接矩阵中删除边
    return SUCCESS;
}

Status removeNode(GraphMat &G, char node)
{
    int idx = 0;
    idx = findNodeIndex(G, node);
    if (idx == -1) // 未找到节点
    {
        return ERROR; // 节点不存在
    }
    for (int i = 0; i < G.size; i++)
    {
        G.arcs[i][idx] = 0; // 删除所有指向该节点的边，令对应的邻接矩阵中的值为 0
        G.arcs[idx][i] = 0; // 删除该节点指向的所有边，令对应的邻接矩阵中的值为 0
    }
    for (; idx < G.size - 1; idx++)
    {
        G.nodes[idx] = G.nodes[idx + 1]; // 将后面的节点搬到现在 idx 指向的位置
        for (int j = 0; j < G.size; j++)
        {
            G.arcs[idx][j] = G.arcs[idx + 1][j]; // 同理搬动邻接矩阵的行
            G.arcs[j][idx] = G.arcs[j][idx + 1]; // 同理搬动邻接矩阵的列
        }
    }
    G.size--; // 减少节点数
    return SUCCESS;
}

int getNodeInDegree(const GraphMat &G, char node)
{
    int idx = findNodeIndex(G, node);
    if (idx == -1)
    {
        return -1; // 节点不存在，返回 -1
    }
    int degree = 0;
    for (int i = 0; i < G.size; i++)
    {
        if (G.arcs[i][idx] == 1)
        {
            degree++; // 统计入度
        }
    }
    return degree;
}

int getNodeOutDegree(const GraphMat &G, char node)
{
    int idx = findNodeIndex(G, node);
    if (idx == -1)
    {
        return -1; // 节点不存在，返回 -1
    }
    int degree = 0;
    for (int j = 0; j < G.size; j++)
    {
        if (G.arcs[idx][j] == 1)
        {
            degree++; // 统计出度
        }
    }
    return degree;
}

int getNodeDegree(const GraphMat &G, char node)
{
    int inDegree = getNodeInDegree(G, node);
    int outDegree = getNodeOutDegree(G, node);
    if (inDegree == -1 || outDegree == -1)
    {
        return -1; // 节点不存在，返回 -1
    }
    return inDegree + outDegree; // 返回度数
}

void BFS(const GraphTable &GT, char start_node)
{
    int start_idx = findNodeIndexFromTable(GT, start_node);
    if (start_idx == -1)
    {
        std::cout << "[-] Error: Cannot find provided start node: " << start_node << std::endl;
        return;
    }

    int queue[MAX_LENGTH]; // 初始化循环队列
    int head = 0, tail = 0;

    bool visited[MAX_LENGTH]; // 存储访问状态标记
    for (int i = 0; i < GT.node_count; i++)
    {
        visited[i] = false; // 初始化
    }

    // 3. 起始节点入队并标记
    std::cout << "[*] BFS Traversal: ";
    queue[tail++] = start_idx;
    visited[start_idx] = true;

    // 队列非空
    while (head < tail)
    {
        // 出队并访问
        int current_node_idx = queue[head++];
        std::cout << GT.nodes[current_node_idx].data << " -> ";

        // 遍历当前节点的所有邻居
        Arc *p = GT.nodes[current_node_idx].firstarc;
        while (p != NULLPTR)    // 边非空
        {
            int neighbor_idx = p->target;
            // 如果邻居未被访问，则标记并入队
            if (!visited[neighbor_idx])
            {
                visited[neighbor_idx] = true;
                queue[tail++] = neighbor_idx;
            }
            p = p->nextarc;
        }
    }
    std::cout << "^" << std::endl;
}

void DFSTraversal(const GraphTable &GT, int node_idx, bool visited[])
{
    visited[node_idx] = true;  // 标记当前节点为已访问
    std::cout << GT.nodes[node_idx].data << " -> ";   // 访问并输出当前节点

    Arc *p = GT.nodes[node_idx].firstarc;  // 获取当前节点的第一条边
    while (p != NULLPTR)    // 第一条边非空
    {
        int neighbor_idx = p->target;
        if (!visited[neighbor_idx]) // 邻居没有被访问过
        {
            DFSTraversal(GT, neighbor_idx, visited);
        }
        p = p->nextarc; // 移动到下一条边
    }
}

void DFS(const GraphTable &GT, char start_node)
{
    int start_idx = findNodeIndexFromTable(GT, start_node);
    if (start_idx == -1)
    {
        std::cout << "[-] Error: Cannot find provided start node: " << start_node << std::endl;
        return;
    }

    bool visited[MAX_LENGTH];   // 存储访问状态标记
    for (int i = 0; i < GT.node_count; i++)
    {
        visited[i] = false; // 初始化
    }

    // 从起始节点开始进行递归遍历
    std::cout << "[*] DFS Traversal: ";
    DFSTraversal(GT, start_idx, visited);

    // 当图为非连通时，处理剩下的节点
    for (int i = 0; i < GT.node_count; i++) {
        if (!visited[i]) {
            DFSTraversal(GT, i, visited);
        }
    }

    std::cout << "^" << std::endl;
}

Status migrateToTable(const GraphMat &G, GraphTable &GT)
{
    // 迁移节点
    for (int i = 0; i < G.size; i++)
    {
        GT.nodes[i].data = G.nodes[i];  // 迁移数据域
        GT.nodes[i].firstarc = NULLPTR; // 初始化边指针
    }
    GT.node_count = G.size; // 获取并设置节点数量
    GT.arc_count = 0;       // 初始化边数量
    for (int line = 0; line < G.size; line++)
    {
        for (int col = 0; col < G.size; col++)
        {
            if (G.arcs[line][col] == 1)
            { // 存在从 line 到 col 的边
                // 创建新边
                Arc *newArc = new Arc;
                if (newArc == NULLPTR)
                {
                    return OVERFLOW;
                }
                newArc->target = col;
                newArc->nextarc = GT.nodes[line].firstarc; // 将新边插入到邻接表的头部
                                                           // 用的是链地址法解决冲突的那种直接插入到头部的方式
                GT.nodes[line].firstarc = newArc;
                GT.arc_count++; // 增加边数量
            }
        }
    }
    return SUCCESS;
}

void printGraphMat(const GraphMat &G)
{
    for (int i = 0; i < G.size; i++)
    {
        for (int j = 0; j < G.size; j++)
        {
            std::cout << G.arcs[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void printGraphTable(const GraphTable &GT)
{
    for (int i = 0; i < GT.node_count; i++)
    {
        std::cout << GT.nodes[i].data << ": ";
        Arc *currentArc = GT.nodes[i].firstarc;
        while (currentArc != NULLPTR)
        {
            std::cout << currentArc->target << " -> ";
            currentArc = currentArc->nextarc;
        }
        std::cout << "^\n";
    }
}

Boolean findPathFromTo(const GraphTable &GT, char from, char to)
{
    int idx = findNodeIndexFromTable(GT, from);
    if (idx == -1)
    {
        return FALSE; // 起始节点不存在
    }
    Arc currentArc = *(GT.nodes[idx].firstarc);
    while (!(currentArc.nextarc == NULLPTR))
    {
        if (GT.nodes[currentArc.target].data == to)
        {
            return TRUE; // 找到路径
        }
        currentArc = *(currentArc.nextarc);
    }
    return FALSE;
}
char getFirstNeighbor(const GraphTable &GT, char node)
{
    int idx = findNodeIndexFromTable(GT, node);
    if (idx == -1)
    {
        return '\0'; // 节点不存在
    }
    Arc *firstArc = GT.nodes[idx].firstarc;
    if (firstArc == NULLPTR)
    {
        return '\0'; // 没有邻居
    }
    else
    {
        return GT.nodes[firstArc->target].data; // 返回第一个邻居的节点数据
    }
}

char getNextNeighbor(const GraphTable &GT, char node, char cur)
{
    int idx = findNodeIndexFromTable(GT, node);
    if (idx == -1)
    {
        return '\0'; // 节点不存在
    }
    Arc *currentArc = GT.nodes[idx].firstarc;
    while (currentArc != NULLPTR)
    {
        if (GT.nodes[currentArc->target].data == cur)
        {
            if (currentArc->nextarc != NULLPTR)
            {
                return GT.nodes[currentArc->nextarc->target].data; // 返回下一个邻居的节点数据
            }
            else
            {
                return '\0'; // 没有下一个邻居
            }
        }
        currentArc = currentArc->nextarc;
    }
    return '\0'; // 当前邻居不存在
}