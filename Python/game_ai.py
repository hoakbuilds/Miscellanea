# coding: utf8
from pprint import pprint
import copy
import random


# ------------------------------------------------------------------
def mostra_quatrolinha(T):
	tabuleiro = ''
	for x in range(9):
		
		if x == 4 or x == 8:
			tabuleiro += '  \n ' + str(T[x])
		else:
			tabuleiro += ' ' + str(T[x])
		
	print(tabuleiro)

# ------------------------------------------------------------------
def mostra_tabuleiro(T):
	tabuleiro = ''
	for x in range(9):
		
		if x == 3 or x == 6:
			tabuleiro += '  \n ' + str(T[x])
		else:
			tabuleiro += ' ' + str(T[x])
		
	print(tabuleiro)

# ------------------------------------------------------------------
# devolve a lista de ações que se podem executar partido de um estado
def acoes(T):
	resultado = []
	for x in range(9):
		if ( T[x] == 0):
			resultado.append(x)

	return resultado
	# IMPLEMENTAR

# ------------------------------------------------------------------
# devolve o estado que resulta de partir de um estado e executar uma ação
def resultado(T,a,jog):
	aux = copy.copy(T)
	if ( jog == 'MAX'):
		aux[a] = 1
	else:
		aux[a] = -1
	
	return aux

# ------------------------------------------------------------------
# existem 8 possíveis alinhamentos vencedores, para cada jogador
def utilidade(T):
	# testa as linhas
	ret = 0
	for i in (0,3,6):
		if ( T[i] == T[i+1] and T[i] == T[i+2] ):
			if T[i] == 0:
				if ret != 0:
					continue
				else:
					ret = 0
			elif T[i] == 1:
				ret = 1
			else:
				ret = -1
	# testa as colunas
	for i in (0,1,2):
		if ( T[i] == T[i+3] and T[i] == T[i+6] ):
			if T[i] == 0:
				if ret != 0:
					continue
				else:
					ret = 0
			elif T[i] == 1:
				ret
			else:
				ret = -1
	# testa as diagonais
	if ( T[0] == T[4] and T[0] == T[8] ):
		if T[0] == 0:
			if ret != 0:
				pass
			else:
				ret = 0
		elif T[0] == 1:
			ret = 1 
		else:
			ret = -1
	
	if ( T[2] == T[4] and T[4] == T[6] ):
		if T[2] == 0:
			if ret != 0:
				pass
			else:
				ret = 0
		elif T[2] == 1:
			ret = 1 
		else:
			ret = -1
	# não é nodo folha ou dá empate
	return ret

# ------------------------------------------------------------------
# devolve True se T é terminal, senão devolve False
def estado_terminal(T):
	x = utilidade(T)

	if ( x == 0 ):
		for x in range(9):
			if ( T[x] == 0 ):
				return(False)
	#print(x)
	return(True)


# ------------------------------------------------------------------
# algoritmo da wikipedia
# https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning
# ignoramos a profundidade e devolvemos o valor, a ação e o estado resultante
def alfabeta(T,alfa,beta,jog):
	if estado_terminal(T):
		return utilidade(T),-1,-1
	if jog:
		v = -10
		ba=-1
		for a in acoes(T):
			v1,ac,es = alfabeta(resultado(T,a,'MAX'),alfa,beta,True)
			if v1 > v: # guardo a ação que corresponde ao melhor
				v = v1
				ba=a
			alfa = max(alfa,v)
			if beta <= alfa:
				break
		return v,ba,resultado(T,ba,'MAX')
	else:
		v = -10
		ba=-1
		for a in acoes(T):
			v1,ac,es = alfabeta(resultado(T,a,'MIN'),alfa,beta,False)
			if v1 > v: # guardo a ação que corresponde ao melhor
				v = v1
				ba=a
			alfa = max(alfa,v)
			if beta <= alfa:
				break
		return v,ba,resultado(T,ba,'MIN')

# ------------------------------------------------------------------
def joga_max(T):
	v,a,e = alfabeta(T,-10,10,True)
	print('MAX joga para ' + str(a) + '\n') 
	return e

# ------------------------------------------------------------------
def joga_min(T):
	v,a,e = alfabeta(T,-10,10,False)
	print('MIN joga para ' + str(a) + '\n')
	return e
	# IMPLEMENTAR

# ------------------------------------------------------------------
def jogo(p1,p2):
	# cria tabuleiro vazio
	T = [0,0,0,0,0,0,0,0,0]
	jogada = 0
	# podemos partir de um estado mais "avançado"
	#T = [1,-1,0,0,-1,0,1,0,0]
	print("Inicio do jogo\n")
	mostra_tabuleiro(T)
	while acoes(T) != [] and not estado_terminal(T):
		jogada +=1
		print("Jogada " + str(jogada))
		T=p1(T)
		mostra_tabuleiro(T)
		if acoes(T) != [] and not estado_terminal(T):
			jogada +=1
			print("Jogada " + str(jogada))
			T=p2(T)
			mostra_tabuleiro(T)
	# fim
	if utilidade(T) == 1:
		print("Venceu o MAX\n\n")
	elif utilidade(T) == -1:
		print("Venceu o MIN\n\n")
	else:
		print("Empate\n\n")

