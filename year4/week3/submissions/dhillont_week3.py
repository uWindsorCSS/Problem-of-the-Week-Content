from collections import defaultdict
if __name__ == '__main__':
    # input of friendships
    numF = int(input())
    Finput = []
    while numF != 0:
        Finput.append(input().split(" "))
        numF -= 1
    # input of posts liked/disliked by people
    numP = int(input())
    Pinput = []
    while numP != 0:
        Pinput.append(input().split(" "))
        numP -= 1
    # u is the user and t is minimum number of likes
    u, t = input().split(" ")
    t = int(t)
    # list of u's friends
    uF = [f for fs in Finput if u in fs for f in fs if f != u]
    # list of posts liked/disliked by friends
    uFP = [(xyz[1], xyz[2]) for xyz in Pinput if xyz[0] in uF]
    # create dict, keys are posts and values are sum of likes(1) and dislikes(-1)
    uFPDict = defaultdict(int)
    for y, z in uFP:
        uFPDict[y] += int(z)
    # print out posts(keys) that have at least t likes
    print('\n'.join([p for p, l in uFPDict.items() if l >= t]))
