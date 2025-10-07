import networkx as nx

import networkx as nx
import matplotlib.pyplot as plt

def create_graph(): 
    G = nx.Graph()

    edges = [
    ("Viana do Castelo","Braga",50),
    ("Viana do Castelo","Porto",80),
    ("Vila Real","Bragança",140),
    ("Braga","Vila Real",100),
    ("Braga","Porto",50),
    ("Porto","Vila Real",120),
    ("Porto","Aveiro",70),
    ("Vila Real","Viseu",110),
    ("Vila Real","Bragança",200),
    ("Vila Real","Guarda",150),
    ("Bragança","Guarda",200),
    ("Viseu","Guarda",80),
    ("Viseu","Coimbra",80),
    ("Viseu","Aveiro",100),
    ("Aveiro","Coimbra",80),
    ("Coimbra","Guarda",160),
    ("Coimbra","Leiria",70),
    ("Coimbra","Castelo Branco",160),
    ("Guarda","Castelo Branco",100),
    ("Castelo Branco","Portalegre",80),
    ("Leiria","Lisboa",130),
    ("Santarém","Lisboa",70),
    ("Santarém","Évora",120),
    ("Santarém","Castelo Branco",200),
    ("Santarém","Portalegre",150),
    ("Lisboa","Setúbal",50),
    ("Setúbal","Beja",135),
    ("Setúbal","Faro",260),
    ("Évora","Beja",80),
    ("Portalegre","Évora",100),
    ("Beja","Faro",170)
]

    for u, v, w in edges:
        G.add_edge(u, v, weight=w)

    #pos = nx.spring_layout(G, seed=42)
    #nx.draw(G, pos, with_labels=True, node_color="lightblue", node_size=1200, font_size=9)
    #nx.draw_networkx_edge_labels(G, pos, edge_labels=nx.get_edge_attributes(G, 'weight'))
    
    return G

def path_length(G, caminho):
    total_distance = 0

    for i in range(len(caminho) - 1):
        x = caminho[i]
        y = caminho[i+1]

        if G.has_edge(x,y):
            distance = G[x][y]["weight"]
            total_distance += distance
        else:
            print(f"There was an invalid path inputed: {x} to {y}")
            break

    return total_distance

def get_bfs_path(G, start, destination):
    bfs_tree = nx.bfs_tree(G, source=start)

    if destination in bfs_tree:
        path = nx.shortest_path(bfs_tree, source=start, target=destination)
        return path
    
def get_dfs_path(G, start, destination):
    dfs_tree = nx.dfs_tree(G, source=start)

    if destination in dfs_tree:
        path = nx.shortest_path(dfs_tree, source=start, target=destination)
        return path

def dist_heuristic(a, b):
    return 0

def get_a_star_path(G, start, destination):
    path = nx.astar_path(G, start, destination, heuristic=dist_heuristic, weight="cost")
    return path

def main(): 
    G = create_graph()
    path = []

    while (True):
        city = input("Input a city to add path(0 to exit): ")

        if city == "0":
            break

        path.append(city)

    distance = path_length(G, path)
    print(f"The total distance is {distance}")

    start = input("Input a starting point: ")
    destination = input("Input a ending point: ")

    ppl_path = get_bfs_path(G, start, destination)
    print(f"The path from {start} to {destination} with the shortest length({path_length(G, ppl_path)}) is {ppl_path}")

    a_star_path = get_a_star_path(G, start, destination)
    print(f"The shortest path using A* is: {a_star_path}")

    city_pairs = [
        ("Viana do Castelo", "Faro"),
        ("Braga", "Évora"),
        ("Porto", "Beja"),
        ("Vila Real", "Lisboa"),
        ("Aveiro", "Castelo Branco"),
        ("Coimbra", "Faro"),
        ("Leiria", "Guarda"),
        ("Santarém", "Viseu"),
        ("Setúbal", "Portalegre"),
        ("Bragança", "Lisboa")
    ]
    print("--------------------------")
    print("| Number |  BFS  |  A*   |  DFS  |")
    
    i = 1
    for (x,y) in city_pairs:
        bfs_path = get_bfs_path(G, x, y)
        a_star_path = get_a_star_path(G, x, y)
        dfs_path = get_dfs_path(G, x, y)

        print(f"|   {i}    |  {path_length(G, bfs_path)}  |  {path_length(G, a_star_path)}  |  {path_length(G, dfs_path)}  |")
        i = i+1

if __name__ == "__main__":
    main()
    
