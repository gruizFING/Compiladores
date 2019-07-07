--[[ salida: 

3628800
100
90
80
70
60
50
-3628790
1	2
1
2
6
24
120
1		2
1		2
true	34
1e+014
1		1		2
1
2
1		5040

]]--


a,b = 1,2

function factorial(n)
   if n == 0 then
      return 1
   else
      return n * factorial(n - 1)
   end
end

function f()
	local a = 10
	local b = factorial(a)
	print(b)
	
	for i = a, 5, -1 do
		print(i*a)
	end
	print(a-b)
end

f()

print(a,b)

function g()
	for a = 1, 5, 1 do
		print(factorial(a))
	end
	print(a,b)
end

g()
print(a,b)
print(true,1*2*3*4+4+6)
print(100000000000000)

function hola()
	return 1,2
end

c,b,d = 1, hola(), factorial(4)
print(c,b,d)

for a = 1, 5, 1 do
	if(a == 3) then
		break
	end
	print(a)
end

return 1,factorial(7)

