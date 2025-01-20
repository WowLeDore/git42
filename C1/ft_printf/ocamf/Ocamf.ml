let socl =
  function
  | char :: _ -> Char.escaped char
  |         _ -> ""

let rec charlist_of_string =
  function
  | ""  -> []
  | str -> String.get str 0 :: charlist_of_string (String.sub str 1 (String.length str - 1)) 

let put_inv_flag last_t flags n =
  invalid_arg
    ((match socl last_t with
        | "" -> "Flag required after "
        | t  -> "Flag " ^ (match t with | " " -> "' '" | c -> c) ^ " is not allowed with ") ^
     String.sub flags 0 (n + 1) ^ "")

let printf str =
  print_endline
    (match charlist_of_string str with
     | '%' :: t0 ->
         (match t0 with
          | '-' :: t1 ->
              (match t1 with
               | '+' :: t2 ->
                   (match t2 with
                    | '1' :: t3 | '2' :: t3 | '3' :: t3 | '4' :: t3 | '5' :: t3
                    | '6' :: t3 | '7' :: t3 | '8' :: t3 | '9' :: t3 ->
                        (match t3 with
                         | '.' :: t4 ->
                             (match t4 with
                              | '1' :: t5 | '2' :: t5 | '3' :: t5 | '4' :: t5 | '5' :: t5
                              | '6' :: t5 | '7' :: t5 | '8' :: t5 | '9' :: t5 | '0' :: t5 ->
                                  (match t5 with
                                   | 'd' :: t6 | 'i' :: t6 ->
                                       "LeftJustify SignForced " ^ socl t2 ^ "Width Precision." ^ socl t4 ^ " Integer(" ^ socl t5 ^ ")"
                                   | _ -> put_inv_flag t5 str 5)
                              | 'd' :: t5 | 'i' :: t5 ->
                                  "LeftJustify SignForced " ^ socl t2 ^ "Width Precision.0 Integer(" ^ socl t4 ^ ")"
                              | _ -> put_inv_flag t4 str 4)
                         | 'd' :: t4 | 'i' :: t4 ->
                             "LeftJustify SignForced " ^ socl t2 ^ "Width Integer(" ^ socl t3 ^ ")"
                         | _ -> put_inv_flag t3 str 3)
                    | '.' :: t3 ->
                        (match t3 with
                         | '1' :: t4 | '2' :: t4 | '3' :: t4 | '4' :: t4 | '5' :: t4
                         | '6' :: t4 | '7' :: t4 | '8' :: t4 | '9' :: t4 | '0' :: t4 ->
                             (match t4 with
                              | 'd' :: t5 | 'i' :: t5 ->
                                  "LeftJustify SignForced Precision." ^ socl t3 ^ " Integer(" ^ socl t4 ^ ")"
                              | _ -> put_inv_flag t4 str 4)
                         | 'd' :: t4 | 'i' :: t4 ->
                             "LeftJustify SignForced Precision.0 Integer(" ^ socl t3 ^ ")"
                         | _ -> put_inv_flag t3 str 3)
                    | 'd' :: t3 | 'i' :: t3 ->
                        "LeftJustify SignForced Integer(" ^ socl t2 ^ ")"
                    | _ -> put_inv_flag t2 str 2)
               | ' ' :: t2 ->
                   (match t2 with
                    | '1' :: t3 | '2' :: t3 | '3' :: t3 | '4' :: t3 | '5' :: t3
                    | '6' :: t3 | '7' :: t3 | '8' :: t3 | '9' :: t3 ->
                        (match t3 with
                         | '.' :: t4 ->
                             (match t4 with
                              | '1' :: t5 | '2' :: t5 | '3' :: t5 | '4' :: t5 | '5' :: t5
                              | '6' :: t5 | '7' :: t5 | '8' :: t5 | '9' :: t5 | '0' :: t5 ->
                                  (match t5 with
                                   | 'd' :: t6 | 'i' :: t6 ->
                                       "LeftJustify SpaceSigned " ^ socl t2 ^ "Width Precision." ^ socl t4 ^ " Integer(" ^ socl t5 ^ ")"
                                   | _ -> put_inv_flag t5 str 5)
                              | 'd' :: t5 | 'i' :: t5 ->
                                  "LeftJustify SpaceSigned " ^ socl t2 ^ "Width Precision.0 Integer(" ^ socl t4 ^ ")"
                              | _ -> put_inv_flag t4 str 4)
                         | 'd' :: t4 | 'i' :: t4 ->
                             "LeftJustify SpaceSigned " ^ socl t2 ^ "Width Integer(" ^ socl t3 ^ ")"
                         | _ -> put_inv_flag t3 str 3)
                    | '.' :: t3 ->
                        (match t3 with
                         | '1' :: t4 | '2' :: t4 | '3' :: t4 | '4' :: t4 | '5' :: t4
                         | '6' :: t4 | '7' :: t4 | '8' :: t4 | '9' :: t4 | '0' :: t4 ->
                             (match t4 with
                              | 'd' :: t5 | 'i' :: t5 ->
                                  "LeftJustify SpaceSigned Precision." ^ socl t3 ^ " Integer(" ^ socl t4 ^ ")"
                              | _ -> put_inv_flag t4 str 4)
                         | 'd' :: t4 | 'i' :: t4 ->
                             "LeftJustify SpaceSigned Precision.0 Integer(" ^ socl t3 ^ ")"
                         | _ -> put_inv_flag t3 str 3)
                    | 'd' :: t3 | 'i' :: t3 ->
                        "LeftJustify SpaceSigned Integer(" ^ socl t2 ^ ")"
                    | _ -> put_inv_flag t2 str 2)
               | '#' :: t2 ->
                   (match t2 with
                    | '1' :: t3 | '2' :: t3 | '3' :: t3 | '4' :: t3 | '5' :: t3
                    | '6' :: t3 | '7' :: t3 | '8' :: t3 | '9' :: t3 ->
                        (match t3 with
                         | '.' :: t4 ->
                             (match t4 with
                              | '1' :: t5 | '2' :: t5 | '3' :: t5 | '4' :: t5 | '5' :: t5
                              | '6' :: t5 | '7' :: t5 | '8' :: t5 | '9' :: t5 | '0' :: t5 ->
                                  (match t5 with
                                   | 'x' :: t6 | 'X' :: t6 ->
                                       "LeftJustify FormAlted " ^ socl t2 ^ "Width Precision." ^ socl t4 ^ " Hexadecimal(" ^ socl t5 ^ ")"
                                   | _ -> put_inv_flag t5 str 5)
                              | 'x' :: t5 | 'X' :: t5 ->
                                  "LeftJustify FormAlted " ^ socl t2 ^ "Width Precision.0 Hexadecimal(" ^ socl t4 ^ ")"
                              | _ -> put_inv_flag t4 str 4)
                         | 'x' :: t4 | 'X' :: t4 ->
                             "LeftJustify FormAlted " ^ socl t2 ^ "Width Hexadecimal(" ^ socl t3 ^ ")"
                         | _ -> put_inv_flag t3 str 3)
                    | '.' :: t3 ->
                        (match t3 with
                         | '1' :: t4 | '2' :: t4 | '3' :: t4 | '4' :: t4 | '5' :: t4
                         | '6' :: t4 | '7' :: t4 | '8' :: t4 | '9' :: t4 | '0' :: t4 ->
                             (match t4 with
                              | 'x' :: t5 | 'X' :: t5 ->
                                  " LeftJustify FormAlted Precision." ^ socl t3 ^ " Hexadecimal(" ^ socl t4 ^ ")"
                              | _ -> put_inv_flag t4 str 4)
                         | 'x' :: t4 | 'X' :: t4 ->
                             "LeftJustify FormAlted Precision.0 Hexadecimal(" ^ socl t3 ^ ")"
                         | _ -> put_inv_flag t3 str 3)
                    | 'x' :: t3 | 'X' :: t3 ->
                        "LeftJustify FormAlted Hexadecimal(" ^ socl t2 ^ ")"
                    | _ -> put_inv_flag t2 str 2)
               | '1' :: t2 | '2' :: t2 | '3' :: t2 | '4' :: t2 | '5' :: t2
               | '6' :: t2 | '7' :: t2 | '8' :: t2 | '9' :: t2 -> invalid_arg str
                (*match t2 with
| *)
               | '.' :: t2 -> invalid_arg str
               | 'c' :: t2 -> invalid_arg str
               | 's' :: t2 -> invalid_arg str
               | 'p' :: t2 -> invalid_arg str
               | 'd' :: t2 | 'i' :: t2 -> invalid_arg str
               | 'u' :: t2 -> invalid_arg str
               | 'x' :: t2 -> invalid_arg str
               | 'X' :: t2 -> invalid_arg str
               | _ -> invalid_arg str)
          | '0' :: t1 -> invalid_arg str
          | '+' :: t1 -> invalid_arg str
          | ' ' :: t1 -> invalid_arg str
          | '#' :: t1 -> invalid_arg str
          | '1' :: t1 | '2' :: t1 | '3' :: t1 | '4' :: t1 | '5' :: t1
          | '6' :: t1 | '7' :: t1 | '8' :: t1 | '9' :: t1 ->
              (match t1 with
               | '.' :: t2 -> 
                   (match t2 with
                    | '1' :: t3 | '2' :: t3 | '3' :: t3 | '4' :: t3 | '5' :: t3
                    | '6' :: t3 | '7' :: t3 | '8' :: t3 | '9' :: t3 | '0' :: t3 ->
                        (match t3 with
                         | 's' :: t4 -> "MinWidth" ^ socl t0 ^ " MaxWidth" ^ socl t2 ^ " String"
                         | 'd' :: t4 | 'i' :: t4 -> "MinWidth" ^ socl t0 ^ " Precision." ^ socl t2 ^ " Integer(" ^ socl t3 ^ ")"
                         | 'u' :: t4 -> "MinWidth" ^ socl t0 ^ " Precision." ^ socl t2 ^ " UnsignedInteger"
                         | 'x' :: t4 | 'X' :: t4 -> "MinWidth" ^ socl t0 ^ " Precision." ^ socl t2 ^ " Hexadecimal(" ^ socl t3 ^ ")"
                         | _ -> put_inv_flag t3  str 3)
                    | 's' :: t3 -> "MinWidth" ^ socl t0 ^ " MaxWidth0 String"
                    | 'd' :: t3 | 'i' :: t3 -> "MinWidth" ^ socl t0 ^ " Precision.0 Integer(" ^ socl t2 ^ ")"
                    | 'u' :: t3 -> "MinWidth" ^ socl t0 ^ " Precision.0 UnsignedInteger"
                    | 'x' :: t3 | 'X' :: t3 -> "MinWidth" ^ socl t0 ^ " Precision.0 Hexadecimal(" ^ socl t2 ^ ")"
                    | _ -> put_inv_flag t2  str 2)
               | 'c' :: t2 -> "MinWidth" ^ socl t0 ^ " Characater"
               | 's' :: t2 -> "MinWidth" ^ socl t0 ^ " String"
               | 'p' :: t2 -> "MinWidth" ^ socl t0 ^ " Pointer"
               | 'd' :: t2 | 'i' :: t2 -> "MinWidth" ^ socl t0 ^ " Integer(" ^ socl t0 ^ ")"
               | 'u' :: t2 -> "MinWidth" ^ socl t0 ^ " UnsignedInteger"
               | 'x' :: t2 | 'X' :: t2 -> "MinWidth" ^ socl t0 ^ " Hexadecimal(" ^ socl t0 ^ ")"
               | _ -> put_inv_flag t1 str 1)
          | '.' :: t1 -> 
              (match t1 with
               | '1' :: t2 | '2' :: t2 | '3' :: t2 | '4' :: t2 | '5' :: t2
               | '6' :: t2 | '7' :: t2 | '8' :: t2 | '9' :: t2 | '0' :: t2 ->
                   (match t2 with
                    | 's' :: t3 -> "MaxWidth" ^ socl t1 ^ " String"
                    | 'd' :: t3 | 'i' :: t3 -> "Precision." ^ socl t1 ^ " Integer(" ^ socl t2 ^ ")"
                    | 'u' :: t3 -> "Precision." ^ socl t1 ^ " UnsignedInteger"
                    | 'x' :: t3 | 'X' :: t3 -> "Precision." ^ socl t1 ^ " Hexadecimal(" ^ socl t2 ^ ")"
                    | _ -> put_inv_flag t2  str 2)
               | 's' :: t2 -> "MaxWidth0 String"
               | 'd' :: t2 | 'i' :: t2 -> "Precision.0 Integer(" ^ socl t1 ^ ")"
               | 'u' :: t2 -> "Precision.0 UnsignedInteger"
               | 'x' :: t2 | 'X' :: t2 -> "Precision.0 Hexadecimal(" ^ socl t1 ^ ")"
               | _ -> put_inv_flag t1  str 1)
          | 'c' :: t1 -> "Characater"
          | 's' :: t1 -> "String"
          | 'p' :: t1 -> "Pointer"
          | 'd' :: t1 | 'i' :: t1 -> "Integer(" ^ socl t0 ^ ")"
          | 'u' :: t1 -> "UnsignedInteger"
          | 'x' :: t1 | 'X' :: t1 -> "Hexadecimal(" ^ socl t0 ^ ")"
          | '%' :: t1 -> "Percentage"
          | _ -> put_inv_flag t0 str 0)
     | _ -> invalid_arg "Flag % is required")
