#include <stdlib.h>
#include "../include/DirectedGraph.h"

Status initGraph(GraphMat &G) {

}

Status insertNode(GraphMat &G, char node) {

}

Status insertArc(GraphMat &G, char from, char to) {

}

Status removeArc(GraphMat &G, char from, char to) {

}

Status removeNode(GraphMat &G, char node) {

}

int getNodeInDegree(const GraphMat &G, char node) {

}

int getNodeOutDegree(const GraphMat &G, char node) {

}

int getNodeDegree(const GraphMat &G, char node) {

}


void BFS(const GraphTable &GT, char start) {

}

void DFS(const GraphTable &GT, char start) {

}

Status migrateToTable(const GraphMat &G, GraphTable &GT) {

}

void printGraphMat(const GraphMat &G) {

}

void printGraphTable(const GraphTable &GT) {

}

Boolean findPathFromTo(const GraphTable &GT, char from, char to) {

}

char getFirstNeighbor(const GraphTable &GT, char node) {

}

char getNextNeighbor(const GraphTable &GT, char node, char cur) {

}