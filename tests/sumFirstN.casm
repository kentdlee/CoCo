Function: sumFirstN/1
Constants: None, 0, 1
Locals: n, total, i
Globals: range
BEGIN
          LOAD_CONST                     1
          STORE_FAST                     1
          SETUP_LOOP               label02
          LOAD_GLOBAL                    0
          LOAD_CONST                     2
          LOAD_FAST                      0
          LOAD_CONST                     2
          BINARY_ADD               
          CALL_FUNCTION                  2
          GET_ITER                 
label00:  FOR_ITER                 label01
          STORE_FAST                     2
          LOAD_FAST                      1
          LOAD_FAST                      2
          BINARY_ADD               
          STORE_FAST                     1
          JUMP_ABSOLUTE            label00
label01:  POP_BLOCK                
label02:  LOAD_FAST                      1
          RETURN_VALUE             
END
Function: main/0
Constants: None, "Please enter an integer: ", "The sum of 1 to", "is"
Locals: x, sumTotal
Globals: int, input, sumFirstN, print
BEGIN
          LOAD_GLOBAL                    0
          LOAD_GLOBAL                    1
          LOAD_CONST                     1
          CALL_FUNCTION                  1
          CALL_FUNCTION                  1
          STORE_FAST                     0
          LOAD_GLOBAL                    2
          LOAD_FAST                      0
          CALL_FUNCTION                  1
          STORE_FAST                     1
          LOAD_GLOBAL                    3
          LOAD_CONST                     2
          LOAD_FAST                      0
          LOAD_CONST                     3
          LOAD_FAST                      1
          CALL_FUNCTION                  4
          POP_TOP                  
          LOAD_CONST                     0
          RETURN_VALUE             
END
