/* Opcode definitions */
#define MAXOPS		15
#define NOPCODES	15

// TODO - Argument type (register?)
// TODO - opfunc take Argument type

typedef void (*Opfunc)(int, int);

typedef struct Opcode Opcode;
typedef struct Opcode {
	char*	str;	// String representation of an op
	Opfunc	ofunc;	// Func to run  with opcode
	// TODO - arguments
};

/* CPU matrix */

typedef struct CPU CPU;
typedef struct CPU {
	// TODO - registers
	Opcode	instrs[MAXOPS];
};

#define HEIGHT	3
#define WIDTH	4

CPU	cpus[HEIGHT][WIDTH];

extern int maxouts, nouts, ninputs; 
