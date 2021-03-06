# ft_printf
Unlock forbidden function for 42 future curriculum.

### Compatibility:
Working with macOS High Sierra version 10.13.4\
Apple LLVM version 9.1.0 (clang-902.0.39.1)\
Target: x86_64-apple-darwin17.5.0\
Thread model: posix

Goal: Reproduces the behavior of printf (attempted without malloc)

##### Note:
About my printf:

1. Estimated to be around 6% speed of the original printf
2. No use of malloc or buffer

##### What I learned:

Speed:
* System call reduces speed. Reduce the amount of write function calls will speed up the function.
* Too many if statements to get the right behavior. 😂
  * Most of the hard-coding are mainly for calculating spaces and handling modifiers

Data structure:
* Use of bits to handle flags
* Dispatch table
* Parsing variadic function.

#### How to improve in future:

Speed wise, store data the data in the buffer and flush the buffer out with single use of write.\
Structure wise, reduce the amount if statements.\
Document the functions and what they do.\
Don't name \*.c files with numbers at the end.

Not one of the best project, but one of the longest.
##### Score:
![](images/printf_score.png)
