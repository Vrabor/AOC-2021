import re
import numpy as np

regex = re.compile(r"\d+")

seen_once = set()
seen_twice = set()

def update_sets(point):
    if point in seen_once:
        seen_twice.add(point)
    else:
        seen_once.add(point)

for line in open("input.txt"):
    l = list(map(int, re.findall(regex, line)))

    # horizontal
    if l[1] == l[3]:
        # y coordinate
        y = l[1]
        # walk the line
        start = min(l[0], l[2])
        end = max(l[0], l[2])
        for i in range(start, end + 1):
            update_sets((i, y))
            
    # vertical
    elif l[0] == l[2]:
        # x coordinate
        x = l[0]
        # walk the line
        start = min(l[1], l[3])
        end = max(l[1], l[3])
        for i in range(start, end + 1):
            update_sets((x, i))

print("Task 1: " + str(len(seen_twice)))

# just get new input for Task 2

seen_once = set()
seen_twice = set()

for line in open("input.txt"):
    l = list(map(int, re.findall(regex, line)))

    # horizontal
    if l[1] == l[3]:
        # y coordinate
        y = l[1]
        # walk the line
        start = min(l[0], l[2])
        end = max(l[0], l[2])
        for i in range(start, end + 1):
            update_sets((i, y))
    # vertical
    elif l[0] == l[2]:
        # x coordinate
        x = l[0]
        # walk the line
        start = min(l[1], l[3])
        end = max(l[1], l[3])
        for i in range(start, end + 1):
            update_sets((x, i))
    # diagonal
    else:
        if l[0] < l[2]:
            # first Point is leftmost
            left = (l[0], l[1])
            right = (l[2], l[3])
        else:
            # second point is leftmost
            left = (l[2], l[3])
            right = (l[0], l[1])

        length = right[0] - left[0]
        
        if left[1] < right[1]:
            # left point is higher, walk down
            for offset in range(0, length + 1):
                new_point = (left[0] + offset, left[1] + offset)
                update_sets(new_point)
        else:
            # left point if lower, walk up
            for offset in range(0, length + 1):
                new_point = (left[0] + offset, left[1] - offset)
                update_sets(new_point)
                
print("Task 2: " + str(len(seen_twice)))
