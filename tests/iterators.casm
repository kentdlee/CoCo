Function: main/0
Constants: None, "Please enter a list of integers separated by spaces: ", "Here are the characters in the string.", "Here are the elements of the list after splitting the string.", "Here are the elements of the list using indexing.", "Here are the elements backwards using indexing.", 1, 0, "The sum of the integers is", "and the product is", -1, -1
Locals: x, lst, a, b, c, product, sum
Globals: input, split, print, int, range, len
BEGIN
          LOAD_GLOBAL                    0
          LOAD_CONST                     1
          CALL_FUNCTION                  1
          STORE_FAST                     0
          LOAD_FAST                      0
          LOAD_ATTR                      1
          CALL_FUNCTION                  0
          STORE_FAST                     1
          LOAD_GLOBAL                    2
          LOAD_CONST                     2
          CALL_FUNCTION                  1
          POP_TOP                  
          SETUP_LOOP               label02
          LOAD_FAST                      0
          GET_ITER                 
label00:  FOR_ITER                 label01
          STORE_FAST                     2
          LOAD_GLOBAL                    2
          LOAD_FAST                      2
          CALL_FUNCTION                  1
          POP_TOP                  
          JUMP_ABSOLUTE            label00
label01:  POP_BLOCK                
label02:  LOAD_GLOBAL                    2
          LOAD_CONST                     3
          CALL_FUNCTION                  1
          POP_TOP                  
          SETUP_LOOP               label05
          LOAD_FAST                      1
          GET_ITER                 
label03:  FOR_ITER                 label04
          STORE_FAST                     3
          LOAD_GLOBAL                    2
          LOAD_GLOBAL                    3
          LOAD_FAST                      3
          CALL_FUNCTION                  1
          CALL_FUNCTION                  1
          POP_TOP                  
          JUMP_ABSOLUTE            label03
label04:  POP_BLOCK                
label05:  LOAD_GLOBAL                    2
          LOAD_CONST                     4
          CALL_FUNCTION                  1
          POP_TOP                  
          SETUP_LOOP               label08
          LOAD_GLOBAL                    4
          LOAD_GLOBAL                    5
          LOAD_FAST                      1
          CALL_FUNCTION                  1
          CALL_FUNCTION                  1
          GET_ITER                 
label06:  FOR_ITER                 label07
          STORE_FAST                     4
          LOAD_GLOBAL                    2
          LOAD_FAST                      1
          LOAD_FAST                      4
          BINARY_SUBSCR            
          CALL_FUNCTION                  1
          POP_TOP                  
          JUMP_ABSOLUTE            label06
label07:  POP_BLOCK                
label08:  LOAD_GLOBAL                    2
          LOAD_CONST                     5
          CALL_FUNCTION                  1
          POP_TOP                  
          SETUP_LOOP               label11
          LOAD_GLOBAL                    4
          LOAD_GLOBAL                    5
          LOAD_FAST                      1
          CALL_FUNCTION                  1
          LOAD_CONST                     6
          BINARY_SUBTRACT          
          LOAD_CONST                    10
          LOAD_CONST                    11
          CALL_FUNCTION                  3
          GET_ITER                 
label09:  FOR_ITER                 label10
          STORE_FAST                     4
          LOAD_GLOBAL                    2
          LOAD_FAST                      1
          LOAD_FAST                      4
          BINARY_SUBSCR            
          CALL_FUNCTION                  1
          POP_TOP                  
          JUMP_ABSOLUTE            label09
label10:  POP_BLOCK                
label11:  LOAD_CONST                     6
          STORE_FAST                     5
          LOAD_CONST                     7
          STORE_FAST                     6
          SETUP_LOOP               label14
          LOAD_FAST                      1
          GET_ITER                 
label12:  FOR_ITER                 label13
          STORE_FAST                     3
          LOAD_FAST                      5
          LOAD_GLOBAL                    3
          LOAD_FAST                      3
          CALL_FUNCTION                  1
          BINARY_MULTIPLY          
          STORE_FAST                     5
          LOAD_FAST                      6
          LOAD_GLOBAL                    3
          LOAD_FAST                      3
          CALL_FUNCTION                  1
          BINARY_ADD               
          STORE_FAST                     6
          JUMP_ABSOLUTE            label12
label13:  POP_BLOCK                
label14:  LOAD_GLOBAL                    2
          LOAD_CONST                     8
          LOAD_FAST                      6
          LOAD_CONST                     9
          LOAD_FAST                      5
          CALL_FUNCTION                  4
          POP_TOP                  
          LOAD_CONST                     0
          RETURN_VALUE             
END
