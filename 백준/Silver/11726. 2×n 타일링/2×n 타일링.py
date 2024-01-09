memo = [0 for _ in range(1001)]
def recursion(n):
    if n == 1:
        return 1
    if n == 2:
        return 2
    if memo[n] != 0:
        return memo[n]

    result = (recursion(n - 1) + recursion(n - 2)) % 10007

    memo[n] = result
    return result

n = int(input())
print(recursion(n))