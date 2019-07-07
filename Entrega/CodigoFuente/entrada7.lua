--[[ 
Prueba tablas


salida: 
nil
1
10
11
5
5
100
4
hola

]]--

t0 = {}
t1 = {1,10}
t2 = {a = 5, b = 20}
t3 = {[10] = "hola"}

print(t0.a)

print(t1[1])
print(t1[2])
a = t1[1] + t1[2]
print(a)

print(t2.a)
print(t2["a"])

b = t2["a"] * t2.b
c = t2["b"] / t2.a
print(b)
print(c)

print(t3[10])

