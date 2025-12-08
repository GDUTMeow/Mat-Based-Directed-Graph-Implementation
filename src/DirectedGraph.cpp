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

int getNodeInDegree(GraphMat G, char node) {

}

int getNodeOutDegree(GraphMat G, char node) {

}

int getNodeDegree(GraphMat G, char node) {

}


void BFS(const GraphTable &GT, char start_node) {

}

void DFS(const GraphTable &GT, char start_node) {

}

Status migrateToTable(GraphMat G, GraphTable &GT) {

}

void showGraphTable(GraphTable G) {

}

void printGraphMat(GraphMat G) {

}

void printGraphTable(GraphTable GT) {

}

Status findPathFromTo(const GraphTable &GT, char from, char to) {

}

char getFirstNeighbor(const GraphTable &GT, char node) {

}

char getNextNeighbor(const GraphTable &GT, char node, char cur_neigh) {

}