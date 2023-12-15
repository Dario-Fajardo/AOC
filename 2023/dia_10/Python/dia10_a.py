# Autor: Darío Fajardo

from collections import deque

matrix = open('input/test2.txt').read().split('\n')

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

print(len(checked) // 2)