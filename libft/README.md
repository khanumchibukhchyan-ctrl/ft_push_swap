# Libft
*This project has been created as part of the 42 curriculum by kchibukh.*

---

## Description 

Libft is a personal C library that reimplements a set of standard libc functions, additional useful functions, and linked list operations.  
It helps understand how standard C functions work under the hood and allows you to use your own library in future assignments.


## Project Goal 

- Reimplement libc functions with the `ft_` prefix.  
- Create useful string, memory, and linked list manipulation functions.  
- Understand memory allocation, pointers, and linked list operations.  


## Instructions 

### Compilation

The library is compiled using the provided Makefile and the `cc` compiler
with the following flags:

-Wall -Wextra -Werror

To compile the library, run:

make

This will generate the static library file `libft.a` at the root of the repository.

### Makefile rules

- make / make all  
- make clean  
- make fclean  
- make re  


## Tasks Completed

---

Part 1 – Libc Functions 

 ft_isalpha — check if character is a letter 

 ft_isdigit — check if character is a digit 

 ft_isalnum — check if character is alphanumeric 

 ft_isascii — check if character is ASCII 

 ft_isprint — check if character is printable 

 ft_strlen — get length of string 

 ft_memset — fill memory with a byte 

 ft_bzero — zero out memory 

 ft_memcpy — copy memory 

 ft_memmove — safely copy memory 

 ft_strlcpy — copy string with size limit 

 ft_strlcat — concatenate strings with size limit 

 ft_toupper — convert char to uppercase 

 ft_tolower — convert char to lowercase 

 ft_strchr — find character in string 

 ft_strrchr — find last occurrence of character 

 ft_strncmp — compare strings up to n characters 

 ft_memchr — locate byte in memory 

 ft_memcmp — compare memory blocks 

 ft_strnstr — locate substring with length limit 

 ft_atoi — convert string to integer 

 ft_calloc — allocate and zero memory 

 ft_strdup — duplicate string 

---

Part 2 – Additional Functions 

 ft_substr — create substring 

 ft_strjoin — join two strings 

 ft_strtrim — trim characters from string 

 ft_split — split string by delimiter 

 ft_itoa — convert integer to string 

 ft_strmapi — apply function to each char, return new string 

 ft_striteri — apply function to each char in place 

 ft_putchar_fd — output character to file descriptor 

 ft_putstr_fd — output string to file descriptor 

 ft_putendl_fd — output string with newline 

 ft_putnbr_fd — output integer to file descriptor 

---

Part 3 – Linked List 

 ft_lstnew — create new node 

 ft_lstadd_front — add node at the beginning 

 ft_lstsize — get list size 

 ft_lstlast — get last node 

 ft_lstadd_back — add node at the end 

 ft_lstdelone — delete single node 

 ft_lstclear — delete entire list 

 ft_lstiter — apply function to each node 

 ft_lstmap — create new list from function 

---

## Resources 

- Linux manual pages
- 42 intranet Libft subject
- Google search for various C-related resources
- peer code reviews and discussions
- AI tools were used only for reviewing code for potential issues
