###MIPS test program###
.org 4000
Label1: addi $t1,$t0, 200000
move $s0, $t1
beq $s2, $s2, exit
li $t5, 40000
jal Label1
exit: sw $v0, 600($s7)
.end 
