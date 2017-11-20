def find_eye_position(A, N):
    sum_left = 0
    sum_right = sum(A[:])
    for i, m in enumerate(A):
        avg_left = 0
        avg_right = 0
        if i != 0:
            sum_left += A[i-1]
            avg_left = sum_left/i
        sum_right -= m
        if i != N-1:
            avg_right = sum_right/(len(A)-1-i)
        if is_eye(avg_left, avg_right, m):
            return i
    return -1

def is_eye(avg_left, avg_right, m):
    diff_left = 15 if avg_left == 0 else (1 - (m/avg_left)) * 100
    diff_right = 15 if avg_right == 0 else (1 - (m/avg_right)) * 100
    if diff_left >= 15 and diff_right >= 15:
        return True
    return False

def main():
    N = int(input())
    A = [int(i) for i in input().split()]
    print(find_eye_position(A, N))

if __name__ == '__main__': main()