activate venv: ./venv/Scripts/Activate.ps1
### Key generation
- the key should be of length 128/192/256 bits
- If the given target length is of 128 but key len is less or more then pad or trim to make it to the expected length.
- we need to break the input text in chunks of 128 bit. If last chunk is not of 128 bit then pad it
- Convert it hex format and group them by 2 digit (Cause 1 hex digit is 4 byte, so 2*4 = 8 byte to represent a character) we should have 128/8 = 16 hex numbers
- Then convert it to a matrix of form 16/4 : 4 .
- divide in words of length 4
- then start round key generation rounds
- follow AES simulation slides

w[8] = w[4] ^ g(w[7])




# Diffie Hellman
Generating big primes:
https://medium.com/@ntnprdhmm/how-to-generate-big-prime-numbers-miller-rabin-49e6e6af32fb

primite roots of big prime:
https://crypto.stackexchange.com/questions/56155/primitive-root-of-a-very-big-prime-number-elgamal-ds

Safe primes and diffie Hellman
https://www.johndcook.com/blog/2017/01/12/safe-primes-sylow-theorems-and-cryptography/

primality test online
https://bigprimes.org/primality-test

