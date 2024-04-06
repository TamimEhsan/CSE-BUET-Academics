from sympy import *
import Interpolate

# x = Symbol('x')
# mx,my,mn = Interpolate.findTable([[19, 1203], [22, 1245], [26, 1378], [28, 1315], [30, 1475]])
# vx,vy,vn = Interpolate.findTable([[19,3000],[22,3500],[26,4000],[28,4500],[30,5000]])
# f = Interpolate.findValue(x,mx,my,mn)*Interpolate.findValue(x,vx,vy,vn)
# f_prime = f.diff(x)
# print(f)
# print(f_prime)
# f_prime = lambdify(x, f_prime)
# print("Force at 25s is: ", f_prime(25))

values = [[2, 7.5], [4.5, 7.5], [5.5, 6], [7, 5]]
X = Symbol('x')
x, y, n = Interpolate.findTable(values)


print("Interpolation Table:")
print(y)

print("Interpolated Equation")
f = Interpolate.findValue(X, x, y, n)
print(f)

print("Simplified equation:")
f = simplify(f)
print(f)


print("\n\n")
f_prime = f.diff(X)

print(f_prime)