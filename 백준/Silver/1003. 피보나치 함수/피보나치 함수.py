n = int(input())

for i in range(n):
    num = int(input())

    if num == 0 :
        print("1 0")
        continue
    fib = [0,1,1]
    if num < 3:
        print("%d %d" %(fib[num-1], fib[num]))
        continue

    for i in range(3, num + 1) :
        fib.append(fib[-1] + fib[-2])

    print("%d %d" %(fib[-2], fib[-1]))
