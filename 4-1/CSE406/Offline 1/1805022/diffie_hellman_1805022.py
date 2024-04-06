# generate prime of at least k bits length

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
    while not MillerRabin(p, 50) or not MillerRabin(p*2+1, 50):
        p = generate_prime_candidate(length)
    return p*2+1


def generate_primitive_root(p,min,max):

    p2 = (p-1)//2
    
    while True:
        g = random.randint(min, max)
        if binpower(g, p2, p) != 1:
            return g



def get_p_g(k):
    p = generate_prime_number(k)
    g = generate_primitive_root(p,2,p-2)
    return p,g

def get_ab(k):
    a = generate_prime_number(k//2+1)
    return a
   
def get_AB(p,g,a):
    A = binpower(g, a, p)
    return A

def get_s(B,a,p):
    s = binpower(B, a, p)
    return s

def Diffie_Hellman_timer(k):
    start_time = time.time()
    p = generate_prime_number(k)
    p_time = time.time() - start_time
    start_time = time.time()
    g = generate_primitive_root(p,2,p-2)
    g_time = time.time() - start_time
    start_time = time.time()
    a = generate_prime_number(k//2+1)
    b = generate_prime_number(k//2+1)
    ab_time = (time.time() - start_time )/2
    start_time = time.time()
    A = binpower(g, a, p)
    B = binpower(g, b, p)
    AB_time = (time.time() - start_time)/2
    start_time = time.time()
    s1 = binpower(B, a, p)
    s2 = binpower(A, b, p)
    ss_time = (time.time() - start_time)/2
    shared_key = bin(s1)[2:]
    if s1 == s2:
        # print("p = ",p)
        # print("g = ",g)
        # print("a = ",a)
        # print("b = ",b)
        # print("A = ",A)
        # print("B = ",B)
        # print("s1 = ",s1)
        # print("s2 = ",s2)
        return [p_time,g_time,ab_time,AB_time,ss_time]
    else:
        print("Error")
        return False
    



def main():
    for k in [128,192,256]:
        # Run the function 5 times
        results = [Diffie_Hellman_timer(k) for _ in range(5)]

        # Calculate the average of each index of the tuple
        averages = [
            sum(values) / len(values)
            for values in zip(*results)
        ]
        averages = [ '%.5f' % elem for elem in averages]
        print(averages)

# main()