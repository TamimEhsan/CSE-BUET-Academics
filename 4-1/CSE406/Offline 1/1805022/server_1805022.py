# first of all import the socket library
import socket			
import diffie_hellman_1805022 as dh
import aes_1805022 as aes

AES_LEN = 128

# next create a socket object
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)		
print ("Socket successfully created")

# reserve a port on your computer in our
# case it is 12345 but it can be anything
port = 12345			

# Next bind to the port
# we have not typed any ip in the ip field
# instead we have inputted an empty string
# this makes the server listen to requests
# coming from other computers on the network
s.bind(('', port))		
print ("socket binded to %s" %(port))

# put the socket into listening mode
s.listen()	
print ("socket is listening")		

# a forever loop until we interrupt it or
# an error occurs


while True:

# Establish connection with client.
    c, addr = s.accept()	
    print ('Got connection from', addr )

    p,g = dh.get_p_g(AES_LEN)
    a = dh.get_ab(AES_LEN)
    A = dh.get_AB(p,g,a)

    # send a thank you message to the client. encoding to send byte type.
    # convert p,g,A to string to send
  
    msg = str(p) + "," + str(g) + "," + str(A)
    c.send(msg.encode())
    msg = c.recv(1024).decode()
    B = int(msg)
   
    key = dh.get_s(B,a,p)
    # key = 347778857900268250074701329886672412254
    print("s = ",key)
    
    key_bin = bin(key)[2:]
    # print("key_bin = ",key_bin)

    text = "Two One Nine Twot"*3
    [encrypted_hex,encrypted_text,time] = aes.ENCRYPT_AES(AES_LEN,text,key_bin)
    print("encrypted_hex = ",encrypted_hex)
    c.send(encrypted_text.encode())
    
    

    # Close the connection with the client
    c.close()

    # Breaking once connection closed
    break

