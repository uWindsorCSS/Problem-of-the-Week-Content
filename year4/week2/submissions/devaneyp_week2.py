def findEye(readings):
	if len(readings) == 1:
		return 0
	if readings[0] / (sum(readings[1:]) / len(readings[1:])) <= 0.85:
		return 0
	for i in range(1, len(readings) - 1):
		if readings[i] / (sum(readings[:i]) / len(readings[:i])) <= 0.85 and readings[i] / (sum(readings[i+1:]) / len(readings[i+1:])) <= 0.85:
			return i
	if readings[-1] / (sum(readings[:-1]) / len(readings[:-1])) <= 0.85:
		return len(readings) - 1
	return -1
n = input()
data = list(map(int, input().split()))
print(findEye(data))