def a(x):
    return x * x


def b(func, x):
    a = 3
    return func(x) + func(a)  # + a(1) # 'int' object is not callable

print(b(a, 2))
