SECTION .text
global subtraction
global sum 
sum: 
  enter 0,0 
  mov eax, [ebp + 8]
  add eax, [ebp + 12]
  add eax, [ebp + 16]
  leave 
  ret 
subtraction:
  enter 0,0
  mov eax, [ebp+8]
  sub eax, [ebp+12]
  leave 
  ret