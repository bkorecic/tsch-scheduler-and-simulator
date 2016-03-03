Pedro Henrique Gomes
EE652

Readme file
-----------

How to compile: gcc -std=gnu99 -o Scheduling util/*.c graphs/*.c mcc/*.c tasa/*.c main.c

How to execute: ./Scheduling <sink_id> <algorithm>
where: 	sink_id = Sink identification (starting at 0)
	algorithm = 0 if MCC and 1 if TASA

Output: you will find files ext_schedule.h and topology.c, which should be used according to the project report

The execution will consider data/prr55.txt file as input for PRR statistics. You need to create the file with tree description before running TASA. You can easily do that first running MCC for a given sink id (e.g. 3) and then running TASA for the same sink id.
