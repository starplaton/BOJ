def create_palindrome_name(N, K):
    chars = [chr(ord("a") + i) for i in range(K)]
    name = ["a"] * N
    for i in range(K):
        name[i] = chars[i % K]
    name.sort()
    return "".join(name)


N, K = map(int, input().split())
print(create_palindrome_name(N, K))
