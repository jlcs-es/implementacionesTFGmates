s = 0
t = 0

def Setup():
  global s
  p = random_prime(2^100)
  q = random_prime(2^100)
  N = p*q
  s = Zmod(N).random_element()
  x = s^2
  return x,N  

def elegir_u(x,N):
  global t
  t = Zmod(N).random_element()
  return t^2

def enviar_prueba(x,N,u,b):
  if b == 0:
    return t
  else:
    return Zmod(N)(t*s)

x,N = Setup()
u = elegir_u(x,N)
w = enviar_prueba(x,N,u,1)

print "Comprobar"
print Zmod(N)(w^2)
print Zmod(N)(u*x)
