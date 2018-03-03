let base b = read_line (*checking if a number is a palindrome*)
let verifica a b =

if List.exists a b then print_endline "ERROR"
else ( let palindrom l = read_line;;
    let rec aux l0 l1 =
      match (l0, l1) with
      | _,[] -> (true,[])
      | hd :: tl, [x] -> (hd = x, tl)
      | _, hd1 :: tl1 -> let (pal, ll) = aux l0 tl1 in
            match ll with
            | [] -> (pal, [])
            | hd::tl -> (pal && hd1 = hd, tl) in
              match l with
              [] -> true
              | _ -> fst (aux l l) )

l = true ? print_endline "YES" : print_endline "NO";;
