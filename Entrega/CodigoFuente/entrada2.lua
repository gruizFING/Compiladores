--[[ salida: 

if1_cond1

2

1
2
3
4
5

6
5
4
3
2
1
0

]]--

--TEST

a = 1
b = 2


if a == 1 then
    print("if1_cond1")
elseif b == 2 then
	print("if1_cond2")
end

if a ~= 1 then
	print("if2_cond1")
else
	a = b
	print(a)
end

i = 1
while i < 6 do
	print(i)
	i = i + 1
end

repeat
	print(i)
	i = i - 1
until i < 0
