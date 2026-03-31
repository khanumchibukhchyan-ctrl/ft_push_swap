*This project has been created as part of the 42 curriculum by manmanuk,kchibukh*

# push_swap

---

## Description

Push_swap is a C program that sorts integers using two stacks (a and b) with minimal operations.  
Stack `a` initially contains a random sequence of positive and/or negative numbers with no duplicates, while stack `b` is empty.  
The program outputs a sequence of operations to sort stack `a` in ascending order using only the allowed Push_swap operations.

---

## Project Goal  

- Sort a stack of integers in ascending order using two stacks with the minimum number of Push_swap operations.
- Implement distinct sorting strategies to optimize performance based on input size and disorder:
- **Optional strategy selector:**
  - `--simple` — Forces the use of your O(n²) algorithm.
  - `--medium` — Forces the use of your O(n√n) algorithm.
  - `--complex` — Forces the use of your O(n log n) algorithm.
  - `--adaptive` — Uses an adaptive algorithm based on disorder. This is the default behavio
- Generate a valid sequence of Push_swap operations (`sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`) to sort the stack efficiently.  

---

## Instructions

---

### Compilation

The project is compiled using the cc compiler:

cc -Wall -Wextra -Werror *.c -o push_swap

This will generate the executable:

./push_swap

---

### Allowed Operations

- **sa** – swap the first two elements of stack A  
- **sb** – swap the first two elements of stack B  
- **ss** – perform sa and sb simultaneously  
- **pa** – push the first element from stack B to stack A  
- **pb** – push the first element from stack A to stack B  
- **ra** – rotate stack A (first element becomes last)  
- **rb** – rotate stack B  
- **rr** – rotate both stacks  
- **rra** – reverse rotate stack A  
- **rrb** – reverse rotate stack B  
- **rrr** – reverse rotate both stacks  

---

## Resources

- 42 push_swap subject documentation  
- Stack and sorting algorithm tutorials:  

### AI Usage

AI tools were used only for:
- Reviewing documentation structure
- Clarifying algorithm explanations
- Improving the clarity of the README

