# 9 Examining Source Files

## 9.1 Printing Source Lines

## 9.2 Specifying a Location

## 9.3 Editing Source Files



## 9.6 Source and Machine Code



### `disassemble`



#### Example

[Few GDB Commands – Debug Core, Disassemble, Load Shared Library](https://www.thegeekstuff.com/2014/03/few-gdb-commands/):

```assembly
(gdb) disassemble main
Dump of assembler code for function main:
   0x00000000004004ac :	push   %rbp
   0x00000000004004ad :	mov    %rsp,%rbp
   0x00000000004004b0 :	mov    $0x0,%eax
   0x00000000004004b5 :	pop    %rbp
   0x00000000004004b6 :	retq   
End of assembler dump.
```