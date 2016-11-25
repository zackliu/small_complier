%{
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define idTableMax 100
#define idLenMax 10
#define globalStackMax 2048
#define stackMax 2048
#define codeMax 200

enum object
{
    variable,
    constant,
    function,
};

struct tablestruct
{
    char name[idLenMax];
    enum object kind;
    int level;
    int adr;
    int size;
};

struct tablestruct localtable[idTableMax], globaltable[idTableMax];

enum fct {
    lit,     opr,     lod, 
    sto,     cal,     ini, 
    jmp,     jpc,     
};

struct instruction
{
	enum fct f;   /* 虚拟机代码指令 */
	int l;        /* 引用层与声明层的层次差 */
	int a;        /* 根据f的不同而不同 */
};
struct instruction code[codeMax];

int localtablePoint;
int globaltablePoint;
int level;
int codePoint;
int listswitch;
int startPoint;
int globalStackPoint;
int localStackPoint;

int returnReg;
int paramReg[10];
int paramPoint;

FILE* fin;      /* 输入源文件 */
FILE* ftable;	  /* 输出符号表 */
FILE* fcode;    /* 输出虚拟机代码 */
FILE* foutput;  /* 输出出错示意（如有错） */
FILE* fresult;  /* 输出执行结果 */
char fname[10];
int err;
extern int line;

int yyerror(char *s);
void init();
struct tablestruct* enter(char *name, enum object kind, int size);
struct tablestruct* position(char *name);
void gen(enum fct x, int y, int z);
void listall();
void listtable();
int main(void);

%}

%union
{
    char ident[10];
    int number;
}

%token BEG, END, IF, ELSE, THEN, WHILE, DO, REPEAT, UNTIL, READ, WRITE ,FUNCTION ,ODD ,XOR
%token BC, GE, LE ,GT, LT ,EQ ,NE
%token VAR, CONST, CALL, RETURN
%token<ident> IDENT
%token<number> NUMBER

%type<number> get_code_addr

%left '%'
%left '+', '-'
%left '*', '/'
%left XOR
%left ODD


%%
program: 
       {
           gen(jmp, 0, 0);
       }
       block
       {
           if(startPoint == 0) yyerror("Cannot find main");
           code[0].a = codePoint;
           gen(cal, 0, startPoint);
           gen(jmp, 0, 0);
       }
       ;

block: block ';' init_stmt
     | block ';' function_stmt
     | init_stmt
     | function_stmt
     ;

init_sequence: init_list
             |
             ;

init_list: init_list ',' init_stmt
         | init_stmt
         ;

init_stmt: VAR identifier
         {
             struct tablestruct* pos = position($<ident>2);
             if(pos && pos -> level == level) yyerror("Redeclaration");
             pos = enter($<ident>2, variable, 1);

             if(level == 0)
             {
                 pos -> adr = globalStackPoint++;
             }
             else
             {
                 pos -> adr = localStackPoint++;
                 gen(ini, 0, 1);
             }

         }
         | CONST identifier BC NUMBER
         {
             struct tablestruct* pos = position($<ident>2);
             if(pos && pos -> level == level) yyerror("Redeclaration");
             pos = enter($<ident>2, constant, 1);
             pos -> adr = localStackPoint++;
             gen(ini, 0, 1);
         }
         ;

function_stmt: FUNCTION identifier 
             {
                 struct tablestruct* pos = position($<ident>2);
                 if(pos && pos -> level == level) yyerror("Redeclaration");
                 pos = enter($<ident>2, function, 0);
                 pos -> adr = codePoint;
                 if(strcmp("main", pos->name) == 0)
                 {
                     startPoint = codePoint;
                 }
                 gen(ini, 0, 2);
                 level++;
                 localStackPoint = 2;
             }
             '(' init_sequence ')' 
             {
                 struct tablestruct* pos = position($<ident>2);
                 pos -> size = localtablePoint;
                 
                 //listall();
                // listtable();
                 
             }
             BEG stmt_sequence END
             {
                 level--;
                 localtablePoint = 0;
                 gen(opr, 0, 0);
             }
             ;

stmt_sequence: stmt_sequence ';' statement
             | statement
             ;

statement:     if_stmt
             | repeat_stmt
             | assign_stmt
             | read_stmt
             | write_stmt
             | init_stmt
             | call_stmt
             | while_stmt
             | dowhile_stmt
             | return_stmt
             ;

if_stmt: if_stmt1 END
       {
           code[$<number>1].a = codePoint;
       }
       | if_stmt1 get_code_addr 
       {
           gen(jmp, 0, 0);
           code[$<number>1].a = codePoint;
       }
       ELSE stmt_sequence END
       {
           code[$<number>2].a = codePoint;
       }       
       ;

