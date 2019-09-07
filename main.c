#include <u.h>
#include <libc.h>
#include <bio.h>

#include "tis100.h"

int maxouts, nouts, ninputs;

void
usage(void)
{
	fprint(2, "usage: %s file.asm inputs0 inputs1 ...\n", argv0);
	exits("usage");
}


// Emulate the imaginary TIS-100 system
void
main(int argc, char *argv[])
{
	char *str;
	Biobuf *f, *in, *out;
	char *fname;
	maxouts = WIDTH * 2 + ((HEIGHT - 2) * 2);

	ARGBEGIN {
	default:
		usage();
	} ARGEND
	
	// Need 1 asm and 1 input minimum
	if(argc < 2)
		sysfatal("err: not enough arguments, need 1 asm 1 input min");
		
	// Get asm
	fname = argv[0];
	
	// Get inputs
	for(ninputs = 1; ninputs < argc; ninputs++){
		if(ninputs > maxouts / 2)
			sysfatal("Too many inputs, expected %d", maxouts / 2);
	}

	in = Bfdopen(0, OREAD);
	out = Bfdopen(1, OWRITE);

	f = Bopen(fname, OREAD);
	if(f == nil)
		sysfatal("err: could not open input asm file - %r");
	
	// Read input asm
	while((str = Brdstr(f, '\n', 1)) != 0){
		// Tokenize
		int n;
		char **ctoks; 
		ctoks = calloc(3, sizeof(char*));
		
		n = getfields(str, ctoks, 3, 1, "\t\r\n ");
		
		if(n < 1){
			free(ctoks);
			continue;
		}
		
		// Skip comments -- TODO might not be safe, need length check?
		if(ctoks[0][0] == '#'){
			free(ctoks);
			continue;
		}
		
		// Convert tokens to utf-8
		// Rune *s = runesmprint("%s", str);
		Rune **toks;
		int i, j;
		
		toks = calloc(3, sizeof(Rune*));
		
		n = 0;
		for(i = 0; i < 3; i++){
			if(ctoks[i] != nil){
				if(ctoks[i][0] == L'#')
					break;

				toks[i] = runesmprint("%s", ctoks[i]);
				n++;
			}
		}
		
		// Clean up char allocs
		free(str);
		free(ctoks);

		// Downcase	
		// Rune tolowerrune(Rune c)
		for(i = 0; i < n; i++)
			for(j = 0; j < runestrlen(toks[i]); j++)
				toks[i][j] = tolowerrune(toks[i][j]);
				
		// Debug print tokens
		print("Tokens (%d):	", n);
		for(i = 0; i < n; i++)
			print("%S	", toks[i]);
		print("\n");
		
		// Ingest @N block (if found)
		
		// Build list of tokens for each node
		
		// Runesmprint allocates the buffer
		for(i = 0; i < 3; i++)
			if(toks[i] != nil)
				free(toks[i]);

		free(toks);
	}
	
	// For each node turn list of tokens into cyclic list of func ptr && args
	// doop(funcptr, args[2])
	
	// Start the clock
	
	// Iterate for as many cycles as we have ingested inputs present for
	// TODO - big
	
	// Tear down
	Bterm(f);
	Bterm(in);
	Bterm(out);
	exits(nil);
}
