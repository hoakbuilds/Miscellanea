# Escalonamento por Prioridades

## Problem C

Dado os dados sobre um conjunto de processos, nomeadamente o tempo de chegada, prioridade e
tempo de dura¸c˜ao/execu¸c˜ao (burst-time) de cada processo escreva um programa para indicar em
cada instante do tempo qual o processo a correr (chamado o ”trace”). O trace come¸car´a no tempo
zero. No fim o programa dever´a imprimir para a ecr˜a a estat´ıstica do tempo m´edio de circula¸c˜ao
. O programa aplicar´a o algoritmo de escalonamento por prioridades com preemp¸c˜ao.

## Input

Uma linha com um inteiro N indicando o numero de processos.
A seguir, N linhas cada uma com trˆes inteiros separados por um espa¸co. Os trˆes inteiros
representam o tempo de chegada, a prioridade e o tempo de dura¸c˜ao. Estas N linhas representam
os N processos com processo ID’s P1, P2, ..PN, neste ordem, ordenados por tempo de chegada.
Nota que
a prioridade ´e um inteiro de 1-100
o tempo de chegada ´e um inteiro de 0-100
o tempo de dura¸c˜ao ´e um inteiro de 1-10
No caso de empate : o processo com numero menor ser´a escolhido.

## Output

O output ´e em primeiro lugar um ”trace” mostrando em cada instante qual o processo que est´a
a executar. O trace terminar´a quando todos os processos s˜ao terminados. Cada linha do ”trace”
tem o formato
tempo-PN
ou
tempo-IDLE
onde N (1....) ´e o numero de processo (PID) a executar e IDLE indica que neste tempo n˜ao h´a
nenhum processo a executar
Depois ser´a mostrada a estat´ıstica de tempo m´edio de circula¸c˜ao (TMC) com um ponto decimal.
Repare que o seu programa necessitar´a como ”printfs” os strings seguintes
"%d-IDLE\n"
"%d-P%d\n"
"TMC=%.1f\n"

## Samples

## Sample Input 1

3
0 3 3
1 2 2
3 1 1

## Sample Output 1

0-P1
1-P2
2-P2
3-P3
4-P1
5-P1
TMC=3.0

## Sample Input 2

5
1 5 2
1 4 4
2 3 3
4 1 2
10 2 1

## Sample Output 2

0-IDLE
1-P2
2-P3
3-P3
4-P4
5-P4
6-P3
7-P2
8-P2
9-P2
10-P5
11-P1
12-P1
TMC=5.8

## Sample Input 3

5
1 2 3
5 3 1
8 10 8
9 4 1
11 3 2

## Sample Output 3

0-IDLE
1-P1
2-P1
3-P1
4-IDLE
5-P2
6-IDLE
7-IDLE
8-P3
9-P4
10-P3
11-P5
12-P5
13-P3
14-P3
15-P3
16-P3
17-P3
18-P3
TMC=3.6

## Sugestão

Uma boa t´ecnica de resolu¸c˜ao ´e de similar o funcionamento dum sistema operativo !
Define uma estrutura de dados para representar os processos e os seus estados, um Processo Controlo
Bloco com campos para
• Numero de Processo (Process ID = PID)
• Tempo de Chegada
• Prioridade
• tempo de dura¸c˜ao inicial / Burst Time Inicial
• tempo de CPU restante (ainda para executar)
• ..etc

