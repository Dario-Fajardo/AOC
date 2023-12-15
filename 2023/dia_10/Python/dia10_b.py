# Autor: Darío Fajardo

matrix = open('dia_10/input/input.txt').read().split('\n')

from collections import deque

for i, row in enumerate(matrix):
    for j, char in enumerate(row):
        if char == 'S':
            starting_row = i 
            starting_col = j

checked = {(starting_row, starting_col)}
queue = deque([(starting_row, starting_col)])

while queue:
    row, column = queue.popleft()
    character = matrix[row][column]
    # Comprobar todas las direcciones posibles
    if row > 0 and character in 'S|JL' and matrix[row - 1][column] in "|7F" and (row - 1, column) not in checked:
        queue.append((row - 1, column))
        checked.add((row - 1, column))
    if row < len(matrix) - 1 and character in 'S7|F' and matrix[row + 1][column] in "|JL" and (row + 1, column) not in checked:
        queue.append((row + 1, column))
        checked.add((row + 1, column))
    if column > 0 and character in 'S7-J' and matrix[row][column - 1] in "F-L" and (row, column - 1) not in checked:
        queue.append((row, column - 1))
        checked.add((row, column - 1))
    if column < len(matrix[0]) - 1 and character in 'S-LF' and matrix[row][column + 1] in "-J7" and (row, column + 1) not in checked:
        queue.append((row, column + 1))
        checked.add((row, column + 1))

def count_inversions(i, j):
    line = matrix[i]
    inversions = 0
    for k in range(j):
        if not (i, k) in checked:
            continue
        inversions += line[k] in {"J", "L", "|", "S"}
    return inversions

total = 0
for i, line in enumerate(matrix):
    for j in range(len(matrix[0])):
        if not (i, j) in checked:
            invs = count_inversions(i, j)
            if invs % 2 == 1:
                total += 1

print(total)