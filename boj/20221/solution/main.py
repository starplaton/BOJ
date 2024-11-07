last = ""
ans = []
for _ in range(int(input())):
    s = input().replace("6", "9")
    if len(s) > len(last):
        last = s.replace("9", "6")
    elif s < last:
        print("impossible")
        exit(0)
    else:
        done = ""
        for i in range(len(s)):
            c, s = s[0], s[1:]
            if done + c.replace("9", "6") + s >= last:
                done += c.replace("9", "6")
            else:
                done += c
        last = done
    ans.append(last)

print("possible")
print(*ans, sep="\n")
