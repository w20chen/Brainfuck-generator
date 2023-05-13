#ifndef _while
#define _while

#define FLAG_(i) i##flag__
#define FLAG(i) FLAG_(i)


#define foreach(i, a, N)	\
	var i = a;				\
	var FLAG(i) = 1;		\
	FLAG(i).while_begin();	\


#define endfor(i, a, N)		\
	i.increment();			\
	(i >= N).if_begin();	\
		FLAG(i).flip();		\
	if_end();				\
	FLAG(i).while_end();


#endif