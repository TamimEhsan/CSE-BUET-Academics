
import random,time

def binpower(base, e, mod):
    result = 1
    base %= mod
    while e:
        if e & 1:
            result = (result * base) % mod
        base = (base * base) % mod
        e >>= 1
    return result

def check_composite(n, a, d, s):
    x = binpower(a, d, n)
    if x == 1 or x == n - 1:
        return False
    for _ in range(1, s):
        x = (x * x) % n
        if x == n - 1:
            return False
    return True

def MillerRabin(n, iter=20):
    if n < 4:
        return n == 2 or n == 3

    s = 0
    d = n - 1
    while d & 1 == 0:
        d >>= 1
        s += 1

    for _ in range(iter):
        a = random.randint(2, n - 3)
        if check_composite(n, a, d, s):
            return False
    return True

def generate_prime_candidate(length):
    p = random.getrandbits(length)
    p |= (1 << length - 1 ) | 1
    return p

def generate_prime_number(length=1024):
    p = generate_prime_candidate(length)
    while not MillerRabin(p, 50):
        p = generate_prime_candidate(length)
    return p

def gcd(a,b):
    if b == 0:
        return a
    else:
        return gcd(b,a%b)

def egcd(a, b):
    if b == 0:
        return (a, 1, 0)
    else:
        d, x, y = egcd(b,a%b)
        return  (d,y, x - (a // b) * y)
    


def modinv(a, m):
    g, x, y = egcd(a,m)
    if g != 1:
        raise Exception('modular inverse does not exist')
    else:
        return (x % m + m )%m
def main():
    k = 128
    p = generate_prime_number(k//2)
    q = generate_prime_number(k//2)
    while p == q:
        q = generate_prime_number(k//2)
    n = p*q
    phi = (p-1)*(q-1)

    e = random.randint(2,phi-1)
    while gcd(e,phi) != 1:
        e = random.randint(2,phi-1)
    
    d = modinv(e,phi)

    print("public key : {",e,",",n,"}")
    print("private key : {",d,",",n,"}")

main()