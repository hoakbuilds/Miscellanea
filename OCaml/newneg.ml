open Array
open Scanf;;

let setConds i j conditions icond n =
  for j = 0 to n do
    conditions.(i).(j) <- icond.(j)
  done;
  conditions

let rec readchk i cond negTable n =
  if( ( i = n ) && ( mem cond.(i) negTable)) then true
  else if (mem cond.(i) negTable) then readchk (i+1) cond negTable n
  else false

let rec chkaux i j conditions negTable n =
  if ( ( j = n ) && ( mem conditions.(i).(j) negTable) ) then true
  else if( mem conditions.(i).(j) negTable) then chkaux i (j+1) conditions negTable n
    else false

let rec checkaux f i conditions negTable n k =
  if i = n then (f, negTable)
  else 
    if conditions.(i).(0) != -1 
    then let ncond = conditions.(i).(0) in 
      if ( chkaux i 1 conditions negTable ncond )
        then checkaux (1) (i+1) conditions (append negTable [|conditions.(i).( (conditions.(i).(0) + 1) )|]) n k
        else checkaux (f) (i+1) conditions negTable n k
    else checkaux (f) (i+1) conditions negTable n k
    
let rec check f conditions negTable n tot k =
  let (f, negTable) = checkaux f 0 conditions negTable n k in 
  if (f = 0) || ( mem k negTable) then negTable
  else check 0 conditions negTable n tot k

let rec readParams i conditions negTable  =
  if i = -1 then (conditions, negTable)
  else
    let indcond = of_list (List.map  int_of_string (Str.split (Str.regexp " ") (read_line()) ) ) in
    if indcond.(0) = 0 then readParams (i-1) conditions (append negTable [|indcond.(1)|] )
    else if( readchk 1 indcond negTable indcond.(0) ) 
      then readParams (i-1) conditions ( append negTable [| indcond.( indcond.(0) + 1) |])
    else readParams (i-1) ( setConds i 0 conditions indcond ((length indcond) - 1 ) ) negTable

let (n,m) = Scanf.sscanf (read_line()) "%d %d" ( fun n m -> n,m );;
let key = Scanf.sscanf (read_line())  "%d" ( fun k -> k );;
let conditions = make_matrix m (n+2) (-1) in
let (conditions, negTable) = readParams (m-1) conditions [||] in
  print_endline(
    if(mem key negTable)
    then "YES"
    else let finalnt = check (0) conditions negTable m n key in
    if(mem key finalnt) 
    then "YES"
    else "NO"
   )