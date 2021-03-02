# get_next_line
The goal of this project is to make you code a function that reads file from file descriptor and retruns *one line ending with a new line('/n')* without knowing the size beforehand. This project allows me to learn various interesting concepts in C programming such as memory allocation and management(heap/static memory), static variables, buffer management, file descriptor and unexpected errors when the size of file is not provided in advance.  

##Prototype 
int	get_next_line(int fd, char **line);

