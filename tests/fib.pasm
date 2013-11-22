Function: fib/1
Constants: None, 0, 1
Locals: n, lastVal, currentVal, i, nextVal
BEGIN
          LOAD_CONST                     1
          STORE_FAST                     1
          LOAD_CONST                     2
          STORE_FAST                     2
          LOAD_CONST                     2
          STORE_FAST                     3
          SETUP_LOOP               label02
label00:  LOAD_FAST                      3
          LOAD_FAST                      0
          COMPARE_OP                     2
          POP_JUMP_IF_FALSE        label01
          BREAK_LOOP               
          JUMP_FORWARD                   0
label01:  LOAD_FAST                      1
          LOAD_FAST                      2
          BINARY_ADD               
          STORE_FAST                     4
          LOAD_FAST                      2
          STORE_FAST                     1
          LOAD_FAST                      4
          STORE_FAST                     2
          LOAD_FAST                      3
          LOAD_CONST                     2
          INPLACE_ADD              
          STORE_FAST                     3
          JUMP_ABSOLUTE            label00
label02:  LOAD_FAST                      2
          RETURN_VALUE             
END
Function: main/0
Constants: None, "Please enter an integer: ", "fib(", ") ="
Locals: x
Globals: int, input, print, str, fib
BEGIN
          LOAD_GLOBAL                    0
          LOAD_GLOBAL                    1
          LOAD_CONST                     1
          CALL_FUNCTION                  1
          CALL_FUNCTION                  1
          STORE_FAST                     0
          LOAD_GLOBAL                    2
          LOAD_CONST                     2
          LOAD_GLOBAL                    3
          LOAD_FAST                      0
          CALL_FUNCTION                  1
          BINARY_ADD               
          LOAD_CONST                     3
          BINARY_ADD               
          LOAD_GLOBAL                    4
          LOAD_FAST                      0
          CALL_FUNCTION                  1
          CALL_FUNCTION                  2
          POP_TOP                  
          LOAD_CONST                     0
          RETURN_VALUE             
END
