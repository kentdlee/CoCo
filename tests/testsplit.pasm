Function: main/0
Constants: None, "Please enter a string: "
Locals: x, a
Globals: input, split, print
BEGIN
          LOAD_GLOBAL                    0
          LOAD_CONST                     1
          CALL_FUNCTION                  1
          STORE_FAST                     0
          SETUP_LOOP               label02
          LOAD_FAST                      0
          LOAD_ATTR                      1
          CALL_FUNCTION                  0
          GET_ITER                 
label00:  FOR_ITER                 label01
          STORE_FAST                     1
          LOAD_GLOBAL                    2
          LOAD_FAST                      1
          CALL_FUNCTION                  1
          POP_TOP                  
          JUMP_ABSOLUTE            label00
label01:  POP_BLOCK                
label02:  LOAD_CONST                     0
          RETURN_VALUE             
END
