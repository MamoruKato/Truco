/*
 * RegraTruco.cpp
 *
 *  Created on: 24 de mai de 2017
 *      Author: bruno
 */


#include "regratruco.h"

namespace p4{

Regra_Truco::Regra_Truco(std::size_t numero_de_jogadores,
		  int cartas_jogadores,
		  int rodadas,
		  int pontuacao_max,
		  int menor_pontuacao,
		  int cartas_inicial):p3::Regra(numero_de_jogadores,cartas_jogadores,rodadas,pontuacao_max,
				  menor_pontuacao,cartas_inicial){

	if(numero_de_jogadores != 2 && numero_de_jogadores != 4){
		throw std::invalid_argument("numero de jogadores invalido");
	}

	std::random_device rd;
	std::mt19937 g(rd());
	std::uniform_int_distribution<std::size_t> x(0,numero_de_jogadores -1);

	_jogador_comeca_turno  = x(g);
	_jogador_comeca = _jogador_comeca_turno;
	
	if(_jogador_comeca == 0){
		_jogador_termina = numero_de_jogadores;
	}
	else{
		_jogador_termina = _jogador_comeca;
	}

	for(auto i = 0; i < rodadas; i++){
		_jogadores_ganharam.push_back(numero_de_jogadores);
	}
}

Regra_Truco::~Regra_Truco(){
}

bool Regra_Truco::checa_fim_rodada(std::size_t _jog_atual){
	if(_jog_atual == _jogador_termina){
		return true;
	}
	
	else{
		return false;
	}
}

std::size_t Regra_Truco::jogador_comeca(){
	return _jogador_comeca;
}

void Regra_Truco::jogador_comeca(std::size_t _comeca){
	if(_comeca > numero_de_jogadores()){
		return;
	}
	else{
		_jogador_comeca = _comeca;
	}
}

std::size_t Regra_Truco::jogador_comeca_turno(){
	return _jogador_comeca_turno;
}

void Regra_Truco::jogador_comeca_turno(std::size_t _comeca_turno){
	if(_comeca_turno > numero_de_jogadores()) return;
	else{
		_jogador_comeca_turno = _comeca_turno;
	}
}

std::size_t Regra_Truco::jogador_termina(){
	return _jogador_termina;
}

void Regra_Truco::jogador_termina(std::size_t _termina){
	if(_termina > numero_de_jogadores()) return;
	else{
		_jogador_termina = _termina;
	}
}

int Regra_Truco::compara(p3::Carta c1, p3::Carta c2,p3::Carta _vira){
	if(_vira.numero() == 10){
		return compara_vira_12(c1,c2);
	}
	else{
		if(c1.numero() == _vira.numero() + 1 && c2.numero() == _vira.numero() + 1){
			if(compara_naipe(c1,c2) == true){
				return (int)(Compara::Maior);
			}
			else{
				return (int)(Compara::Menor);
			}
		}
		else if(c1.numero() == _vira.numero() + 1){
			return (int)(Compara::Maior);
		}
		else if(c2.numero() == _vira.numero() + 1){
			return (int)(Compara::Menor);
		}
		else{
			return compara_valor(c1,c2);
		}
	}
}

void Regra_Truco::jogador_ganhou_rodada(std::size_t _jogador, std::size_t _rodada){
	if(_jogador >= numero_de_jogadores()){
		_jogadores_ganharam[_rodada] = 2;
	}
	else{
		_jogadores_ganharam[_rodada] = _jogador % 2;
		return;
	}
}

bool Regra_Truco::fim_turno(std::size_t _rodada){
	int cont1 = 0, cont2 = 0,cont3 = 0;
	for(int i = 0; i <	(int)_rodada; i++){
		if(_jogadores_ganharam[i] == 0){
			cont1 ++;
		}
		else if(_jogadores_ganharam[i] == 1){
			cont2 ++;
		}
		else if(_jogadores_ganharam[i] == 2){
			cont3 ++;
		}
	}
	if (_rodada == 3 || cont1 == 2 || cont2 == 2 || (cont3 == 1 && (cont2 == 1 || cont1 == 1))){
		return true;
	}
	else{
		return false;
	}

}

std::size_t Regra_Truco::jogador_ganhou_turno(std::size_t _rodada){
	if(_jogadores_ganharam[0] == 2 && _jogadores_ganharam[1] != _jogadores_ganharam[0]){
		std::size_t vencedor = _jogadores_ganharam[1];
		for(int i; i < (int)_rodada; i++){
			_jogadores_ganharam[i] = 3;
		}
		_rodada = 0;
		return vencedor;
	}
	else{
		int cont1 = 0,cont2 = 0,cont3 = 0;
		for(int i = 0; i < (int)_rodada ;i++){
			if(_jogadores_ganharam[i] == 0){
				cont1 ++;
			}
			else if(_jogadores_ganharam[i] == 1){
				cont2 ++;
			}
			else if(_jogadores_ganharam[i] == 2){
				cont3 ++;
			}
		}
		if(cont1 > cont2){
			for(int i; i <(int)_rodada; i++){
				_jogadores_ganharam[i] = 3;
			}
			_rodada = 0;
			return 0;
		}
		else if(cont2 > cont1){
			for(int i; i < (int)_rodada; i++){
				_jogadores_ganharam[i] = 3;
			}
			_rodada = 0;
			return 1;
		}
		else if(cont3 == 3){
			for(int i; i < (int)_rodada; i++){
				_jogadores_ganharam[i] = 3;
			}
			_rodada = 0;
			return 2;
		}
		else if(cont1 == cont2){
			for(int i; i <(int)_rodada; i++){
				_jogadores_ganharam[i] = 3;
			}
			_rodada = 0;
			return _jogadores_ganharam[0];
		}
	}
	return 3;
}




//Funcoes privadas

bool Regra_Truco::compara_naipe(p3::Carta c1,p3::Carta c2){
	if(c1.naipe() == p3::Carta::Naipe::Paus){
		return true;
	}
	else if(c1.naipe() == p3::Carta::Naipe::Copas){
		if(c2.naipe() == p3::Carta::Naipe::Paus){
			return false;
		}
		else{
			return true;
		}
	}
	else if(c1.naipe() == p3::Carta::Naipe::Espadas){
		if(c2.naipe() == p3::Carta::Naipe::Copas || c2.naipe() ==p3::Carta::Naipe::Paus){
			return false;
		}
		else{
			return true;
		}
	}
	else{
		return false;
	}
}

int Regra_Truco::compara_vira_12(p3::Carta c1,p3::Carta c2){
	if(c1.numero() == 1 && c2.numero() == 1){
		if(compara_naipe(c1,c2) == true){
			return (int)(Compara::Maior);
		}
		else{
			return (int)(Compara::Menor);
		}
	}
	else if(c1.numero() == 1 && c2.numero() != 1){
		return (int)(Compara::Maior);
	}
	else if(c2.numero() == 1 && c1.numero() != 1){
		return (int)(Compara::Menor);
	}
	else{
		return compara_valor(c1,c2);
	}
}

int Regra_Truco::compara_valor(p3::Carta c1 , p3::Carta c2){
	if((c1.numero() == 3 || c1.numero() == 2 || c1.numero() == 1) &&
			(c2.numero() == 3 || c2.numero() == 2 || c2.numero() == 1)){
		if(c1.numero() > c2.numero()){
			return (int)(Compara::Maior);
		}
		else if(c1.numero() == c2.numero()){
			return (int)(Compara::Igual);
		}
		else{
			return (int)(Compara::Menor);
		}
	}
	else if(c1.numero() == 3 || c1.numero() == 2 || c1.numero() == 1){
		if(c2.numero() != 3 && c2.numero() != 2 && c2.numero() != 1){
			return (int)(Compara::Maior);
		}
	}
	else if(c2.numero() == 3 || c2.numero() == 2 || c2.numero() == 1){
		if(c1.numero() != 3 && c1.numero() != 2 && c1.numero() != 1){
			return (int)(Compara::Menor);
		}
	}
	else{
		if(c1.numero() > c2.numero()){
			return (int)(Compara::Maior);
		}
		else if(c1.numero() == c2.numero()){
			return (int)(Compara::Igual);
		}
		else{
			return (int)(Compara::Menor);
		}
	}
	return -1;
}



}
 /* namespace p4 */
