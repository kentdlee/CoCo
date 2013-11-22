Function: funA/2
Constants: None, 0, 1
Locals: x, y, z
Globals: print
BEGIN
          LOAD_CONST                     1
          STORE_FAST                     2
          SETUP_LOOP               label02
label00:  LOAD_FAST                      0
          LOAD_FAST                      1
          COMPARE_OP                     0
          POP_JUMP_IF_FALSE        label01
          LOAD_FAST                      2
          LOAD_FAST                      0
          BINARY_ADD               
          STORE_FAST                     2
          LOAD_GLOBAL                    0
          LOAD_FAST                      0
          LOAD_FAST                      1
          LOAD_FAST                      2
          CALL_FUNCTION                  3
          POP_TOP                  
          LOAD_FAST                      0
          LOAD_CONST                     2
          BINARY_ADD               
          STORE_FAST                     0
          JUMP_ABSOLUTE            label00
label01:  POP_BLOCK                
label02:  LOAD_FAST                      2
          RETURN_VALUE             
END

Function: main/0
Constants: None, "Please enter an integer: ", "The answer is"
Locals: x, y, z
Globals: int, input, funA, print
BEGIN
          LOAD_GLOBAL                    0
          LOAD_GLOBAL                    1
          LOAD_CONST                     1
          CALL_FUNCTION                  1
          CALL_FUNCTION                  1
          STORE_FAST                     0
          LOAD_GLOBAL                    0
          LOAD_GLOBAL                    1
          LOAD_CONST                     1
          CALL_FUNCTION                  1
          CALL_FUNCTION                  1
          STORE_FAST                     1
          LOAD_GLOBAL                    2
          LOAD_FAST                      0
          LOAD_FAST                      1
          CALL_FUNCTION                  2
          STORE_FAST                     2
          LOAD_GLOBAL                    3
          LOAD_CONST                     2
          LOAD_FAST                      2
          CALL_FUNCTION                  2
          POP_TOP                  
          LOAD_CONST                     0
          RETURN_VALUE             
END
