/*
 * regra.cpp
 *
 *  Created on: 17 de mai de 2017
 *      Author: aluno
 */

#include "regra.h"

namespace p3 {

Regra::Regra(std::size_t numero_de_jogadores,
			 int cartas_jogadores,
			 int rodadas /* = -1 */,
			 int pontuacao_max /* = -1 */, 
			 int menor_pontuacao /* = -1 */,
			 int cartas_inicial /* = 52 */,
			 modo_fim fim /* = modo_fim::pontuacao */, 
			 condicao_vitoria vit /* = condicao_vitoria::maior_pontuacao */, 
			 condicao_derrota der /* = condicao_derrota::nenhuma */) : _fim(fim), _vit(vit), _der(der){
	
	_numero_de_jogadores = numero_de_jogadores;
	_cartas_inicial = cartas_inicial;
	_cartas_jogadores = cartas_jogadores;
	_rodadas = rodadas;
	_pontuacao_max = pontuacao_max;
	_menor_pontuacao = menor_pontuacao;
}

Regra::~Regra() {

}

std::size_t Regra::numero_de_jogadores() const {
	return _numero_de_jogadores;
}
int Regra::cartas_inicial() const {//retorna numero de cartas do monte
	return _cartas_inicial;
}
int Regra::cartas_jogadores() const { //retorna cartas iniciais por jogadores
	return  _cartas_jogadores;
}
int Regra::max_rodadas() const {//retorna numero maximo de rodadas
	return _rodadas;
}
int Regra::pontuacao_max() const {//retorna numero de pontos para termino
	return _pontuacao_max;
}

Regra::modo_fim Regra::fim() const {

	return _fim;
}

Regra::condicao_vitoria Regra::cond_vit() const {

	return _vit;
}

Regra::condicao_derrota Regra::cond_der() const {

	return _der;
}

bool Regra::checa_fim_rodada(std::size_t _jog_atual){
}

std::size_t Regra::jogador_comeca(){
}

void Regra::jogador_comeca(std::size_t _comeca){
}
	
std::size_t Regra::jogador_comeca_turno(){
}
	
void Regra::jogador_comeca_turno(std::size_t _comeca_turno){}
	
std::size_t Regra::jogador_termina(){}
	
void Regra::jogador_termina(std::size_t _termina){}

int Regra::compara(p3::Carta c1,p3::Carta c2,p3::Carta _vira){}

void Regra::jogador_ganhou_rodada(std::size_t _jogador, std::size_t _rodada){}

bool Regra::fim_turno(std::size_t _rodada){}

std::size_t Regra::jogador_ganhou_turno(std::size_t _rodada){}



} /* namespace p3 */
