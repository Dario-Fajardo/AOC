grid = open('dia_11/Input/input.txt').read().split('\n')

galaxies = []

for i, row in enumerate(grid):
    for j, char in enumerate(row):
        if char == '#':
            galaxies.append((i, j))
    
sum_of_min_distances = 0
visited = []
for galaxy in galaxies:
    visited.append(galaxy)
    for galaxy2 in galaxies:
        if galaxy != galaxy2 and galaxy2 not in visited:
            print(galaxy, galaxy2)
            extra_distance = 0
            for i in range(min(galaxy[0], galaxy2[0]), max(galaxy[0], galaxy2[0])):
                if grid[i] == '.' * len(grid[i]):
                    extra_distance += 10**6 - 1
            for j in range(min(galaxy[1], galaxy2[1]), max(galaxy[1], galaxy2[1])):
                if all([row[j] == '.' for row in grid]):
                    extra_distance += 10**6 - 1
                    
            sum_of_min_distances += abs(galaxy[0] - galaxy2[0]) + abs(galaxy[1] - galaxy2[1]) + extra_distance
        
print(sum_of_min_distances)