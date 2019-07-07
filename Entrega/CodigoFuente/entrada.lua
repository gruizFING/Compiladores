--[[ salida: 

if1_cond1
if2_cond2
if3_cond3
if4_cond4
while1_1
while2_1
repeat1_1

]]--

if true then
    print("if1_cond1")
end

if false then
    print("if2_cond1")
else
    print("if2_cond2")
end

if false then
    print("if3_cond1")
elseif false then
    print("if3_cond2")
elseif true then
    print("if3_cond3")
end

if false then
    print("if4_cond1")
elseif false then
    print("if4_cond2")
elseif false then
    print("if4_cond3")
else
    print("if4_cond4")
end


while true do
    print("while1_1")
    break
end

while true do
    print("while2_1")
    if true then
        break
    end
end

repeat
    print("repeat1_1")
until true