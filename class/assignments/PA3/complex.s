	.data
	.align	2
	.globl	class_nameTab
	.globl	Main_protObj
	.globl	Int_protObj
	.globl	String_protObj
	.globl	bool_const0
	.globl	bool_const1
	.globl	_int_tag
	.globl	_bool_tag
	.globl	_string_tag
_int_tag:
	.word	3
_bool_tag:
	.word	4
_string_tag:
	.word	5
	.globl	_MemMgr_INITIALIZER
_MemMgr_INITIALIZER:
	.word	_NoGC_Init
	.globl	_MemMgr_COLLECTOR
_MemMgr_COLLECTOR:
	.word	_NoGC_Collect
	.globl	_MemMgr_TEST
_MemMgr_TEST:
	.word	0
	.word	-1
str_const43:
	.word	5
	.word	5
	.word	String_dispTab
	.word	int_const0
	.byte	0	
	.align	2
	.word	-1
str_const42:
	.word	5
	.word	6
	.word	String_dispTab
	.word	int_const5
	.ascii	"Shape"
	.byte	0	
	.align	2
	.word	-1
str_const41:
	.word	5
	.word	6
	.word	String_dispTab
	.word	int_const8
	.ascii	"String"
	.byte	0	
	.align	2
	.word	-1
str_const40:
	.word	5
	.word	6
	.word	String_dispTab
	.word	int_const9
	.ascii	"Bool"
	.byte	0	
	.align	2
	.word	-1
str_const39:
	.word	5
	.word	5
	.word	String_dispTab
	.word	int_const10
	.ascii	"Int"
	.byte	0	
	.align	2
	.word	-1
str_const38:
	.word	5
	.word	6
	.word	String_dispTab
	.word	int_const9
	.ascii	"Main"
	.byte	0	
	.align	2
	.word	-1
str_const37:
	.word	5
	.word	5
	.word	String_dispTab
	.word	int_const11
	.ascii	"IO"
	.byte	0	
	.align	2
	.word	-1
str_const36:
	.word	5
	.word	6
	.word	String_dispTab
	.word	int_const8
	.ascii	"Object"
	.byte	0	
	.align	2
	.word	-1
str_const35:
	.word	5
	.word	8
	.word	String_dispTab
	.word	int_const12
	.ascii	"<basic class>"
	.byte	0	
	.align	2
	.word	-1
str_const34:
	.word	5
	.word	13
	.word	String_dispTab
	.word	int_const13
	.ascii	"It is some other generic Object.\n"
	.byte	0	
	.align	2
	.word	-1
str_const33:
	.word	5
	.word	10
	.word	String_dispTab
	.word	int_const14
	.ascii	"It is the Main object.\n"
	.byte	0	
	.align	2
	.word	-1
str_const32:
	.word	5
	.word	13
	.word	String_dispTab
	.word	int_const15
	.ascii	"It is a Shape (but not a Circle).\n"
	.byte	0	
	.align	2
	.word	-1
str_const31:
	.word	5
	.word	9
	.word	String_dispTab
	.word	int_const16
	.ascii	"It is a Circle.\n"
	.byte	0	
	.align	2
	.word	-1
str_const30:
	.word	5
	.word	13
	.word	String_dispTab
	.word	int_const17
	.ascii	"  - Analyzing an object's type: "
	.byte	0	
	.align	2
	.word	-1
str_const29:
	.word	5
	.word	9
	.word	String_dispTab
	.word	int_const18
	.ascii	"\n--- Test End ---\n"
	.byte	0	
	.align	2
	.word	-1
str_const28:
	.word	5
	.word	10
	.word	String_dispTab
	.word	int_const14
	.ascii	"  - Negative of 10 is: "
	.byte	0	
	.align	2
	.word	-1
str_const27:
	.word	5
	.word	11
	.word	String_dispTab
	.word	int_const19
	.ascii	"  - Block evaluated to: "
	.byte	0	
	.align	2
	.word	-1
str_const26:
	.word	5
	.word	14
	.word	String_dispTab
	.word	int_const20
	.ascii	"  - This is inside a block expression.\n"
	.byte	0	
	.align	2
	.word	-1
str_const25:
	.word	5
	.word	17
	.word	String_dispTab
	.word	int_const21
	.ascii	"5. Testing other expressions (blocks, negation)...\n"
	.byte	0	
	.align	2
	.word	-1
