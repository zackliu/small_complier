typedef union
{
    char ident[10];
    int number;
} YYSTYPE;
#define	BEG	257
#define	END	258
#define	IF	259
#define	ELSE	260
#define	THEN	261
#define	WHILE	262
#define	DO	263
#define	REPEAT	264
#define	UNTIL	265
#define	READ	266
#define	WRITE	267
#define	FUNCTION	268
#define	ODD	269
#define	XOR	270
#define	BC	271
#define	GE	272
#define	LE	273
#define	GT	274
#define	LT	275
#define	EQ	276
#define	NE	277
#define	VAR	278
#define	CONST	279
#define	CALL	280
#define	RETURN	281
#define	IDENT	282
#define	NUMBER	283


extern YYSTYPE yylval;