if_stmt1: IF exp get_code_addr
        {
            gen(jpc, 0, 0);
        }
        THEN stmt_sequence
        {
            $<number>$ = $<number>3;
        }
        ;

repeat_stmt: REPEAT get_code_addr stmt_sequence UNTIL exp
           {
               gen(jpc, 0, $<number>2);
           }
           ;

assign_stmt: identifier BC exp
           {
               struct tablestruct* pos = position($<ident>1);
               if(pos == NULL) yyerror("Undifined variable");
               if(pos && pos -> kind != variable) yyerror("Identifier with wrong kind");
               gen(sto, pos->level, pos->adr);
           }
           ;

read_stmt: READ identifier
         {
             struct tablestruct* pos = position($<ident>2);
             if(pos == NULL) yyerror("Undifined variable");
             if(pos && pos -> kind != variable) yyerror("Identifier with wrong kind");
             gen(opr, 0, 16);
             gen(sto, pos->level, pos->adr);
         }
         ;

write_stmt: WRITE exp
          {
              gen(opr, 0, 14);
          }
          ;

call_stmt: CALL identifier '(' param_sequence ')'
         {
             struct tablestruct* pos = position($<ident>2);
             if(pos == NULL || pos && pos -> kind != function) yyerror("Undifined function");
             if(pos -> size != $<number>4) yyerror("Param with wrong number");
             gen(cal, $<number>4, pos->adr);
         }
         ;

param_sequence: 
              {
                  paramPoint = 0;
              }
              param_list
              {
                  $<number>$ = $<number>2;
              }
              | 
              ;

param_list: param_list ',' param_stmt
          {
              $<number>$ = $<number>1 + 1;
          }
          | param_stmt
          {
              $<number>$ = 1;
          }
          ;

param_stmt: exp
          {
              gen(opr, paramPoint++, 19);
          }
          ;


while_stmt: WHILE get_code_addr exp get_code_addr
          {
              gen(jpc, 0, 0);
          }
          DO stmt_sequence END
          {
              gen(jmp, 0, $<number>2);
              code[$<number>4].a = codePoint;
          }
          ;

dowhile_stmt: DO get_code_addr stmt_sequence WHILE exp
            {
                gen(jpc, 0, codePoint+1);
                gen(jmp, 0, $<number>2);
            }
            ;

return_stmt: RETURN exp
           {
               gen(opr, 0, 17);
               gen(opr, 0, 0);
           }
           | RETURN
           {
               gen(opr, 0, 0);
           }
           ;

exp: simple_exp GT simple_exp
   {
       gen(opr, 0, 12);
   }
   | simple_exp LT simple_exp
   {
       gen(opr, 0, 10);
   }
   | simple_exp GE simple_exp
   {
       gen(opr, 0, 11);
   }
   | simple_exp LE simple_exp
   {
       gen(opr, 0, 13);
   }
   | simple_exp EQ simple_exp
   {
       gen(opr, 0, 8);
   }
   | simple_exp NE simple_exp
   {
       gen(opr, 0, 9);
   }
   | simple_exp
   ;

simple_exp: simple_exp '+' simple_exp
          {
              gen(opr, 0, 2);
          }
          | simple_exp '-' simple_exp
          {
              gen(opr, 0, 3);
          }
          | simple_exp '*' simple_exp
          {
              gen(opr, 0, 4);
          }
          | simple_exp '/' simple_exp
          {
              gen(opr, 0, 5);
          }
          | simple_exp '%' simple_exp
          {
              gen(opr, 0, 21);
          }
          | simple_exp XOR simple_exp
          {
              gen(opr, 0, 22);
          }
          | ODD simple_exp
          {
              gen(opr, 0, 23);
          }
          | NUMBER
          {
              gen(lit, 0, $<number>1);
          }
          | identifier
          {
              struct tablestruct* pos = position($<ident>1);
              if(pos == NULL || pos && pos -> kind == function) yyerror("Undifined variable");
              gen(lod, pos -> level, pos -> adr);
          }
          | '(' exp ')'
          | call_stmt
          {
              gen(opr, 0, 18);
          }
          ;

identifier: IDENT
          {
              strcpy($<ident>$, $<ident>1);
          }
          ;

get_code_addr:
              {
                $<number>$ = codePoint;
              } 
              ;

%%
int yyerror(char *s)
{
	err = err + 1;
    printf("%s in line %d\n", s, line);
	fprintf(foutput, "%s in line %d\n", s, line);
	return 0;
}

/* 初始化 */
void init()
{
	localtablePoint = 0;
    globaltablePoint = 0;
    level = 0;
    codePoint = 0;
    err = 0;
    startPoint = 0;
    globalStackPoint = 0;
    localStackPoint = 0;
    returnReg = 0;
    paramPoint = 0;
}