str_const24:
	.word	5
	.word	12
	.word	String_dispTab
	.word	int_const22
	.ascii	"  - 'self' is void. (Error)\n\n"
	.byte	0	
	.align	2
	.word	-1
str_const23:
	.word	5
	.word	14
	.word	String_dispTab
	.word	int_const23
	.ascii	"  - 'self' is not void, as expected.\n\n"
	.byte	0	
	.align	2
	.word	-1
str_const22:
	.word	5
	.word	14
	.word	String_dispTab
	.word	int_const20
	.ascii	"  - 'void_object' is not void. (Error)\n"
	.byte	0	
	.align	2
	.word	-1
str_const21:
	.word	5
	.word	15
	.word	String_dispTab
	.word	int_const24
	.ascii	"  - 'void_object' is void, as expected.\n"
	.byte	0	
	.align	2
	.word	-1
str_const20:
	.word	5
	.word	16
	.word	String_dispTab
	.word	int_const25
	.ascii	"\n4. Testing 'isvoid' and 'not' operators...\n"
	.byte	0	
	.align	2
	.word	-1
str_const19:
	.word	5
	.word	12
	.word	String_dispTab
	.word	int_const26
	.ascii	"3. Testing Case expression...\n"
	.byte	0	
	.align	2
	.word	-1
str_const18:
	.word	5
	.word	12
	.word	String_dispTab
	.word	int_const27
	.ascii	"  - Factorial test FAILED.\n\n"
	.byte	0	
	.align	2
	.word	-1
str_const17:
	.word	5
	.word	12
	.word	String_dispTab
	.word	int_const27
	.ascii	"  - Factorial test PASSED.\n\n"
	.byte	0	
	.align	2
	.word	-1
str_const16:
	.word	5
	.word	10
	.word	String_dispTab
	.word	int_const14
	.ascii	"  - Factorial of 5 is: "
	.byte	0	
	.align	2
	.word	-1
str_const15:
	.word	5
	.word	17
	.word	String_dispTab
	.word	int_const28
	.ascii	"2. Testing While loop, If-Else, and Arithmetic...\n"
	.byte	0	
	.align	2
	.word	-1
str_const14:
	.word	5
	.word	5
	.word	String_dispTab
	.word	int_const11
	.ascii	"\n\n"
	.byte	0	
	.align	2
	.word	-1
str_const13:
	.word	5
	.word	13
	.word	String_dispTab
	.word	int_const15
	.ascii	"  - My static type (as Shape) is: "
	.byte	0	
	.align	2
	.word	-1
str_const12:
	.word	5
	.word	5
	.word	String_dispTab
	.word	int_const6
	.ascii	"\n"
	.byte	0	
	.align	2
	.word	-1
str_const11:
	.word	5
	.word	11
	.word	String_dispTab
	.word	int_const19
	.ascii	"  - My dynamic type is: "
	.byte	0	
	.align	2
	.word	-1
str_const10:
	.word	5
	.word	17
	.word	String_dispTab
	.word	int_const21
	.ascii	"1. Testing Class, Let, Dispatch, and Overriding...\n"
	.byte	0	
	.align	2
	.word	-1
str_const9:
	.word	5
	.word	16
	.word	String_dispTab
	.word	int_const29
	.ascii	"--- COOL Comprehensive Syntax Test Start ---\n\n"
	.byte	0	
	.align	2
	.word	-1
str_const8:
	.word	5
	.word	8
	.word	String_dispTab
	.word	int_const30
	.ascii	"A Circle Object"
	.byte	0	
	.align	2
	.word	-1
str_const7:
	.word	5
	.word	6
	.word	String_dispTab
	.word	int_const8
	.ascii	"Circle"
	.byte	0	
	.align	2
	.word	-1
str_const6:
	.word	5
	.word	5
	.word	String_dispTab
	.word	int_const11
	.ascii	")\n"
	.byte	0	
	.align	2
	.word	-1
str_const5:
	.word	5
	.word	5
	.word	String_dispTab
	.word	int_const11
	.ascii	", "
	.byte	0	
	.align	2
	.word	-1
