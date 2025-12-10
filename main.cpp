#include <iostream>
#include <string>
#include <stdlib.h>
#include <limits>

#include "include/common.h"
#include "include/art.h"
#include "include/DirectedGraph.h"

#include "include/const.h"

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void showPause()
{
    std::cout << "[*] Press ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void insertNodeHandler(GraphMat &G)
{
    char node = '\0';
    while (1)
    {
        std::cout << "[+] Enter the node you want to insert (1 character only, 0 to return): ";
        std::cin >> node;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清除输入缓冲区
        if (node == '0')
        {
            return;
        }
        if (insertNode(G, node) == SUCCESS)
        {
            std::cout << "[+] Node " << node << " inserted successfully." << std::endl;
        }
        else
        {
            std::cout << "[-] Error: Node " << node << " already exists." << std::endl;
        }
        std::cout << "[*] Current nodes in the graph: " << std::endl;
        printGraphNodes(G);
    }
}

void insertArcHandler(GraphMat &G)
{
    char from = '\0', to = '\0';
    while (1)
    {
        std::cout << "[+] Enter the edge you want to insert in format 'from to' (0 0 to return): ";
        std::cin >> from >> to;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清除输入缓冲区
        if (from == '0' && to == '0')
        {
            return;
        }
        if (from == '0' || to == '0')
        {
            std::cout << "[-] Error: Node cannot be '0'." << std::endl;
            continue;
        }
        if (insertArc(G, from, to) == SUCCESS)
        {
            std::cout << "[+] Edge from " << from << " to " << to << " inserted successfully." << std::endl;
        }
        else
        {
            std::cout << "[-] Error: Unable to insert edge from " << from << " to " << to << "." << std::endl;
        }
        std::cout << "[*] Current arcs in the graph: " << std::endl;
        printGraphArcs(G);
    }
}

void removeNodeHandler(GraphMat &G)
{
    char node = '\0';
    while (1)
    {
        std::cout << "[+] Enter the node that you want to remove (1 character only, 0 to return): ";
        std::cin >> node;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (node == '0')
        {
            return;
        }
        if (removeNode(G, node) == SUCCESS)
        {
            std::cout << "[+] Node " << node << " removed successfully." << std::endl;
        }
        else
        {
            std::cout << "[-] Error: Node " << node << " does not exist." << std::endl;
        }
        std::cout << "[*] Current nodes in the graph: " << std::endl;
        printGraphNodes(G);
    }
}

void removeArcHandler(GraphMat &G)
{
    char from = '\0', to = '\0';
    while (1)
    {
        std::cout << "[+] Enter the edge you want to remove in format 'from to' (0 0 to return): ";
        std::cin >> from >> to;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (from == '0' && to == '0')
        {
            return;
        }
        if (from == '0' || to == '0')
        {
            std::cout << "[-] Error: Node cannot be '0'." << std::endl;
            continue;
        }
        if (removeArc(G, from, to) == SUCCESS)
        {
            std::cout << "[+] Edge from " << from << " to " << to << " removed successfully." << std::endl;
        }
        else
        {
            std::cout << "[-] Error: Unable to remove edge from " << from << " to " << to << "." << std::endl;
        }
        std::cout << "[*] Current arcs in the graph: " << std::endl;
        printGraphArcs(G);
    }
}

void countInDegreeHandler(const GraphMat &G)
{
    char node = '\0';
    while (1)
    {
        std::cout << "[+] Enter the node to calculate its in-degree (1 character only, 0 to return): ";
        std::cin >> node;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (node == '0')
        {
            return;
        }
        int inDegree = getNodeInDegree(G, node);
        if (inDegree != -1)
        {
            std::cout << "[*] The in-degree of node " << node << " is: " << inDegree << std::endl;
        }
        else
        {
            std::cout << "[-] Error: Node " << node << " does not exist." << std::endl;
        }
    }
}

void countOutDegreeHandler(const GraphMat &G)
{
    char node = '\0';
    while (1)
    {
        std::cout << "[+] Enter the node to calculate its out-degree (1 character only, 0 to return): ";
        std::cin >> node;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (node == '0')
        {
            return;
        }
        int outDegree = getNodeOutDegree(G, node);
        if (outDegree != -1)
        {
            std::cout << "[*] The out-degree of node " << node << " is: " << outDegree << std::endl;
        }
        else
        {
            std::cout << "[-] Error: Node " << node << " does not exist." << std::endl;
        }
    }
}

void countDegreeHandler(const GraphMat &G)
{
    char node = '\0';
    while (1)
    {
        std::cout << "[+] Enter the node to calculate its degree (1 character only, 0 to return): ";
        std::cin >> node;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (node == '0')
        {
            return;
        }
        int degree = getNodeDegree(G, node);
        if (degree != -1)
        {
            std::cout << "[*] The degree of node " << node << " is: " << degree << std::endl;
        }
        else
        {
            std::cout << "[-] Error: Node " << node << " does not exist." << std::endl;
        }
    }
}

void BFSHandler(const GraphMat &G)
{
    GraphTable GT;
    if (migrateToTable(G, GT) != SUCCESS)
    {
        std::cout << "[-] Error: Failed to migrate graph to adjacency list." << std::endl;
        return;
    }
    char start_node = '\0';
    while (1)
    {
        std::cout << "[+] Enter the start node for BFS (1 character only, 0 to return): ";
        std::cin >> start_node;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (start_node == '0')
        {
            return;
        }
        BFS(GT, start_node);
    }
}

void DFSHandler(const GraphMat &G)
{
    GraphTable GT;
    if (migrateToTable(G, GT) != SUCCESS)
    {
        std::cout << "[-] Error: Failed to migrate graph to adjacency list." << std::endl;
        return;
    }
    char start_node = '\0';
    while (1)
    {
        std::cout << "[+] Enter the start node for DFS (1 character only, 0 to return): ";
        std::cin >> start_node;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (start_node == '0')
        {
            return;
        }
        DFS(GT, start_node);
    }
}

void printGraphMatHandler(const GraphMat &G)
{
    std::cout << "[*] Adjacency Matrix:" << std::endl;
    printGraphMat(G);
}

void printGraphTableHandler(const GraphMat &G)
{
    GraphTable GT;
    if (migrateToTable(G, GT) != SUCCESS)
    {
        std::cout << "[-] Error: Failed to migrate graph to adjacency list." << std::endl;
        return;
    }
    std::cout << "[*] Adjacency List:" << std::endl;
    printGraphTable(GT);
}

void findPathFromToHandler(const GraphMat &G)
{
    GraphTable GT;
    if (migrateToTable(G, GT) != SUCCESS)
    {
        std::cout << "[-] Error: Failed to migrate graph to adjacency list." << std::endl;
        return;
    }
    char from = '\0', to = '\0';
    while (1)
    {
        std::cout << "[+] Enter the nodes to find path in format 'from to' (0 0 to return): ";
        std::cin >> from >> to;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (from == '0' && to == '0')
        {
            return;
        }
        if (from == '0' || to == '0')
        {
            std::cout << "[-] Error: Node cannot be '0'." << std::endl;
            continue;
        }
        if (findPathFromTo(GT, from, to) == TRUE)
        {
            std::cout << "[*] A path exists from " << from << " to " << to << "." << std::endl;
        }
        else
        {
            std::cout << "[-] No path exists from " << from << " to " << to << "." << std::endl;
        }
    }
}

void getFirstNeighborHandler(const GraphMat &G)
{
    GraphTable GT;
    if (migrateToTable(G, GT) != SUCCESS)
    {
        std::cout << "[-] Error: Failed to migrate graph to adjacency list." << std::endl;
        return;
    }
    char node = '\0';
    while (1)
    {
        std::cout << "[+] Enter the node to find its first neighbor (1 character only, 0 to return): ";
        std::cin >> node;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (node == '0')
        {
            return;
        }
        char neighbor = getFirstNeighbor(GT, node);
        if (neighbor != '\0')
        {
            std::cout << "[*] The first neighbor of node " << node << " is: " << neighbor << std::endl;
        }
        else
        {
            std::cout << "[-] Error: Node " << node << " has no neighbors or does not exist." << std::endl;
        }
    }
}

void getNextNeighborHandler(const GraphMat &G)
{
    GraphTable GT;
    if (migrateToTable(G, GT) != SUCCESS)
    {
        std::cout << "[-] Error: Failed to migrate graph to adjacency list." << std::endl;
        return;
    }
    char node = '\0', cur = '\0';
    while (1)
    {
        std::cout << "[+] Enter the node and its current neighbor to find the next neighbor in format 'node current' (0 0 to return): ";
        std::cin >> node >> cur;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (node == '0' && cur == '0')
        {
            return;
        }
        if (node == '0' || cur == '0')
        {
            std::cout << "[-] Error: Node cannot be '0'." << std::endl;
            continue;
        }
        char neighbor = getNextNeighbor(GT, node, cur);
        if (neighbor != '\0')
        {
            std::cout << "[*] The next neighbor of node " << node << " after " << cur << " is: " << neighbor << std::endl;
        }
        else
        {
            std::cout << "[-] Error: No next neighbor found for node " << node << " after " << cur << "." << std::endl;
        }
    }
}

int main()
{
    GraphMat G;
    int choice = -1;
    int printed_title = 0;
    while (true)
    {
        clearScreen();
        if (!printed_title)
        {
            printed_title = 1,
            RainbowPrint(TITLE, 0.1, 0);
        }
        std::cout << MENU << std::endl;
        std::cout << "[*] Current nodes in the graph" << std::endl;
        printGraphNodes(G);
        std::cout << "[*] Current arcs in the graph" << std::endl;
        printGraphArcs(G);
        std::cout << std::endl;
        std::cout << "[*] Tell me your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (std::cin.fail()) // 避免输入非 choice 接受字符导致无限 loop 炸裂
        {
            std::cout << "[-] Invalid input. Please enter a number between 0 and 15." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            showPause();
            continue;
        }

        switch (choice)
        {
        case 0:
        {
            std::cout << "[*] Goodbye! Exiting program..." << std::endl;
            return 0;
        }
        case 1:
        {
            insertNodeHandler(G);
            break;
        }
        case 2:
        {
            insertArcHandler(G);
            break;
        }
        case 3:
        {
            removeNodeHandler(G);
            break;
        }
        case 4:
        {
            removeArcHandler(G);
            break;
        }
        case 5:
        {
            countInDegreeHandler(G);
            break;
        }
        case 6:
        {
            countOutDegreeHandler(G);
            break;
        }
        case 7:
        {
            countDegreeHandler(G);
            break;
        }
        case 8:
        {
            BFSHandler(G);
            break;
        }
        case 9:
        {
            DFSHandler(G);
            break;
        }
        case 10:
        {
            printGraphMatHandler(G);
            break;
        }
        case 11:
        {
            printGraphTableHandler(G);
            break;
        }
        case 12:
        {
            findPathFromToHandler(G);
            break;
        }
        case 13:
        {
            getFirstNeighborHandler(G);
            break;
        }
        case 14:
        {
            getNextNeighborHandler(G);
            break;
        }
        default:
        {
            std::cout << "[-] Invalid choice. Please enter a number between 0 and 14." << std::endl;
            showPause();
            break;
        }
        }
    }
}