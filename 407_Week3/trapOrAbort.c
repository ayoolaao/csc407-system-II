//Can't the compiler or linker tell beforehand whether 
//an instruction will be a trap or abort and do something 
//about it at compile or link time?

int i;

int int main()
{
	printf("Please enter an index: ");
	fgets(array, LENGTH, stdin);

	i = strtol(array, NULL, 10); //CAN'T
	//This is legal or illegal, depended on i 

	return(EXIT_SUCCESS);
}