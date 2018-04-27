open Array
open String

let rec readnegotiationparam () =
  let s = read_line() in
  let (n,m) = Scanf.sscanf s "%d %d" (fun n m -> n,m) in
  if (n<=2 || n>=20 || m<0 || m>=20) then readnegotiationparam() else (n,m);;

let rec readkey () =
  let key:int = read_int() in if ( key<1 || key >= 20) then readkey() else key;;

let rec checkconditions i j condn joined =
  if j > Array.length condn then joined
  else
  let ncond = Array.length condn.(j) in
  let condtojoin = condn.(j) in if condtojoin.(0) = 0 then checkconditions 1 (j+1) condn (Array.append [|condtojoin.(ncond-1)|] joined)
  else if not(Array.mem condtojoin.(i) joined) then checkconditions 1 (j+1) condn joined
  else if ((condtojoin.(i) > 1) && (i != condtojoin.(0))) then checkconditions (i+1) j condn joined
  else checkconditions 1 (j+1) condn (Array.append [|condtojoin.(ncond-1)|] joined)
  
let rec readArray i conditions joined =
  if i = 0 then (conditions, joined)
  else
    let s = Array.of_list (List.map int_of_string(Str.split (Str.regexp " ") (read_line()))) in
    let ncond = s.(0) in
    if ncond = 0 then readArray (i-1) conditions ( Array.append [|s.((Array.length s))|] joined)
    else readArray (i-1) (Array.append [|s|] conditions) (checkconditions 1 0 conditions joined);;

let rec finalCheck joined conditions i =
  if i = Array.length conditions then joined
  else  finalCheck (checkconditions 1 0 conditions joined) conditions (i+1);;

let (n,m) = readnegotiationparam() in
let k = readkey() in
let (conditions, joined) = readArray m [||] [||] in
let final = finalCheck joined conditions 0 in
  if (Array.mem k final) 
    then print_endline "YES"
      else print_endline "NO";; 