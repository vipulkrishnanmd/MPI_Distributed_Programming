# MPI_Distributed_Programming

Distributed	Event	Modelling with	MPI

Your	naval	fleet	patrols	an	area	comprising	1000 distinct locations.	Each	vessel	can	
occupy	any	one	of	these	locations	randomly at	the	end	of	sampling	interval.	For	a	
vessel	to	be	able	to	launch	a	strike,	other	vessels	must	accompany	it.	The	rules	for	
launching	a	strike	are	summarised	as	follows:
1. At	least	one	odd	numbered	and	two	even	numbered vessels share	the	same	
location,	at	a	given	point	in	time,	for	a	strike	to	be	counted. MPI	rank	1 to	n may	be	
used	to	number	each	vessel	in	the	fleet
2. The	fleet	may	generate	more	than	one	strike	at	an	instant	of	time	(it	will	however	
depend	on	the	number	of	locations	meeting	the	strike	criterion,	item	1	above, at	that	
instant	of	time).
3. There	is	no	limit	on	the	number	of	vessels	in	the	fleet.	The	objective	is	to	achieve	the	
highest	possible	strike	rate.		It	may	however	be	pointed	out	that	increases	in	fleet	
size	will	increase	the	probability	of	satisfying	Rule	no.	1	(above),	but	doing	so	will	
also	slow	the	program	owing	to	higher	inter-process	communication	overheads.

Assume	that	a	set	of	MPI	processes	represents	the	fleet	and	each	MPI	process	represents	
a	naval	vessel.
