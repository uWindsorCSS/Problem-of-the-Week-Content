class WordFinder():

    def __init__(self, r, c, grid, w, words):
        self.r = r
        self.c = c
        self.grid = grid
        self.w = w
        self.words = words
        self.character_map = self.build_character_map()
        self.results = []

    def build_character_map(self):
        character_map = {}
        for r in range(self.r):
            for c in range(self.c):
                char = self.grid[r][c]
                if char in character_map:
                    character_map[char].append((r,c))
                else:
                    character_map[char] = [(r,c)]

        return character_map


    def find_words(self):
        for word in self.words:
            if word[0].upper() in self.character_map:
                for p in self.character_map[word[0].upper()]:
                    if self.dfs(word.upper(), [p], p, 1, False):
                        self.results.append(word)
                        break

        self.results = sorted(self.results, key=str.lower)

    def dfs(self, w, visited, p, i, found):
        if found:
            return found
        if i == len(w):
            return self.dfs(w, visited, p, i, True)
        qps = self.determine_qualifying_positions(w[i], visited, p)
        for qp in qps:
            found = (found or self.dfs(w, visited.copy(), qp, i+1, found))

        return found

    def determine_qualifying_positions(self, char, visited, p):
        qps = []
        # top
        if p[0] != 0 and not (p[0]-1,p[1]) in visited and self.grid[p[0]-1][p[1]] == char:
            qps.append((p[0]-1,p[1]))
        # right
        if p[1] < (self.c - 1) and not (p[0],p[1]+1) in visited and self.grid[p[0]][p[1]+1] == char:
            qps.append((p[0],p[1]+1))
        # bottom
        if p[0] < (self.r - 1) and not (p[0]+1,p[1]) in visited and self.grid[p[0]+1][p[1]] == char:
            qps.append((p[0]+1,p[1]))
        # left
        if p[1] != 0 and not (p[0],p[1]-1) in visited and self.grid[p[0]][p[1]-1] == char:
            qps.append((p[0],p[1]-1))

        visited.extend(qps)
        return qps

def main():
    r = int(input())
    c = int(input())
    grid = [[c for c in input().split()] for row in range(r)]
    w = int(input())
    words = [input().strip() for word in range(w)]

    ws = WordFinder(r,c,grid,w,words)
    ws.build_character_map()
    ws.find_words()
    for word in ws.results:
         print(word)

if __name__ == '__main__': main()
