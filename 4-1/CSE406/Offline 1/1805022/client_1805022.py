# Import socket module
import socket			
import diffie_hellman_1805022 as dh
import aes_1805022 as aes

AES_LEN = 128
# Create a socket object
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)		

# Define the port on which you want to connect
port = 12345			

# connect to the server on local computer
s.connect(('127.0.0.1', port))

# receive data from the server and decoding to get the string.
msg = s.recv(1024).decode()
[p,g,A] = msg.split(",")

p = int(p)
g = int(g)
A = int(A)

b = dh.get_ab(AES_LEN)
B = dh.get_AB(p,g,b)

s.send(str(B).encode())

key = dh.get_s(A,b,p)
# key = 347778857900268250074701329886672412254
print("s = ",key)
key_bin = bin(key)[2:]
# print("key_bin = ",key_bin)
# close the connection

encrypted_text = s.recv(1024).decode()
# print("encrypted_text = ",encrypted_text)


[decrypted_hex,decrypted_text,time] = aes.DECRYPT_AES(AES_LEN,encrypted_text,key_bin)
print("Decrypted Text: ",decrypted_text)
s.close()	
	
