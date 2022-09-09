extern print 
SECTION .data 
  var dd 6 
SECTION .text 
global main 
main:
  push dword[var] 
  call print
  add esp, 4
