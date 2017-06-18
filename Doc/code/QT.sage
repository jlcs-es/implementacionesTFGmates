y = 0  

# Accion de P. Configuracion de parametros iniciales.

def Setup():
  p = random_prime(2^100)
  q = random_prime(2^100)
  N = p*q
  a = Zmod(p).random_element()
  while a.is_square():
    a = Zmod(p).random_element()    
  b = Zmod(q).random_element()
  while b.is_square():
    b = Zmod(q).random_element()
  s = crt([ZZ(a),ZZ(b)],[p,q])
  #print kronecker(s,N)
  return s,N

# Hiding. 

def Hiding(s,N,b):
  global y
  y = Zmod(N).random_element()
  while gcd(y,N)!=1:
    y = Zmod(N).random_element()
  x = Zmod(N)(s^b*y^2)
  return x

# Opening.

def v(s,N,x,y):
  if Zmod(N)(x-y^2)==0:
    return 0
  elif Zmod(N)(x-s*y^2)==0:
    return 1
  else:
    return -1

s,N = Setup()
x = Hiding(s,N,1)
print v(s,N,x,y)


