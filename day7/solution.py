import numpy as np

with open("input.txt") as inp:
    in_arr = inp.readline().strip().split(",")

parsed = np.array(list(map(lambda x: int(x), in_arr)))

def Task1(inp):
    align_to = np.median(inp)
    return np.sum(np.abs(inp - align_to))

def Task2(inp):
    def ramping_sum(diff):
        # Gauss formula
        return (diff * (diff + 1)) / 2

    align_to = np.ceil(np.mean(inp))
    fuel = 0
    for i in inp:
        fuel += ramping_sum(np.abs(i - align_to))

    align_to = np.floor(np.mean(inp))
    fuel2 = 0
    for i in inp:
        fuel2 += ramping_sum(np.abs(i - align_to))
    
    return min(fuel, fuel2)


print("Task1: " + str(Task1(parsed)))
print("Task2: " + str(Task2(parsed)))