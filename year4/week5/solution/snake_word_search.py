#
# POTW Year 4 Week 5
# Snake Word Search
#
# Joel Rorseth
#


# DFS Solution
def dfs(b, i, j, word):

    if len(word) == 0:
        return True

    # End recursion when boundaries are breached
    if i<0 or j<0 or i>=len(b) or j>=len(b[0]):
        return False

    # Check current character
    if word[0] != b[i][j]:
        return False

    # Mark current cell as visited until recursion finishes and returns here
    temp = b[i][j]
    b[i][j] = "$"

    # Recursively check all adjacent cells, then their adjacent cells etc...
    found = dfs(b, i+1, j, word[1:]) or dfs(b, i-1, j, word[1:])\
            or dfs(b, i, j+1, word[1:]) or dfs(b, i, j-1, word[1:])

    b[i][j] = temp
    return found


def main():

    r = int(input())
    c = int(input())

    b = [[0 for x in range(c)] for y in range(r)]

    for row in range(r):
        for j, cell in enumerate(input().split(" ")):
            b[row][j] = cell

    words = set()
    n = int(input())

    for i in range(n):
        words.add(input())

    found = set()


    # Begin search, attempt search starting at every index
    for word in words:
        for i in range(r):
            for j in range(c):
                if dfs(b, i, j, word.upper()):
                    found.add(word)

    # Print in case-insensitive alphabetical order
    for f in sorted(found, key=lambda s: s.lower()):
        print(f)

main()
