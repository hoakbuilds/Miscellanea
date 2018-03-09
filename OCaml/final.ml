let reverse = 0;; (*arithmetically checking if a number is a palindrome, no use of lists, vectors and/or strings*)
let remainder = 0;;

let rec lerbase() =
	let (base:int) = read_int() in if(base<0 || base>10) then lerbase() else base;;

let base = lerbase();;

let rec verifbase num base =
	if (num = 0) then true
	else if (num mod 10 >= base) then false
	else verifbase (num/10) base;;

let rec verifpal n reverse remainder =
	if n = 0 then reverse
	else verifpal (n/10) ((reverse*10)+(n mod 10)) (n mod 10);;

let (palindrome:int) = read_int() in
	if(not(verifbase palindrome base)) then print_string "ERROR\n"
	else let reverse = verifpal palindrome reverse remainder in if reverse = palindrome then print_string "YES\n" else print_string "NO\n";;
