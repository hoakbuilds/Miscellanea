open List
open String

let rec readnegotiationparam () =
  let s = read_line() in
  let (n,m) = Scanf.sscanf s "%d %d" (fun n m -> n,m) in
  if (n<=2 || n>=20 || m<0 || m>=20) then readnegotiationparam() else (n,m);;

let rec readkey () =
  let key:int = read_int() in if ( key<1 || key >= 20) then readkey() else key;;

let rec checkconditions i j condn joined =
  if j > List.length condn then joined
  else
  let ncond = List.length (List.nth condn j) in
  let condtojoin = (List.nth condn j) in if (List.nth condtojoin 0) = 0 then checkconditions 1 (j+1) condn ((List.nth condtojoin (ncond-1))::joined)
  else if not(mem (List.nth condtojoin i) joined) then checkconditions 1 (j+1) condn joined
  else if (((List.nth condtojoin 0) > 1) && (i != (List.nth condtojoin 0))) then checkconditions (i+1) j condn joined
  else checkconditions 1 (j+1) condn ((List.nth condtojoin (ncond-1))::joined)
  
let rec readlist i condlist joined =
  if i = 0 then (condlist, joined)
  else
    let s = List.map int_of_string( Str.split (Str.regexp " ") (read_line())) in
    let ncond = (List.nth s 0) in
    if ncond = 0 then readlist (i-1) condlist (List.nth s ((List.length s) -1) :: joined)
    else readlist (i-1) (s::condlist) (checkconditions 1 0 condlist joined);;

let rec finalCheck joined conditions i =
  if i = List.length conditions then joined
  else  finalCheck (checkconditions 1 0 conditions joined) conditions (i+1);;

let (n,m) = readnegotiationparam() in
let k = readkey() in
let (conditions, joined) = readlist m [] [] in
let final = finalCheck joined conditions 0 in
  if (List.mem k final) 
    then print_endline "YES"
      else print_endline "NO";; 