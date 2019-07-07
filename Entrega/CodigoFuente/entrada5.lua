--[[ salida: 

6

factorial de 4: 	24

6

error: attempt to perform arithmetic on local n (a nil value)

]]--


function factorial(n)
   if n == 0 then
      return 1
   else
      return n * factorial(n - 1)
   end
end

print(factorial(3))
print("factorial de 4: ", factorial(4))
print(factorial(3,4))
print(factorial())

