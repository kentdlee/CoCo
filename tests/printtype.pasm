Function: factorial/1
Constants: None, 0, 1
Locals: n
Globals: factorial
BEGIN
          LOAD_FAST                      0
          LOAD_CONST                     1
          COMPARE_OP                     2
          POP_JUMP_IF_FALSE        label00
          LOAD_CONST                     2
          RETURN_VALUE             
label00:  LOAD_FAST                      0
          LOAD_GLOBAL                    0
          LOAD_FAST                      0
          LOAD_CONST                     2
          BINARY_SUBTRACT          
          CALL_FUNCTION                  1
          BINARY_MULTIPLY          
          RETURN_VALUE             
END
Function: main/0
Constants: None
Globals: print, type, factorial
BEGIN
          LOAD_GLOBAL                    0
          LOAD_GLOBAL                    1
          LOAD_GLOBAL                    2
          CALL_FUNCTION                  1
          CALL_FUNCTION                  1
          POP_TOP                  
          LOAD_CONST                     0
          RETURN_VALUE             
END