str_const4:
	.word	5
	.word	6
	.word	String_dispTab
	.word	int_const5
	.ascii	" at ("
	.byte	0	
	.align	2
	.word	-1
str_const3:
	.word	5
	.word	5
	.word	String_dispTab
	.word	int_const6
	.ascii	">"
	.byte	0	
	.align	2
	.word	-1
str_const2:
	.word	5
	.word	6
	.word	String_dispTab
	.word	int_const8
	.ascii	"Shape<"
	.byte	0	
	.align	2
	.word	-1
str_const1:
	.word	5
	.word	8
	.word	String_dispTab
	.word	int_const12
	.ascii	"Generic Shape"
	.byte	0	
	.align	2
	.word	-1
str_const0:
	.word	5
	.word	8
	.word	String_dispTab
	.word	int_const31
	.ascii	"./complex.cl"
	.byte	0	
	.align	2
	.word	-1
int_const31:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	12
	.word	-1
int_const30:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	15
	.word	-1
int_const29:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	46
	.word	-1
int_const28:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	50
	.word	-1
int_const27:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	28
	.word	-1
int_const26:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	30
	.word	-1
int_const25:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	44
	.word	-1
int_const24:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	40
	.word	-1
int_const23:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	38
	.word	-1
int_const22:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	29
	.word	-1
int_const21:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	51
	.word	-1
int_const20:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	39
	.word	-1
int_const19:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	24
	.word	-1
int_const18:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	18
	.word	-1
int_const17:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	32
	.word	-1
int_const16:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	16
	.word	-1
int_const15:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	34
	.word	-1
int_const14:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	23
	.word	-1
int_const13:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	33
	.word	-1
int_const12:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	13
	.word	-1
int_const11:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	2
	.word	-1
int_const10:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	3
	.word	-1
int_const9:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	4
	.word	-1
int_const8:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	6
	.word	-1
int_const7:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	120
	.word	-1
int_const6:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	1
	.word	-1
int_const5:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	5
	.word	-1
int_const4:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	20
	.word	-1
int_const3:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	10
	.word	-1
int_const2:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	100
	.word	-1
int_const1:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	314
	.word	-1
int_const0:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	0
	.word	-1
bool_const0:
	.word	4
	.word	4
	.word	Bool_dispTab
	.word	0
	.word	-1
bool_const1:
	.word	4
	.word	4
	.word	Bool_dispTab
	.word	1
class_nameTab:
	.word	str_const36
	.word	str_const37
	.word	str_const38
	.word	str_const39
	.word	str_const40
	.word	str_const41
	.word	str_const42
	.word	str_const7
class_objTab:
	.word	Object_protObj
	.word	Object_init
	.word	IO_protObj
	.word	IO_init
	.word	Main_protObj
	.word	Main_init
	.word	Int_protObj
	.word	Int_init
	.word	Bool_protObj
	.word	Bool_init
	.word	String_protObj
	.word	String_init
	.word	Shape_protObj
	.word	Shape_init
	.word	Circle_protObj
	.word	Circle_init
Object_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
Shape_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	Shape.init
	.word	Shape.get_type_name
	.word	Shape.print_info
Circle_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	Shape.init
	.word	Circle.get_type_name
	.word	Shape.print_info
	.word	Circle.area
	.word	Circle.init_circle
String_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	String.length
	.word	String.concat
	.word	String.substr
Bool_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
Int_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
IO_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
Main_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	Main.main
	.word	Main.test_object_type
	.word	-1
Object_protObj:
	.word	0
	.word	3
	.word	Object_dispTab
	.word	-1
Shape_protObj:
	.word	6
	.word	6
	.word	Shape_dispTab
	.word	int_const0
	.word	int_const0
	.word	str_const43
	.word	-1
Circle_protObj:
	.word	7
	.word	7
	.word	Circle_dispTab
	.word	int_const0
	.word	int_const0
	.word	str_const43
	.word	int_const0
	.word	-1
String_protObj:
	.word	5
	.word	5
	.word	String_dispTab
	.word	int_const0
	.word	0
	.word	-1
Bool_protObj:
	.word	4
	.word	4
	.word	Bool_dispTab
	.word	0
	.word	-1
Int_protObj:
	.word	3
	.word	4
	.word	Int_dispTab
	.word	0
	.word	-1