struct tablestruct* enter(char *name, enum object kind, int size)
{
    if(level == 0)
    {
        strcpy(globaltable[globaltablePoint].name, name);
        globaltable[globaltablePoint].kind = kind;
        globaltable[globaltablePoint].level = level;
        globaltable[globaltablePoint].size = size;
        globaltablePoint++;
        return &globaltable[globaltablePoint-1];
    }
    else
    {
        strcpy(localtable[localtablePoint].name, name);
        localtable[localtablePoint].kind = kind;
        localtable[localtablePoint].level = level;
        localtable[localtablePoint].size = size;
        localtablePoint++;
        return &localtable[localtablePoint-1];
    }
}

struct tablestruct* position(char *name)
{
    int i = 0;
	if(level != 0)
    {
        i = localtablePoint - 1;
        while(i >= 0)
        {
            if(strcmp(name, localtable[i].name) == 0) return &localtable[i];
            i--;
        }
    }
    i = globaltablePoint - 1;
    while(i >= 0)
    {
        if(strcmp(name, globaltable[i].name) == 0) return &globaltable[i];
        i--;
    }
    return NULL;
}

void gen(enum fct x, int y, int z)
{
	if (codePoint >= codeMax)
	{
		printf("Program is too long!\n");	/* 生成的虚拟机代码程序过长 */
		exit(1);
	}
	if ( z >= stackMax)
	{
		printf("Displacement address is too big!\n");	/* 地址偏移越界 */
		exit(1);
	}
	code[codePoint].f = x;
	code[codePoint].l = y;
	code[codePoint].a = z;
	codePoint++;
}

void listall()
{
	int i;
	char name[][5]=
	{
		{"lit"},{"opr"},{"lod"},{"sto"},{"cal"},{"int"},{"jmp"},{"jpc"},
	};
    if (listswitch)
	{
		for (i = 0; i < codePoint; i++)
		{
			printf("%d %s %d %d\n", i, name[code[i].f], code[i].l, code[i].a);
			fprintf(fcode,"%d %s %d %d\n", i, name[code[i].f], code[i].l, code[i].a);
			
		}
    }
}

void listtable()
{
    int i = 0;
    printf("-----------global table-----------\n");
    while(i < globaltablePoint)
    {
        printf("name = %s, level = %d, adr = %d, size = %d\n", globaltable[i].name, globaltable[i].level, globaltable[i].adr, globaltable[i].size);
        i++;
    }
    printf("-----------local table-----------\n");
    i  = 0;
    while(i < localtablePoint)
    {
        printf("name = %s, level = %d, adr = %d, size= %d\n", localtable[i].name, localtable[i].level, localtable[i].adr, localtable[i].size);
        i++;
    }

}

