

typedef struct process{
	int pid; 			 
	int burst;
    	int arrival;
	int priority; 	
	int deadline;
    	int io;
} Process;


void delimit(std::string line, int pvalues[] );