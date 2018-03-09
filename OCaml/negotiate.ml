let rec lernegociadores () =
  let negociadores:int = read_int() in if negociadores<2||negociadores>20 then lernegociadores () else negociadores;;

let rec lercondicoes () =
  let condicoes:int = read_int() in if condicoes<1||condicoes>20 then lercondicoes () else condicoes;;

let rec lerchave () =
  let chave:int = read_int() in if chave<1||chave>20 then lerchave () else chave;;

