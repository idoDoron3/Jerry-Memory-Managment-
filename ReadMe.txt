the project divide to 4 files - 
Defs.h contain the enum bool and status
Jerry.h - define all the structs and declaration of the functions in Jerry.c
Jerry.c - create all the objects, and the functions from the h file
ManageJerries - contain all the main of the project.
first its read and store all the information from the configuration file 
after that its manage all rick requests by the menu.
if there is any memory problem by reading the configuration file or adding caracters it will return null end clean all the store information, and eventually exit the program.
