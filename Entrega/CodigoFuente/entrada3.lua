--[[ salida: 

1

2
f_else

8
f_else

g()_while
g()_while

]]--


a = 1
b = 2

function f()
	if a == 1 then
		print(a)
	else
		print(b)
		print("f_else")
	end
end

f()

a = b

f()

b = 8

f()

function g()
	while b < 10 do
		print("g()_while")
		b = b + 1
	end
end

g()