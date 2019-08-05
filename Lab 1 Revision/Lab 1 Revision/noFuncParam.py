def a(x):
    return x * x


def b(func, x):
    a = 3
    return func(x) + func(a)

print(b(a, 2))
