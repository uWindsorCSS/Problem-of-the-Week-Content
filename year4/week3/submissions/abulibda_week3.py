#potw
#abdul abu libda
#104613522
n = int(input())
a = [] #list containing all people
b = [] #2d list containing x's friends, x is indexed by position in a
for i in range(n):
    asd = str(input())
    if asd.split()[0] not in a:
        a.append(asd.split()[0])
        b.append([])
    if asd.split()[1] not in a:
        a.append(asd.split()[1])
        b.append([])
    b[a.index(asd.split()[0])].append(asd.split()[1])
    b[a.index(asd.split()[1])].append(asd.split()[0])
m = int(input())
c = []
d = []
like = []
dislike = []
score = []
for i in range(m):
    asd2 = str(input())
    if asd2.split()[0] not in c:
        c.append(asd2.split()[0])
        like.append([])
        dislike.append([])
    if asd2.split()[1] not in d:
        d.append(asd2.split()[1])
        score.append([0])
    if asd2.split()[2] == "1":
        like[c.index(asd2.split()[0])].append(asd2.split()[1])
    elif asd2.split()[2] == "-1":
        dislike[c.index(asd2.split()[0])].append(asd2.split()[1])

o = str(input())
target = o.split()[0]
num = int(o.split()[1])
friends = b[a.index(target)]
numfriends = len(friends)
liked = []
disliked = []
posts = []
postlike = []
postdislike = []
for friend in friends:
    if friend in c:
        liked = like[c.index(friend)]
        disliked = dislike[c.index(friend)]
    for x in liked:
        score[d.index(x)][0] += 1
    for y in disliked:
        score[d.index(y)][0] -= 1

for z in score:
    if int(z[0]) >= num:
        print(d[score.index(z)])