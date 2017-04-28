import sys
from random import randint
from collections import namedtuple

prime_low_bound = 61
prime_high_bound = 192
key_bound = 31
max_input_message = prime_low_bound * prime_low_bound - 1
RSAKeys = namedtuple("RSAKeys", "enc dec cy")


# Testing whether a number is prime
def test_prime(n):
    t_f = True
    for i in range(2, n, +1):
        if n % i == 0:
            t_f = False
    return t_f


# Randomly generate a prime number roughly in the range of
#   [PRIME_LOW_BOUND, RPIME_HIGH_BOUND).
def gen_prime():
    n = randint(0, prime_high_bound - prime_low_bound) + prime_low_bound
    if n % 2 == 0:
        n -= 1
    while not test_prime(n):
        n -= 2
    return n


# Find the greatest common divisor (gcd) of two positive numbers
def gcd(n1, n2):
    if n1 >= n2:
        greater = n1
        smaller = n2
    else:
        greater = n2
        smaller = n1
    divisor = smaller
    while not(greater % smaller == 0):
        divisor = greater % smaller
        greater = smaller
        smaller = divisor
    return divisor


# Randomly generate a positive integer that is coprime to the given
#   positive integer n and approximately in the range of [KEY_LOW_BOUND, n).
def gen_coprime(n):
    coprime = randint(0, n - key_bound) + key_bound
    if n % 2 == 0:
        if coprime % 2 == 0:
            coprime -= 1
        while not(gcd(n, coprime) == 1):
            coprime -= 2
    else:
        while not (gcd(n, coprime) == 1):
            coprime -= 1
    return coprime


# Generate a public-private key pair and the corresponding modulus cipher.
def gen_keys():
    p = gen_prime()
    q = gen_prime()
    while p == q:
        p = gen_prime()
        q = gen_prime()
    t = (p - 1) * (q - 1)
    e = gen_coprime(t)
    while not(gcd(t, e) == 1):
        e = gen_coprime(t)
    x = 1
    while not((x * t + 1) % e == 0):
        x += 1
    d = (x * t + 1) / e
    return RSAKeys(enc=e, dec=d, cy=(p * q))


# Find the remainder of pow(m, k)
def pow_mod(m, k, c):
    result = 1
    for i in range(0, k, +1):
        result = (result * m) % c
    return result


"""
Encryption function
    Parameters:
    m - the original message, or plaintext
    e - the public encryption key
    c - the modulus cipher p*q
    Returns:
    the encrypted message (i.e. ciphertext, which is an int)
"""


def encrypt(m, e, c):
    return pow_mod(m, e, c)


"""
Decryption function
    Parameters:
    s - the encrypted message (i.e. ciphertext)
    d - the private decryption key
    c - the modulus cipher p*q
    Returns:
    the decrypted message, i.e. the original message
"""


def decrypt(s, d, c):
    if s < 0 & s >= c:
        print("Something is wrong.")
        return -1
    return pow_mod(s, d, c)


def main(arg):
    if arg.argv[1] == "-genkeys":
        keys = gen_keys()
        print("Generating keys...")
        print("Public encryption key e: ", keys.enc)
        print("Private decryption key d: ", int(keys.dec))
        print("Modulus cipher c: ", keys.cy, "\n")
    elif arg.argv[1] == "-enc":
        m = input("What is the message? ")
        e = eval(input("What is the encryption key? "))
        c = eval(input("What is the modulus cipher? "))
        print("Encrypting keys...")
        s = 0
        multy = 1
        for element in range(0, len(m), +1):
            temp = encrypt(ord(m[element]), e, c)
            s += temp * multy
            multy *= 100000
        print("CipherText: ", s, "\n")
    elif arg.argv[1] == "-dec":
        s = input("What is the cipherText? ")
        d = eval(input("What is the decryption key? "))
        c = eval(input("What is the modulus cipher? "))
        print("Decrypting keys...")
        string = ""
        size = int(len(s)/5) + 1
        for i in range(0, size, +1):
            temp = s[-5:]
            s = s[:-5]
            string += chr(decrypt(int(temp), d, c))
        """
        while s > 0:
            past = int(s % 100000)
            temp = decrypt(past, d, c)
            string += chr(temp)
            s = ((s - past) / 100000)"""

        print("Plain Text: ", string, "\n")
    else:
        sys.exit("Error")

if __name__ == '__main__':
    main(sys)
