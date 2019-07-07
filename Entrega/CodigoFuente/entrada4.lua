--[[ salida: 

1000

1

1
2
3
4
5
1
5

1
5

1000

1000
5
Soy variable c local

1
nil

]]--


a = 1
b = 2

function f()
	local a = 1000
	print(a)
end

f()

print(a)

function g()
	for a = 1, 5, 1 do
		if true then
			print(a)
			b = a
		end
	end
	print(a)
	print(b)
end

g()

print(a)
print(b)

f()

function h()
	local a = 5
	local c = "Soy variable c local"
	f()
	print(a)
	print(c)
end

h()

print(a)
print(c)