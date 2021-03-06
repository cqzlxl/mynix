.section .text

.global outb
outb:
//  - send a byte to an I/O port
//  stack:
//      [esp + 8] the data byte
//      [esp + 4] the I/O port
//      [esp + 0] return address
    movb 8(%esp), %al           // move the data to be sent into the al register
    movw 4(%esp), %dx           // move the address of the I/O port into the dx register
    outb %al, %dx               // send the data to the I/O port
    ret                         // return to the calling function


.global inb
inb:
//  - returns a byte from the given I/O port
//  stack:
//      [esp + 4] The address of the I/O port
//      [esp + 0] The return address
    movw 4(%esp), %dx           // move the address of the I/O port to the dx register
    movl $0, %eax
    inb  %dx, %al               // read a byte from the I/O port and store it in the al register
    ret                         // return the read byte
