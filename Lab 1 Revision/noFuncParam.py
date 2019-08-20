def a(x):
    return x * x


def b(x):
    return x**3


def c(func, x):
    a = 3
    return func(x) + func(a)



print(c(a, 2))
print(c(b, 2))
