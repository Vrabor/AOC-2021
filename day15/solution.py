import heapq
import numpy as np


def dijkstra(graph, start, end):
    '''Dijkstra path-finding on implicit graph'''
    def add_with_checks(position, path_len):
        pos_x, pos_y = position
        if pos_x > 0:
            new_pos = (pos_x - 1, pos_y)
            new_len = path_len + graph[new_pos[0], new_pos[1]]
            heapq.heappush(pqueue, (new_len, new_pos)) 
        if pos_y > 0:
            new_pos = (pos_x, pos_y - 1)
            new_len = path_len + graph[new_pos[0], new_pos[1]]
            heapq.heappush(pqueue, (new_len, new_pos)) 
        if pos_x < x - 1:
            new_pos = (pos_x + 1, pos_y)
            new_len = path_len + graph[new_pos[0], new_pos[1]]
            heapq.heappush(pqueue, (new_len, new_pos)) 
        if pos_y < y - 1:
            new_pos = (pos_x, pos_y + 1)
            new_len = path_len + graph[new_pos[0], new_pos[1]]
            heapq.heappush(pqueue, (new_len, new_pos)) 
    
    pqueue = []
    x, y = graph.shape
    visited = set()
    next_pos = start
    current_length = 0
    add_with_checks(next_pos, current_length)
    while next_pos != end:
        current_length, next_pos = heapq.heappop(pqueue)
        if next_pos in visited:
            continue
        add_with_checks(next_pos, current_length)
        visited.add(next_pos)
    
    return current_length

def extend_risk_map(risk_map, times):
    extended_map = np.array(risk_map)
    for i in range(1, times):
        to_stack = risk_map + i
        extended_map = np.hstack((extended_map, to_stack))

    top_matrix = extended_map # extend with already horizontally extended map
    for i in range(1, times):
        to_stack = top_matrix + i
        extended_map = np.vstack((extended_map, to_stack))

    def fix_risks(x):
        if x > 9:
            return x - 9
        else:
            return x
    fix_array = np.frompyfunc(fix_risks, 1, 1)

    return fix_array(extended_map)

with open("input.txt", encoding="UTF-8") as f:
    lines_raw = f.readlines()

chars = list(map(lambda x: list(x.strip()), lines_raw))
nums = list(map(lambda x: list(map(ord, x)), chars))
risk_map = np.array(nums) - ord('0')
task1 = dijkstra(risk_map, (0, 0), (99, 99))
print("Task1: " + str(task1))
extended_risk_map = extend_risk_map(risk_map, 5)
task2 = dijkstra(extended_risk_map, (0, 0), (499, 499))
print("Task2: " + str(task2))