IO_protObj:
	.word	1
	.word	3
	.word	IO_dispTab
	.word	-1
Main_protObj:
	.word	2
	.word	4
	.word	Main_dispTab
	.word	0
	.globl	heap_start
heap_start:
	.word	0
	.text
	.globl	Main_init
	.globl	Int_init
	.globl	String_init
	.globl	Bool_init
	.globl	Main.main
Object_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Shape_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	la	$a0 int_const0
	sw	$a0 12($s0)
	la	$a0 int_const0
	sw	$a0 16($s0)
	la	$a0 str_const1
	sw	$a0 20($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Circle_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Shape_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
String_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Bool_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Int_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
IO_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Main_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	jal	IO_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Shape.init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 20($fp)
	sw	$a0 12($s0)
	lw	$a0 16($fp)
	sw	$a0 16($s0)
	lw	$a0 12($fp)
	sw	$a0 20($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 24
	jr	$ra	
Shape.get_type_name:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 20($s0)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Shape.print_info:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	la	$a0 str_const3
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 20($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const2
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($fp)
	bne	$a0 $zero label0
	la	$a0 str_const0
	li	$t1 34
	jal	_dispatch_abort
label0:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	bne	$a0 $zero label1
	la	$a0 str_const0
	li	$t1 34
	jal	_dispatch_abort
label1:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	bne	$a0 $zero label2
	la	$a0 str_const0
	li	$t1 34
	jal	_dispatch_abort
label2:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	la	$a0 str_const6
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 16($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const5
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const4
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 12($fp)
	bne	$a0 $zero label3
	la	$a0 str_const0
	li	$t1 35
	jal	_dispatch_abort
label3:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	bne	$a0 $zero label4
	la	$a0 str_const0
	li	$t1 35
	jal	_dispatch_abort
label4:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	bne	$a0 $zero label5
	la	$a0 str_const0
	li	$t1 35
	jal	_dispatch_abort
label5:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	bne	$a0 $zero label6
	la	$a0 str_const0
	li	$t1 35
	jal	_dispatch_abort
label6:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	bne	$a0 $zero label7
	la	$a0 str_const0
	li	$t1 35
	jal	_dispatch_abort
label7:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 16
	jr	$ra	
Circle.get_type_name:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	la	$a0 str_const7
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Circle.area:
	addiu	$sp $sp -20
	sw	$fp 20($sp)
	sw	$s0 16($sp)
	sw	$ra 12($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	sw	$s1 4($fp)
	sw	$s2 0($fp)
	la	$s2 int_const1
	move	$s1 $s2
	lw	$a0 24($s0)
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s1)
	mul	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s1 $a0
	lw	$a0 24($s0)
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s1)
	mul	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s1 $a0
	la	$a0 int_const2
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s1)
	div	$t1 $t1 $t2
	sw	$t1 12($a0)
	lw	$s1 4($fp)
	lw	$s2 0($fp)
	lw	$fp 20($sp)
	lw	$s0 16($sp)
	lw	$ra 12($sp)
	addiu	$sp $sp 20
	jr	$ra	
Circle.init_circle:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	lw	$a0 20($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 16($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const8
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label8
	la	$a0 str_const0
	li	$t1 59
	jal	_dispatch_abort
label8:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$a0 12($fp)
	sw	$a0 24($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 24
	jr	$ra	
Main.main:
	addiu	$sp $sp -24
	sw	$fp 24($sp)
	sw	$s0 20($sp)
	sw	$ra 16($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	sw	$s1 8($fp)
	sw	$s2 4($fp)
	sw	$s3 0($fp)
	la	$a0 str_const9
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label9
	la	$a0 str_const0
	li	$t1 74
	jal	_dispatch_abort
label9:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	la	$a0 str_const10
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label10
	la	$a0 str_const0
	li	$t1 77
	jal	_dispatch_abort
label10:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	la	$a0 int_const3
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const4
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const5
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 Circle_protObj
	jal	Object.copy
	jal	Circle_init
	bne	$a0 $zero label11
	la	$a0 str_const0
	li	$t1 78
	jal	_dispatch_abort
label11:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	move	$s3 $a0
	move	$a0 $s0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s3
	bne	$a0 $zero label12
	la	$a0 str_const0
	li	$t1 79
	jal	_dispatch_abort
label12:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr		$t1
	la	$a0 str_const12
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s3
	bne	$a0 $zero label13
	la	$a0 str_const0
	li	$t1 80
	jal	_dispatch_abort
label13:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const11
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label14
	la	$a0 str_const0
	li	$t1 80
	jal	_dispatch_abort
label14:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	bne	$a0 $zero label15
	la	$a0 str_const0
	li	$t1 80
	jal	_dispatch_abort
label15:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	bne	$a0 $zero label16
	la	$a0 str_const0
	li	$t1 80
	jal	_dispatch_abort
label16:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	la	$a0 str_const14
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s3
	bne	$a0 $zero label17
	la	$a0 str_const0
	li	$t1 83
	jal	_dispatch_abort
label17:
	la	$t1 Shape_dispTab
	lw	$t1 16($t1)
	jalr		$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const13
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label18
	la	$a0 str_const0
	li	$t1 83
	jal	_dispatch_abort
label18:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	bne	$a0 $zero label19
	la	$a0 str_const0
	li	$t1 83
	jal	_dispatch_abort
label19:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	bne	$a0 $zero label20
	la	$a0 str_const0
	li	$t1 83
	jal	_dispatch_abort
label20:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	la	$a0 str_const15
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label21
	la	$a0 str_const0
	li	$t1 87
	jal	_dispatch_abort
label21:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	la	$s3 int_const5
	la	$s2 int_const6
label22:
	la	$s1 int_const0
	lw	$t1 12($s1)
	lw	$t2 12($s3)
	la	$a0 bool_const1
	blt	$t1 $t2 label24
	la	$a0 bool_const0
label24:
	lw	$t1 12($a0)
	beq	$t1 $zero label23
	move	$s1 $s2
	move	$a0 $s3
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s1)
	mul	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s2 $a0
	move	$s1 $s3
	la	$a0 int_const6
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s1)
	sub	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s3 $a0
	b	label22
label23:
	move	$a0 $zero
	la	$a0 str_const12
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	sw	$s2 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const16
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label25
	la	$a0 str_const0
	li	$t1 93
	jal	_dispatch_abort
label25:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	bne	$a0 $zero label26
	la	$a0 str_const0
	li	$t1 93
	jal	_dispatch_abort
label26:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	bne	$a0 $zero label27
	la	$a0 str_const0
	li	$t1 93
	jal	_dispatch_abort
label27:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	move	$s1 $s2
	la	$t2 int_const7
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label30
	la	$a1 bool_const0
	jal	equality_test
label30:
	lw	$t1 12($a0)
	beqz	$t1 label28
	la	$a0 str_const17
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label31
	la	$a0 str_const0
	li	$t1 96
	jal	_dispatch_abort
label31:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	b	label29
label28:
	la	$a0 str_const18
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label32
	la	$a0 str_const0
	li	$t1 98
	jal	_dispatch_abort
label32:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
label29:
	la	$a0 str_const19
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label33
	la	$a0 str_const0
	li	$t1 103
	jal	_dispatch_abort
label33:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	la	$a0 Shape_protObj
	jal	Object.copy
	jal	Shape_init
	move	$s3 $a0
	la	$a0 Circle_protObj
	jal	Object.copy
	jal	Circle_init
	move	$s2 $a0
	move	$s1 $s0
	sw	$s3 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label34
	la	$a0 str_const0
	li	$t1 108
	jal	_dispatch_abort
label34:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	sw	$s2 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label35
	la	$a0 str_const0
	li	$t1 109
	jal	_dispatch_abort
label35:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	sw	$s1 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label36
	la	$a0 str_const0
	li	$t1 110
	jal	_dispatch_abort
label36:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	la	$a0 str_const20
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label37
	la	$a0 str_const0
	li	$t1 114
	jal	_dispatch_abort
label37:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$a0 12($s0)
	move	$t1 $a0
	la	$a0 bool_const1
	beqz	$t1 label40
	la	$a0 bool_const0
label40:
	lw	$t1 12($a0)
	beqz	$t1 label38
	la	$a0 str_const21
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label41
	la	$a0 str_const0
	li	$t1 116
	jal	_dispatch_abort
label41:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	b	label39
label38:
	la	$a0 str_const22
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label42
	la	$a0 str_const0
	li	$t1 118
	jal	_dispatch_abort
label42:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
label39:
	move	$a0 $s0
	move	$t1 $a0
	la	$a0 bool_const1
	beqz	$t1 label46
	la	$a0 bool_const0
label46:
	lw	$t1 12($a0)
	la	$a0 bool_const1
	beqz	$t1 label45
	la	$a0 bool_const0
label45:
	lw	$t1 12($a0)
	beqz	$t1 label43
	la	$a0 str_const23
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label47
	la	$a0 str_const0
	li	$t1 122
	jal	_dispatch_abort
label47:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	b	label44
label43:
	la	$a0 str_const24
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label48
	la	$a0 str_const0
	li	$t1 124
	jal	_dispatch_abort
label48:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
label44:
	la	$a0 str_const25
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label49
	la	$a0 str_const0
	li	$t1 128
	jal	_dispatch_abort
label49:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	la	$a0 str_const26
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label50
	la	$a0 str_const0
	li	$t1 130
	jal	_dispatch_abort
label50:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	la	$a0 int_const2
	move	$s3 $a0
	la	$a0 str_const12
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	sw	$s3 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const27
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label51
	la	$a0 str_const0
	li	$t1 133
	jal	_dispatch_abort
label51:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	bne	$a0 $zero label52
	la	$a0 str_const0
	li	$t1 133
	jal	_dispatch_abort
label52:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	bne	$a0 $zero label53
	la	$a0 str_const0
	li	$t1 133
	jal	_dispatch_abort
label53:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	la	$a0 str_const12
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const3
	jal	Object.copy
	lw	$t1 12($a0)
	neg	$t1 $t1
	sw	$t1 12($a0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const28
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label54
	la	$a0 str_const0
	li	$t1 134
	jal	_dispatch_abort
label54:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	bne	$a0 $zero label55
	la	$a0 str_const0
	li	$t1 134
	jal	_dispatch_abort
label55:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	bne	$a0 $zero label56
	la	$a0 str_const0
	li	$t1 134
	jal	_dispatch_abort
label56:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	la	$a0 str_const29
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label57
	la	$a0 str_const0
	li	$t1 137
	jal	_dispatch_abort
label57:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$s1 8($fp)
	lw	$s2 4($fp)
	lw	$s3 0($fp)
	lw	$fp 24($sp)
	lw	$s0 20($sp)
	lw	$ra 16($sp)
	addiu	$sp $sp 24
	jr	$ra	
Main.test_object_type:
	addiu	$sp $sp -16
	sw	$fp 16($sp)
	sw	$s0 12($sp)
	sw	$ra 8($sp)
	addiu	$fp $sp 4
	move	$s0 $a0
	sw	$s1 0($fp)
	la	$a0 str_const30
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label58
	la	$a0 str_const0
	li	$t1 144
	jal	_dispatch_abort
label58:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$a0 16($fp)
	bne	$a0 $zero label60
	la	$a0 str_const0
	li	$t1 145
	jal	_case_abort2
label60:
	lw	$t2 0($a0)
	blt	$t2 7 label61
	bgt	$t2 7 label61
	move	$s1 $a0
	la	$a0 str_const31
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label62
	la	$a0 str_const0
	li	$t1 146
	jal	_dispatch_abort
label62:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	b	label59
label61:
	blt	$t2 6 label63
	bgt	$t2 7 label63
	move	$s1 $a0
	la	$a0 str_const32
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label64
	la	$a0 str_const0
	li	$t1 147
	jal	_dispatch_abort
label64:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	b	label59
label63:
	blt	$t2 2 label65
	bgt	$t2 2 label65
	move	$s1 $a0
	la	$a0 str_const33
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label66
	la	$a0 str_const0
	li	$t1 148
	jal	_dispatch_abort
label66:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	b	label59
label65:
	blt	$t2 0 label67
	bgt	$t2 7 label67
	move	$s1 $a0
	la	$a0 str_const34
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label68
	la	$a0 str_const0
	li	$t1 149
	jal	_dispatch_abort
label68:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	b	label59
label67:
	jal	_case_abort
label59:
	lw	$s1 0($fp)
	lw	$fp 16($sp)
	lw	$s0 12($sp)
	lw	$ra 8($sp)
	addiu	$sp $sp 20
	jr	$ra	
