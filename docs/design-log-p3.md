# Project 3 Design Log
**Author:** <Cody Miller> · **P2 code used:** <my own>
**Tools used:** <Used Claude: helped explain the spec and what my job was then asked it to direct me to areas of the spec that would help me complete functions since the spec was long.


## 1. Hash table
For the hash table I used chaining because it seemed simple to implement as only one bucket needs to be searched and chains dont effect each other. The spec also points out the longest probe length is 6 for chaining and 30 for open addressing so chaining seems more efficient. 

I used the reccomendation from the spec, FNV-1a, because it meets the requirements that every character touches every byte so that names with 1 character differences dont collide. It also is order sensitive so that same characters in different orders dont collide. FNV-1a is what allows the longest chain to only be 6 long. 

I selected the load factor (size/bucket count) to have a threshold of one because it is a good balance of speed and memory usage. Increasing or decreasing this threshold gives little benefit compared to the cost to speed and memory in each case. (smaller threshold = faster but more memory and larger threshold = slower but less memeory)

For the resize policy I decided to double when the load factor was going to hit 1. The starting value I selected was 8 mainly because it was a power of 2 and was within the 1-64 requirement. I decided to double it because it was a familiar method that worked well in project 2 and it benefits by staying a power of 2. add() is amortized  (1). A single resize costs O(n) because grow() moves every entry, but resizes only happen when the count reaches 8, 16, 32, ..., so the total work across all resizes is a geometric series: 8 + 16 +... + 2^j < 2N. For my 10,000 tools that is 11 resizes and 16,376 moves, about 1.6 extra moves per add, so the average cost per add stays constant.

Bucket Count: 16,384 
Load Factor: 0.6104
Max Probe Length: 6
Alternative Hash Chain Length: 9000


## 2. Pointer stability
Pointers survived from find() because the buckets store a unique pointer to the tool and when a resize occurs the tool never moves since moving a unique_ptr copies the address into the new bucket. This allows find() to always point at the same object. 

## 3. Calculator trace
The '2' (Value: '2') is stored in the value stack then '*' (OP: '*') is stored in the op stack. The opening paranthes '('(OP: '*' '(') gets pushed into op stack then '3' (Value: '2' '3') gets pushed onto value stack and '+' (OP: '*' '(' '+') onto op stack then the '4' (Value: '2' '3' '4') onto value stack. When the closing parenthese gets hit ')' the values inside the parentheses get calculated the '+' op is popped (OP: '*' '(' )from the op stack and '4' and '3' are popped from the value stack  and compute 3+4 =7. The '7' (Value: '2' '7')is pushed onto value stack and '(' (OP:'*')is popped from the op stack. When '-' is seen and its precendence is lower than '*' (OP: )so its popped as well as '2' and '7' (Value: )and the 2 * 7 is computed to '14' (Value: '14') which is pushed onto the value stack then '-' (OP: '-')gets pushed onto op stack and '5' (Value: '14' '5')onto value stack. Then '-' (OP: )gets popped and '14' and '5' (Value: )get popped and 14-5 is computed and the final result is '9'. 

## 4. Errors as values
Tools, resolve(), and calc_evaluate() return errors instead of throwing becuase errors or failures are expected and should respond accordingly by trying something else and respond with a failure message to inform the user. Exceptions are for programmer errors like logic errors and the reason for the error is less specific. Throwing would treat an expected event as if it were a bug. It would land in the same catch the dispatcher keeps as a last line of defense for crashes in broken code. The model couldnt tell "your path is outside the workspace" apart from "this tool's code is broken."
## 5. What I would design differently
I would store each entry's full hash inside the Entry next to key and tool. Right now grow() recomputes FNV-1a for every key on every resize for 10,000 tools, grow() could compute each new index directly with hash (new_count - 1)`, and find() could compare the stored hash before comparing strings, skipping most string
comparisons in a chain.