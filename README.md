# ShellProgram
C program that serves as a shell (i.e. command-based interface) for Linux. The shell accepts user commands and executes each command using a separate process. In addition, the shell provides a history  feature that allows users  to access the recently-entered  commands

Two	 techniques	implemented  for	 retrieving	 and	 executing	 the	
commands	from	the	command	history:
a. When	the	user	enters	!!,	the	most	recent	command	in	the	history	is	executed	
(e.g.	in	the	above	case,	!!	will	execute	ps -ael).

b. When	the	user	enters	a	single ! followed	by	an	integer	N,	the	Nth command	in	
the	history	is	executed	(e.g.	in	the	above	case,	!3	should	execute	top)	.

Note	that:
a. The real	command	(not	the	symbol	“!!”	or	“!N”)	executed	in	this	fashion	is	
displayed	on	the	user’s	screen	so	that	the	user	knows	which	command	is	
executed.	

b. In	addition,	the	real command (not	the	symbol	“!!”	or	“!N”) is placed	in	
the	history	as	the	most	recent	command.	
c. Assuming	that	N	is	in	the	range	of	1	to	10.

b) The	program	also	manages	basic	error	handling.	

a. If	there	are	no	commands	in	the	history,	entering	!! or	!N	or	 history should	
result	in	a	message	“No command in history!” on	the	screen. In	this	case,	
!! or	!N	or		history is NOT added	to	the	history.

b. If	there	are	commands	in	the	history,	but	there	is	no	command	corresponding	
to	the	user	input	“!N”,	the	program outputs	”Such a command is 
NOT in history!".	In	this	case,	“!N”	is	NOT added	to	the	history.
c. Any	 other	 invalid	 command	 results	 in a	 message	 “Invalid 
command!”	on	the	screen.	

In	this	case,	the	invalid	command	is	added	to	the	
command	history
