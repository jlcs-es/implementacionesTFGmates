p = 0
q = 0

def Setup():
  global p,q
  p = random_prime(2^100)
  q = random_prime(2^100)
  N = p*q
  s = Zmod(N).random_element()
  x = s^2
  return x,N  

def elegir_u(x,N):
  t = Zmod(N).random_element()
  return t^2

def enviar_prueba(x,N,u,b):
  if b == 0:
    z = u
  else:
    z = x*u
  zp = Zmod(p)(z)
  zq = Zmod(q)(z)
  w = crt([ZZ(sqrt(zp)),ZZ(sqrt(zq))],[p,q])
  return w

x,N = Setup()
u = elegir_u(x,N)
w = enviar_prueba(x,N,u,1)

print "Comprobar"
print Zmod(N)(w^2)
print Zmod(N)(u*x)
