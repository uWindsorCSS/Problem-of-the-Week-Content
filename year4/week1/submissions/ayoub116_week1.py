def is_suitable_move(L, c, s):
    d = {}
    count = 0
    
    for i in range(0, len(L)):
        diff = s-L[i]
        if diff in d:
            count += d[diff]
        if L[i] in d:
            d[L[i]] += 1
        else:
            d[L[i]] = 1
    return count >= c

def main():
    num_entries = int(input())
    L = [int(i) for i in input().split()]
    c, s = map(int, input().split())
    print(is_suitable_move(L, c, s))

if __name__ == '__main__': main()
