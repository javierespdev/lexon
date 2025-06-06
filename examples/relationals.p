a := 'hola';
b := 'hola';
c := 'mundo';

print(a = b);        # true
print(a = c);        # false

print(a <> b);       # false
print(a <> c);       # true

print(a < c);        # true   ('hola' < 'mundo')
print(a > c);        # false

print(a <= b);       # true
print(a >= b);       # true