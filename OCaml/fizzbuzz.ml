let i = 1;;

let rec fizzbuzz i = 
  print_endline (
    if ( i mod 3 = 0 ) && ( i mod 5 = 0 ) then "FizzBuzz" else
    if i mod 5 = 0 then "Buzz" else 
    if i mod 3 = 0 then "Fizz" else string_of_int i ) in fizzbuzz (i+1);;