Universidade da Beira Interior SO

## Problem B

# Seek

## Problem

Este exerc ́ıcio tem como objetivo utilizar as fun ̧c ̃oes do I/O de ficheiros de baixo-n ́ıvel, as chamadas
ao sistema de open, write e lseek.
Podem usar as fun ̧c ̃oes de input do standard library, por exemplo scanf(), mas n ̃ao podem usar
as fun ̧c ̃oes de output do standard library (printf, putchar etc) (nem podem ter estas palavras em
coment ́arios)

O objetivo do programa ́e pesquisar dentro dum ficheiro bin ́ario para encontrar um string escon-
dido. Vai ser dado uma sequˆencia de instru ̧c ̃oes que tem de seguir para obter o string escondido.
H ́a cinco tipos de instru ̧c ̃ao (i) ir para o fim/in ́ıcio dum ficheiro e recuar/avan ̧car n bytes, (ii)
avan ̧car/recuar da posi ̧c ̃ao atual n bytes e (iii) ler n bytes para um buffer (iv) limpar o buffer (v)
terminar.

## Input

O nome do ficheiro bin ́ario para abrir em modo leitura ́e passado no primeiro argumento ao
programa (argv[1]). Se a abertura do ficheiro dar um erro o seu programa dever ́a terminar logo.
De qualquer maneira o valor de retorno do programa dever ́a ser sempre zero.
O input (standard input) contˆem uma sequˆencia de linhas. Cada linha contˆem um car ́acter e
um inteiro separado por um espa ̧co. A sequˆencia termine com o par ’s’ 0(zero). Os caracteres e
os seus significados s ̃ao:

+ n : avan ̧car n bytes

- n : recuar n bytes
i n : ir para o inicio do ficheiro e e avan ̧car n bytes
f n : ir para o fim do ficheiro e recuar n bytes
r n : read/ler n bytes e append a um buffer.
l 0 : limpar o buffer
s 0 : stop

## Output

O output ́e o buffer escrito para o standard output usando apenas o comando write seguido por
um byte (a nova linha).
Para escrever uma nova linha, o car ́acter\n, poder ́a definir uma vari ́avel ou constante e utilizar
write(), por exemplo

const char barran=’\n’;
write(STDOUT_FILENO,&barran,1);

## Constraints

O buffer ter ́a um m ́aximo de 100 bytes, portanto o string a encontrar n ̃ao ter ́a mais de 99 caracteres.

Neste exerc ́ıcio n ̃ao pode usar printf - a palavra printf n ̃ao poder ́a aparecer em parte algum do seu
programa - em vez do printf utilizar write(STDOUTFILENO,..) para escrever para o ecr ̃a.

Invalid Submission = utiliza ̧c ̃ao do standard library .. printf.

Pode ver se a palavra printf est ́a no seu programa usando o comando grep.

Mar ̧co de 2018 1


Universidade da Beira Interior SO

## Samples

Considere o ficheiro deEXactamente 22bytes test1.bin que contˆem o string seguinte (sem fim
de linha)

ola one two three four

Nota que s ̃ao 22 bytes visto que s ̃ao 18 caracteres (a-z) e 4 espa ̧cos. Dever ́a criara este ficheiro
para efetuar testes.
Considere os inputs nos ficheiros input1 e input2 como em baixo.
Dever ́a correr o seu programa com os seus testes da seguinte maneira :

./a.out test1.bin < input
./a.out test1.bin < input

## Sample Input 1

i 2
+ 2
r 3
+ 5
r 5
s 0

## Sample Output 1

onethree

## Sample Input 2

i 2
i 0
r 3
f 2

- 2
r 4
s 0

## Sample Output 2

olafour

Mar ̧co de 2018 2