def jogador(T, player_name, player):

	joga = 0

	while joga == 0:
			
		x = input("Onde deseja jogar?  ")

		if player == 1:
			aux = copy.copy(T)
			if aux[int(x)] == 0:
				aux[int(x)] = 1
				joga = 1
				print("Jogador '" + str(player_name) + "' jogou na casa " + str(x))
				return aux
			else:
				print("Essa casa já está ocupada.")
				continue
		else:
			aux = copy.copy(T)
			if aux[int(x)] == 0:
				aux[int(x)] = -1
				joga = 1
				print("Jogador '" + str(player_name) + "' jogou na casa " + str(x))
				return aux
			else:
				print("Essa casa já está ocupada.")
				continue


def jogo_pvp(player1,player2):
	# cria tabuleiro vazio
	T = [0,0,0,0,0,0,0,0,0]
	jogada = 0
	# podemos partir de um estado mais "avançado"
	#T = [1,-1,0,0,-1,0,1,0,0]
	print("\n\nInicio do jogo\n")
	mostra_tabuleiro(T)
	while utilidade(T) == 0:
		jogada +=1
		print("Jogada " + str(jogada) + ": " + str(player1) + " a jogar.")
		T=jogador(T, player1, 1)
		mostra_tabuleiro(T)
		if utilidade(T) == 0:
			jogada +=1
			print("Jogada " + str(jogada) + ": " + str(player2) + " a jogar.")
			T=jogador(T, player2, 2)
			mostra_tabuleiro(T)
		else:
			break
	# fim
	if utilidade(T) == 1:
		print("Venceu o " + str(player1) + "\n\n")
	elif utilidade(T) == -1:
		print("Venceu o " + str(player2) + "\n\n")
	else:
		print("Empate")

def jogo_pvai(player):
	# cria tabuleiro vazio
	T = [0,0,0,0,0,0,0,0,0]
	jogada = 0
	# podemos partir de um estado mais "avançado"
	#T = [1,-1,0,0,-1,0,1,0,0]
	print("\n\nInicio do jogo\n")
	mostra_tabuleiro(T)
	while utilidade(T) == 0:
		jogada +=1
		print("Jogada " + str(jogada))
		T=jogador(T, player, 2)
		mostra_tabuleiro(T)
		if ( T[6] == T[7] and T[7] == T[8] ):
			print(utilidade(T))
			if T[6] == 0:
				print("0") 
			elif T[7] == 1:
				print("1") 
			else:
				print("-1") 
		if utilidade(T) == 0 and acoes(T) != [] and not estado_terminal(T):
			jogada +=1
			print("Jogada " + str(jogada))
			T=joga_max(T)
			mostra_tabuleiro(T)
		else:
			break
	# fim
	if utilidade(T) == -1:
		print("Venceu o " + str(player) + "\n\n")
	elif utilidade(T) == 1:
		print("Venceu o MAX."  + "\n\n")
	else:
		print("Empate")


# ------------------------------------------------------------------
# jogador aleatório
def joga_rand(T):
	x = jogada_rand()
	while True:
		if  ( T[x] == 0 ):
			T = resultado(T, x, 'RAND')
			break
		else:
			x = jogada_rand()
	# COMPLETAR
	print('  RAND joga para ',x)
	return T

# sortear jogada do rand
def jogada_rand():
	return(random.randint(0,8))
# ------------------------------------------------------------------

def player_vs_player():
	print("Nome do Jogador 1:")
	player1 = input(">> ")
	print("Nome do Jogador 2:")
	player2 = input(">> ")
	jogo_pvp(player1, player2)
	return

def player_vs_ai():
	print("Nome do Jogador:")
	player1 = input(">> ")
	jogo_pvai(player1)
	return

def ai_vs_ai():
	jogo(joga_max, joga_min)
	return

def ai_vs_rand():
	jogo(joga_max, joga_rand)
	return

def main():
	games = [
		" - - - J O G O   D O   G A L O - - - ",
		" - - - Q U A T R O   E M   L I N H A - - - " 
	]
	gameOptions = [
		[
			{ 
				"1 - Jogo PvP " : player_vs_player
			},
			{ 
				"2 - Jogo PvAI " : player_vs_ai
			},
			{ 
				"3 - Jogo AIvAI " : ai_vs_ai
			},
			{ 
				"4 - Jogo AIvRAND " : ai_vs_rand
			}

		],
		[
			{ 
				"5 - Jogo PvP " : player_vs_player
			},
			{ 
				"6 - Jogo PvAI " : player_vs_ai
			},
			{ 
				"7 - Jogo AIvAI " : ai_vs_ai
			},
			{ 
				"8 - Jogo AIvRAND " : ai_vs_rand
			}
		]
	]
	while True:	
		for idgame, game in enumerate(games):
			print(game)
			for option in gameOptions[idgame]:
				for key, value in option.items():
					print(key)
	
		x = input(">> ")

		try:
			if int(x) < 0: 
				raise ValueError
            # Call the matching function
			if int(x) > 0 and int(x) < 5:
				for index, item in enumerate(gameOptions[0]):
					if ((index + 1) == int(x)):
						list(gameOptions[0][index].values())[0]()
			elif int(x) > 4 and int(x) < 9:
				for index, item in enumerate(gameOptions[1]):
					if ((index + 1) == (int(x)-4)):
						list(gameOptions[1][index].values())[0]()
			else:
				continue
		except (ValueError, IndexError):
			pass


main()
# deve ganhar sempre o max:
#jogo(joga_max,joga_rand)
# devem empatar sempre:
#jogo(joga_max,joga_min)


