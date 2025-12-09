import random
import string

# --- 配置区 ---
# 节点名称的字符集
NODE_CHAR_SET = string.ascii_letters + string.digits

# 测试参数
TOTAL_OPERATIONS = 50  # 总共要执行多少次随机操作
MAX_NODES = 15  # 图中最多允许有多少个节点

# --- 脚本主体 ---


def generate_random_test_case(filename="random_input.txt"):
    """生成一系列完全随机的操作指令并保存到文件"""

    # 用于跟踪当前图的状态，以生成有效的指令
    nodes_in_graph = set()
    edges_in_graph = set()

    # 指令列表
    commands = []

    for _ in range(TOTAL_OPERATIONS):
        # 随机决定下一步要做什么
        # 我们会给“添加”操作更高的权重，以确保图中有内容可供测试
        possible_choices = [
            "add_node",
            "add_node",
            "add_node",  # 增加添加节点的概率
            "add_edge",
            "add_edge",
            "remove_node",
            "remove_edge",
            "query_degree",
            "bfs",
            "dfs",
            "find_path",
        ]

        # 根据当前图的状态，过滤掉不能执行的操作
        if len(nodes_in_graph) >= MAX_NODES:
            # 如果节点满了，就不能再添加了
            possible_choices = [c for c in possible_choices if c != "add_node"]

        if len(nodes_in_graph) < 2:
            # 如果节点少于2个，既不能添加边，也不能查找两个节点间的路径
            possible_choices = [
                c for c in possible_choices if c not in ["add_edge", "find_path"]
            ]
        if not nodes_in_graph:
            # 如果一个节点都没有，很多操作都不能做
            possible_choices = ["add_node"]  # 只能添加节点

        if not edges_in_graph:
            # 如果没有边，就不能删除边
            possible_choices = [c for c in possible_choices if c != "remove_edge"]

        # 从可行的操作中随机选择一个
        action = random.choice(possible_choices)

        # --- 根据选择的动作生成指令 ---

        if action == "add_node":
            commands.append("1")  # 选择功能 1
            # 随机生成一个不在图中的节点名
            new_node = random.choice(NODE_CHAR_SET)
            while new_node in nodes_in_graph:
                new_node = random.choice(NODE_CHAR_SET)
            commands.append(new_node)
            nodes_in_graph.add(new_node)
            commands.append("0")  # 返回菜单

        elif action == "add_edge":
            commands.append("2")  # 选择功能 2
            from_node, to_node = random.sample(list(nodes_in_graph), 2)
            commands.append(f"{from_node} {to_node}")
            edges_in_graph.add((from_node, to_node))
            commands.append("0 0")  # 返回菜单

        elif action == "remove_node":
            commands.append("3")  # 选择功能 3
            node_to_remove = random.choice(list(nodes_in_graph))
            commands.append(node_to_remove)
            nodes_in_graph.remove(node_to_remove)
            # 同时也要从边集合中移除所有与该节点相关的边
            edges_in_graph = {
                (f, t)
                for f, t in edges_in_graph
                if f != node_to_remove and t != node_to_remove
            }
            commands.append("0")  # 返回菜单

        elif action == "remove_edge":
            commands.append("4")  # 选择功能 4
            edge_to_remove = random.choice(list(edges_in_graph))
            commands.append(f"{edge_to_remove[0]} {edge_to_remove[1]}")
            edges_in_graph.remove(edge_to_remove)
            commands.append("0 0")  # 返回菜单

        elif action == "query_degree":
            # 随机选择一个度数查询 (5, 6, 7)
            degree_choice = random.randint(5, 7)
            commands.append(str(degree_choice))
            node_to_query = random.choice(list(nodes_in_graph))
            commands.append(node_to_query)
            commands.append("0")  # 返回

        elif action == "bfs":
            commands.append("8")
            start_node = random.choice(list(nodes_in_graph))
            commands.append(start_node)
            commands.append("0")

        elif action == "dfs":
            commands.append("9")
            start_node = random.choice(list(nodes_in_graph))
            commands.append(start_node)
            commands.append("0")

        elif action == "find_path":
            commands.append("12")
            # 50% 的概率找存在的边，50% 的概率找完全随机的点
            if random.random() < 0.5 and edges_in_graph:
                from_node, to_node = random.choice(list(edges_in_graph))
            else:
                from_node, to_node = random.sample(list(nodes_in_graph), 2)
            commands.append(f"{from_node} {to_node}")
            commands.append("0 0")

    # --- 测试结束前，打印最终状态 ---
    commands.append("10")  # 打印矩阵
    commands.append("11")  # 打印邻接表

    # --- 最终退出程序 ---
    commands.append("0")

    # --- 写入文件 ---
    with open(filename, "w") as f:
        for command in commands:
            f.write(command + "\n")

    print(
        f"[*] Random test case with {len(commands)} commands generated in '{filename}'!"
    )


if __name__ == "__main__":
    generate_random_test_case()