void interpret()
{
	int p = 0; /* 指令指针 */
	int b = 0; /* 指令基址 */
	int t = 0; /* 栈顶指针 */
	struct instruction i;	/* 存放当前指令 */
	int s[stackMax];	/* 栈 */
    int globals[globalStackMax];

	printf("Start small\n");
	fprintf(fresult,"Start small\n");
	s[0] = 0; /* s[0]不用 */
	do {
	    i = code[p];	/* 读当前指令 */
        // printf("------line %d----------\n", p);
		p = p + 1;
		switch (i.f)
		{
			case lit:	/* 将常量a的值取到栈顶 */
				t = t + 1;
				s[t] = i.a;				
				break;
			case opr:	/* 数学、逻辑运算 */
				switch (i.a)
				{
					case 0:  /* 函数调用结束后返回 */
						t = b - 1;
						p = s[t + 2];
						b = s[t + 1];
						break;
					case 1: /* 栈顶元素取反 */
						s[t] = - s[t];
						break;
					case 2: /* 次栈顶项加上栈顶项，退两个栈元素，相加值进栈 */
						t = t - 1;
						s[t] = s[t] + s[t + 1];
						break;
					case 3:/* 次栈顶项减去栈顶项 */
						t = t - 1;
						s[t] = s[t] - s[t + 1];
						break;
					case 4:/* 次栈顶项乘以栈顶项 */
						t = t - 1;
						s[t] = s[t] * s[t + 1];
						break;
					case 5:/* 次栈顶项除以栈顶项 */
						t = t - 1;
						s[t] = s[t] / s[t + 1];
						break;
					case 6:/* 栈顶元素的奇偶判断 */
						s[t] = s[t] % 2;
						break;
					case 8:/* 次栈顶项与栈顶项是否相等 */
						t = t - 1;
						s[t] = (s[t] == s[t + 1]);
						break;
					case 9:/* 次栈顶项与栈顶项是否不等 */
						t = t - 1;
						s[t] = (s[t] != s[t + 1]);
						break;
					case 10:/* 次栈顶项是否小于栈顶项 */
						t = t - 1;
						s[t] = (s[t] < s[t + 1]);
						break;
					case 11:/* 次栈顶项是否大于等于栈顶项 */
						t = t - 1;
						s[t] = (s[t] >= s[t + 1]);
						break;
					case 12:/* 次栈顶项是否大于栈顶项 */
						t = t - 1;
						s[t] = (s[t] > s[t + 1]);
						break;
					case 13: /* 次栈顶项是否小于等于栈顶项 */
						t = t - 1;
						s[t] = (s[t] <= s[t + 1]);
						break;
					case 14:/* 栈顶值输出 */
						printf("%d\n", s[t]);
						fprintf(fresult, "%d", s[t]);
						t = t - 1;
						break;
					case 15:/* 输出换行符 */
						printf("\n");
						fprintf(fresult,"\n");
						break;
					case 16:/* 读入一个输入置于栈顶 */
						t = t + 1;
						printf("?");
						fprintf(fresult, "?");
						scanf("%d", &(s[t]));
						fprintf(fresult, "%d\n", s[t]);						
						break;
                    case 17:
                        returnReg = s[t];
                        t--;
                        break;
                    case 18:
                        t++;
                        s[t] = returnReg;
                        break;
                    case 19:
                        paramReg[i.l] = s[t];
                        t--;
                        break;
                    case 21:
                        t = t - 1;
						s[t] = s[t] % s[t + 1];
                        break;
                    case 22:
                        t = t - 1;
						s[t] = s[t] ^ s[t + 1];
                        break;
                    case 23:
                        s[t] = s[t] % 2 == 1 ? 1 : 0;
						break;
				}
				break;
			case lod:	/* 取相对当前过程的数据基地址为a的内存的值到栈顶 */
				t = t + 1;
				s[t] = i.l == 0 ? globals[i.a] : s[b + i.a];
				break;
			case sto:	/* 栈顶的值存到相对当前过程的数据基地址为a的内存 */
                if(i.l == 0)
                {
                    globals[i.a] = s[t];
                }
                else
                {
                    s[b + i.a] = s[t];
                }
				t = t - 1;
				break;
			case cal:	/* 调用子过程 */
				s[t + 1] = b;	/* 将本过程基地址入栈，即建立动态链 */
				s[t + 2] = p;	/* 将当前指令指针入栈，即保存返回地址 */
				b = t + 1;	/* 改变基地址指针值为新过程的基地址 */
				p = i.a;	/* 跳转 */
                int count = 0;
                for(; count < i.l; count++)
                {
                    s[t+3+count] = paramReg[count];
                }
				break;
			case ini:	/* 在数据栈中为被调用的过程开辟a个单元的数据区 */
				t = t + i.a;	
				break;
			case jmp:	/* 直接跳转 */
				p = i.a;
				break;
			case jpc:	/* 条件跳转 */
				if (s[t] == 0) 
					p = i.a;
				t = t - 1;
				break;
		}
        
        // int count = 0;
        // for(; count <= t; count++)
        // {
        //     printf("%d %d\n", count, s[count]);
        // }
	} while (p != 0);
	printf("End small\n");
	fprintf(fresult,"End small\n");
}


int main(void)
{
	printf("Input pl/0 file?   ");
	scanf("%s", fname);		/* 输入文件名 */

	if ((fin = fopen(fname, "r")) == NULL)
	{
		printf("Can't open the input file!\n");
		exit(1);
	}	
	if ((foutput = fopen("foutput.txt", "w")) == NULL)
  {
		printf("Can't open the output file!\n");
		exit(1);
	}
	if ((ftable = fopen("ftable.txt", "w")) == NULL)
	{
		printf("Can't open ftable.txt file!\n");
		exit(1);
	}
	
	printf("List object codes?(Y/N)");	/* 是否输出虚拟机代码 */
	scanf("%s", fname);
	listswitch = (fname[0]=='y' || fname[0]=='Y');
	
	redirectInput(fin);		
	init();
    yyparse();
	if(err == 0)
	{
		printf("\n===Parsing success!===\n");
		fprintf(foutput, "\n===Parsing success!===\n");
		if ((fcode = fopen("fcode.txt", "w")) == NULL)
		{
			printf("Can't open fcode.txt file!\n");
			exit(1);
		}		

		if ((fresult = fopen("fresult.txt", "w")) == NULL)
		{
			printf("Can't open fresult.txt file!\n");
			exit(1);
		}
		
		listall();  /* 输出所有代码 */
		fclose(fcode);
		
		interpret();	/* 调用解释执行程序 */        	
		fclose(fresult);
	}
  else
	{
		printf("%d errors in PL/0 program\n", err);
		fprintf(foutput, "%d errors in PL/0 program\n", err);
		
	}
	
	fclose(ftable);
    fclose(foutput);
	fclose(fin);
	return 0;
}