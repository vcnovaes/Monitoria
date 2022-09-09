SECTION  .data 
vetor dd 1,2,3,4,5
vectorSize dd 5
SECTION .text 
extern vecSum 
extern print
global main
main:
  push dword[vectorSize]
  push dword vetor
  call vecSum
  add esp,8
  push eax
  call print 
  add esp,8