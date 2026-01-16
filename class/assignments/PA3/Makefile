
#现在假装执行make parser
ASSN = 3
CLASS= cs143
CLASSDIR= ../..
LIB=  -lfl 
AR= gar
ARCHIVE_NEW= -cr
RANLIB= gar -qs

SRC= cool.y cool-tree.handcode.h good.cl bad.cl README
#5.需要变量parser-phase.cc等文件，本地目录保存有
CSRC= parser-phase.cc utilities.cc stringtab.cc dumptype.cc \
      tree.cc cool-tree.cc tokens-lex.cc  handle_flags.cc 
TSRC= myparser mycoolc cool-tree.aps
#6.需要变量cool-parse.cc文件
CGEN= cool-parse.cc
HGEN= cool-parse.h
LIBS= lexer semant cgen
#3.需要变量C Source和C Generate（最终变量替换结果是CFIL = parser-phase.cc utilities.cc stringtab.cc dumptype.cc tree.cc cool-tree.cc tokens-lex.cc handle_flags.cc cool-parse.cc）
CFIL= ${CSRC} ${CGEN}
HFIL= cool-tree.h cool-tree.handcode.h 
LSRC= Makefile
#2.发现需要变量CFIL，并且把变量中的.cc换成.o
OBJS= ${CFIL:.cc=.o}	
OUTPUT= good.output bad.output


CPPINCLUDE= -I. -I${CLASSDIR}/include/PA${ASSN} -I${CLASSDIR}/src/PA${ASSN}

BFLAGS = -d -v -y -b cool --debug -p cool_yy

CC=g++
CFLAGS=-g -Wall -Wno-unused -Wno-deprecated  -Wno-write-strings -DDEBUG ${CPPINCLUDE}
FLEX=flex ${FFLAGS}
BISON= bison ${BFLAGS}
DEPEND = ${CC} -MM ${CPPINCLUDE}

source: ${SRC} ${TSRC} ${LIBS} lsource

lsource: ${LSRC}

${OUTPUT}:	parser good.cl bad.cl	#这个是规则，表明目标：good.output和bad.output需要parser、goot.cl、bad.cl
	@rm -f ${OUTPUT}	#@表示命令执行前不输出命令
	./myparser good.cl >good.output 2>&1 
	-./myparser bad.cl >bad.output 2>&1 	#最前面的 - 表示出错仍继续执行
	
#决定是否执行：
#如果 parser 文件不存在，或者任何一个 .o 文件的修改时间比 parser 文件新，那么 Make 就认为 parser 文件是“过时”的。这时，它才会执行一次下面的链接命令，重新生成 parser。
#如果 parser 文件存在，并且所有 .o 文件的修改时间都比 parser 文件旧，那么 Make 就认为 parser 文件是“最新的”。这时，它就会什么都不做，直接告诉你 make: 'parser' is up to date.。
#1.找到parser的这一行，然后发现需要变量${OBJS}的内容
parser: ${OBJS}  
	${CC} ${CFLAGS} ${OBJS} ${LIB} -o parser
#最终展开的内容：parser: parser-phase.o utilities.o stringtab.o dumptype.o tree.o cool-tree.o tokens-lex.o handle_flags.o cool-parse.o
#	g++ -g -Wall ... -I. -I../../include/PA3 -I../../src/PA3 parser-phase.o utilities.o ... cool-parse.o -lfl -o parser


.cc.o:
	${CC} ${CFLAGS} -c $<
#7.构件cool-parse首先需要cool.y，然后使用bison进行编译处理（需要变量BFLAG），最后重命名文件
cool-parse.cc cool-parse.h: cool.y
	bison ${BFLAGS} cool.y
	mv -f cool.tab.c cool-parse.cc

dotest:	parser good.cl bad.cl
	@echo "\nRunning parser on good.cl\n"
	-./myparser good.cl 
	@echo "\nRunning parser on bad.cl\n"
	-./myparser bad.cl

${LIBS}:
	${CLASSDIR}/etc/link-object ${ASSN} $@

${TSRC} ${CSRC}:
	-ln -s ${CLASSDIR}/src/PA${ASSN}/$@ $@

${HSRC}:
	-ln -s ${CLASSDIR}/include/PA${ASSN}/$@ $@

clean :
	-rm -f ${OUTPUT} *.s core ${OBJS} ${CGEN} ${HGEN} lexer parser cgen semant *~ *.a *.o 

clean-compile:
	@-rm -f core ${OBJS} ${CGEN} ${HGEN} ${LSRC}

%.d: %.cc ${LSRC}
	${SHELL} -ec '${DEPEND} $< | sed '\''s/\($*\.o\)[ :]*/\1 $@ : /g'\'' > $@'

-include ${CFIL:.cc=.d}
