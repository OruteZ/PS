memo = [0 for _ in range(46)]
def fib(n):
    if n == 0:
        return 0
    if n == 1:
        return 1
    if memo[n] != 0:
        return memo[n]

    answer = fib(n - 2) + fib(n - 1)
    memo[n] = answer
    
    return answer


number = int(input())
print(fib(number))
