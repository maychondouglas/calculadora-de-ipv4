#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;
void menuPrincipal();
void enderecamentoComClasse();
void enderecamentoSemClasseMascaraNotacaoDecimal();
void enderecamentoSemClasseMascaraNotacaoCIDR();
bool validarIP(int a, int b, int c, int d);
int  *convertendoParaBinario(int number);
int  converterParaDecimal(int *vetor, int inteiro);


int main(){
	
	menuPrincipal();
}

void menuPrincipal(){
	int opcao = 0;
	do{
	
	cout<<"************* Menu Principal *************";
	cout<<"\nEscolha uma das opcoes abaixo: \n";
	cout<<"1. Calculo de Enderecamento COM Classes: \n";
	cout<<"2. Calculo de Enderecamento SEM Classes - Mascara na Notacao Decimal: \n";
	cout<<"3. Calculo de Enderecamento SEM Classes - Mascara na Notacao CIDR: \n";
	cout<<"Digite o numero conrespondente a opcao desejada: ";
	cin>>opcao;
	
	if(opcao<1 || opcao>3){
		system("cls");
		cout<<"\nDigite uma opcao valida!!!\n";
	}
	}	
	while(opcao<1 || opcao>3);
	
	switch(opcao){
		case 1:
			enderecamentoComClasse();
			break;
		case 2:
			enderecamentoSemClasseMascaraNotacaoDecimal();
			break;
		case 3:
			enderecamentoSemClasseMascaraNotacaoCIDR();
			break;
		default:
			break;
	}
	
}

bool validarIP(int a, int b, int c, int d){
	return !((a<0 || a>255)||(b<0 || b>255)||(c<0 || c>255)||(d<0 || d>255));
}

void enderecamentoComClasse(){
	system("cls");
	int x = 0, y = 0, z = 0, t = 0;
	
	//RECEBENDO ENDERECO IP
	do{
		cout<<"\n************* Enderecamento COM Classe *************";
		cout<<"\nDigite o IPv4 separado por espacos: Ex: 192 168 0 1\n";
		cin>> x;
		cin>> y;
		cin>> z;
		cin>> t;
		
		if(!validarIP(x, y, z, t)){
			system("cls");
			cout<<"\nDigite um IP valido!!!\n";
		}
	}while(!validarIP(x, y, z, t));
	
	//VERIFICANDO A CLASSE
	string classe = "";
	string mascaraDecimal = "";
	int mascaraCIDR = 0;
	int numeroDeHosts = 0;
	int enderecoRede[] = {x, y, z, 0};
	int enderecoBroadcast[] = {x, y, z, 255};
	int primeiroEnderecoUtilizavel[] = {x, 0, 0, 1};
	int ultimoEnderecoUtilizavel[] ={x, 255, 255, 254};
	
	int a = x;
	if(a<=127){
		classe = "A";
		mascaraDecimal = "255.0.0.0";
		mascaraCIDR = 8;
		numeroDeHosts = pow(2, (32-mascaraCIDR)) - 2;
		enderecoRede[1] = 0;
		enderecoRede[2] = 0;
		enderecoRede[3] = 0;
		enderecoBroadcast[1] = 255;
		enderecoBroadcast[2] = 255;
		enderecoBroadcast[3] = 255;
		
	}else{
		if(a<=191){
			classe = "B";
			mascaraDecimal = "255.255.0.0";
			mascaraCIDR = 16;
			numeroDeHosts = pow(2, (32-mascaraCIDR)) - 2;
			enderecoRede[2] = 0;
			enderecoRede[3] = 0;
			enderecoBroadcast[2] = 255;
			enderecoBroadcast[3] = 255;
			primeiroEnderecoUtilizavel[1] = y;
			ultimoEnderecoUtilizavel[1] = y;

		}else{
			if(a<=223){
				classe = "C";
				mascaraDecimal = "255.255.255.0";
				mascaraCIDR = 24;
				numeroDeHosts = pow(2, (32-mascaraCIDR)) - 2;
				primeiroEnderecoUtilizavel[1] = y;
				primeiroEnderecoUtilizavel[2] = z;
				ultimoEnderecoUtilizavel[1] = y;
				ultimoEnderecoUtilizavel[2] = z;
			}else{
				if(a<=239){
					classe = "D";
				}else{
					classe = "E";
				}
			}
		}
	}
	system("cls");
	cout<<"\n************* Enderecamento COM Classe *************\n";
	//REALIZANDO IMPRESSAO DOS DADOS
	if(classe!="D" && classe!="E"){

		cout<<"\nIP Digitado: "<<x<<"."<<y<<"."<<z<<"."<<t;
		cout<<"\nClasse: "<<classe;
		cout<<"\nMascara na notacao Decimal: "<<mascaraDecimal;
		cout<<"\nMascara na notacao CIDR: /"<<mascaraCIDR;
		cout<<"\nNumero de Host's por rede (descontando IP's de Rede e de Broadcast): "<<numeroDeHosts;
		cout<<"\nEndereco de Rede: "<<enderecoRede[0]<<"."<<enderecoRede[1]<<"."<<enderecoRede[2]<<"."<<enderecoRede[3];
		cout<<"\nEndereco de Broadcast: "<<enderecoBroadcast[0]<<"."<<enderecoBroadcast[1]<<"."<<enderecoBroadcast[2]<<"."<<enderecoBroadcast[3];
		cout<<"\nPrimeiro Endereco de Host Utilizavel no Bloco: "<<primeiroEnderecoUtilizavel[0]<<"."<<primeiroEnderecoUtilizavel[1]<<"."<<primeiroEnderecoUtilizavel[2]<<"."<<primeiroEnderecoUtilizavel[3];
		cout<<"\nUltimo Endereco de Host Utilizavel no Bloco: "<<ultimoEnderecoUtilizavel[0]<<"."<<ultimoEnderecoUtilizavel[1]<<"."<<ultimoEnderecoUtilizavel[2]<<"."<<ultimoEnderecoUtilizavel[3];
		
	}else{
		cout<<"\nIP Digitado: "<<x<<"."<<y<<"."<<z<<"."<<t;
		cout<<"\nPertence a Classe: "<<classe;
	}
	cout<<"\n\nDigite uma das opcoes abaixo: \n0. Voltar ao MENU PRINCIPAL \n1. Calcular outro IP COM CLASSE \n2. Fechar\n";
		int op = 0;
		cin>>op;
		
		switch(op){
			case 0:
				menuPrincipal();
				break;
			case 1:
				enderecamentoComClasse();
				break;
			default:
				system("exit");
		}
}

void enderecamentoSemClasseMascaraNotacaoDecimal(){

	system("cls");
	int x = 0, y = 0, z = 0, t = 0;
	
	//RECEBENDO ENDERECO IP
	do{
		cout<<"************* Enderecamento SEM Classe *************\n";
		cout<<"***********   (mascara Notacao Decimal)  ************\n";
		cout<<"\nDigite o IPv4 separado por espacos: Ex: 192 168 0 1\n";
		cin>> x;
		cin>> y;
		cin>> z;
		cin>> t;
		
		if(!validarIP(x, y, z, t)){
			system("cls");
			cout<<"\nDigite um IP valido!!!\n";
		}
	}while(!validarIP(x, y, z, t));
	
	//RECEBENDO A MASCARA NA NOTACAO DECIMAL
	int xM = 0, yM = 0, zM = 0, tM = 0;
	do{
		cout<<"\nDigite a mascara da Rede em notacao DECIMAL separa por espacos, Ex: 255 192 0 0\n";
		cin>> xM;
		cin>> yM;
		cin>> zM;
		cin>> tM;
		
		if(convertendoParaBinario(xM)[0]!=1){
			system("cls");
			cout<<"\nDigite uma Mascara valida!!!\n";
		}
	}while(convertendoParaBinario(xM)[0]!=1);
	
	//TRANSFORMANDO A MASCARA EM BINARIO, PARA IDENTIFICAR A NOTACAO EM CIDR
	int *xMB = convertendoParaBinario(xM);
	int *yMB = convertendoParaBinario(yM);
	int *zMB = convertendoParaBinario(zM);
	int *tMB = convertendoParaBinario(tM);
	
	int *xB = convertendoParaBinario(x);
	int *yB = convertendoParaBinario(y);
	int *zB = convertendoParaBinario(z);
	int *tB = convertendoParaBinario(t);
	
	//UNINDO OS VETORES IP E MASCARA BINARIA EM UM SO VETOR, CALCULANDO A MASCARA INVERTIDA, CALCULANDO A MASCARA CIDR;
	int mascaraBinaria[32], mascaraInvertida[32], p = 0, ipBinario[32];
	for(int i = 0; i<8; i++){
		//MASCARA
		mascaraBinaria[i] = xMB[i];
		
		//IP
		ipBinario[i] = xB[i];
				
		//CALCULANDO MASCARA CIDR
		if(mascaraBinaria[i]==0 && mascaraBinaria[i-1]==1){
			p = i;
		}
		
		//GERANDO MASCARA INVERTIDA
		if(xMB[i]==0) mascaraInvertida[i]=1;
		else mascaraInvertida[i]=0;
		
	}
	for(int i = 8, j = 0; j< 8; i++, j++){
		//MASCARA
		mascaraBinaria[i] = yMB[j];
		//IP
		ipBinario[i] = yB[j];
		
		//CALCULANDO MASCARA CIDR
		if(mascaraBinaria[i]==0 && mascaraBinaria[i-1]==1){
			p = i;
		}
		
		//GERANDO MASCARA INVERTIDA
		if(yMB[j]==0) mascaraInvertida[i]=1;
		else mascaraInvertida[i]=0;
	}
	for(int i = 16, j = 0; j < 8; i++, j++){
		//MASCARA 
		mascaraBinaria[i] = zMB[j];
		//IP
		ipBinario[i] = zB[j];
		
		//CALCULANDO MASCARA EM CIDR
		if(mascaraBinaria[i]==0 && mascaraBinaria[i-1]==1){
			p = i;
		}
		
		//GERANDO MASCARA INVERTIDA
		if(zMB[j]==0) mascaraInvertida[i]=1;
		else mascaraInvertida[i]=0;
	}
	for(int i = 24, j = 0; j < 8; i++, j++){
		
		//MASCARA
		mascaraBinaria[i] = tMB[j];
		
		//IP
		ipBinario[i] = tB[j];
		
		//CALCULANDO MASCARA EM CIDR
		if(mascaraBinaria[i]==0 && mascaraBinaria[i-1]==1){
			p = i;
		}
		
		//GERANDO MASCARA INVERTIDA
		if(tMB[j]==0) mascaraInvertida[i]=1;
		else mascaraInvertida[i]=0;
	}
	
	
	//FAZER OPERAÇÃO OR ENTRE O IP E A MASCARA NEGADA(INVERTIDA) PARA OBTER O BROADCAST
	int ipBroadcast[32];
	for(int i = 0; i<32; i++){
		ipBroadcast[i] = (mascaraInvertida[i] | ipBinario[i]);
	}
	
	
	int broadcastX = 0, broadcastY = 0, broadcastZ = 0, broadcastT = 0;
	broadcastX = converterParaDecimal(ipBroadcast, 0);
	broadcastY = converterParaDecimal(ipBroadcast, 8);
	broadcastZ = converterParaDecimal(ipBroadcast, 16);
	broadcastT = converterParaDecimal(ipBroadcast, 24); 
	
	//MASCARA CIDR
	int mascaraCIDR = p;
	
	//CALCULANDO NUMERO DE HOSTS
	int numeroDeHosts = pow(2, (32-mascaraCIDR))-2;
	
	//PARA ENCONTRAR O ENDERECO DE REDE UTILIZAREI A OPERACAO AND ENTRE O ENDERECO E A MASCARA DECIMAL
	int enderecoRede[] = {x & xM, y & yM, z & zM, t & tM};
	
	//PARA ENCONTRAR O PRIMEIRO ENDERECO DO BLOCO UTILIZAVEL, SOMA-SE 1 NO ULTIMO OCTETO DO ENDERECO DE REDE
	int primeiroEnderecoUtilizavel[] = {x&xM, y&yM, z&zM, (t&tM)+1};
	
	
	
	
	//IMPRIMINDO OS RESULTADOS
	cout<<"\nIP Digitado: "<<x<<"."<<y<<"."<<z<<"."<<t;
	cout<<"\nMascara na notacao CIDR: /"<<mascaraCIDR;
	cout<<"\nNumero de Host's por rede (descontando IP's de Rede e de Broadcast): "<<numeroDeHosts;
	cout<<"\nEndereco de Rede: "<<enderecoRede[0]<<"."<<enderecoRede[1]<<"."<<enderecoRede[2]<<"."<<enderecoRede[3];
	cout<<"\nEndereco de Broadcast: "<<broadcastX<<"."<<broadcastY<<"."<<broadcastZ<<"."<<broadcastT;
	cout<<"\nPrimeiro Endereco de Host Utilizavel no Bloco: "<<primeiroEnderecoUtilizavel[0]<<"."<<primeiroEnderecoUtilizavel[1]<<"."<<primeiroEnderecoUtilizavel[2]<<"."<<primeiroEnderecoUtilizavel[3];
	//PARA ENCONTRAR O PRIMEIRO ENDERECO DO BLOCO UTILIZAVEL, SUBTRAI 1 NO ULTIMO OCTETO DO ENDERECO DE BROADCAST;
	cout<<"\nUltimo Endereco de Host Utilizavel no Bloco: "<<broadcastX<<"."<<broadcastY<<"."<<broadcastZ<<"."<<broadcastT-1;
	
	cout<<"\n\nDigite uma das opcoes abaixo: \n0. Voltar ao MENU PRINCIPAL \n1. Calcular outro IP SEM CLASSE COM MASCARA NA NOTACAO DECIMAL \n2. Fechar\n";
		int op = 0;
		cin>>op;
		
		switch(op){
			case 0:
				menuPrincipal();
				break;
			case 1:
				enderecamentoSemClasseMascaraNotacaoDecimal();
				break;
			default:
				system("exit");
		}
}	


void enderecamentoSemClasseMascaraNotacaoCIDR(){
	
	system("cls");
	int x = 0, y = 0, z = 0, t = 0, cidr = 0;
	
	//RECEBENDO ENDERECO IP e a MASCARA CIDR
	do{
		cout<<"************* Enderecamento SEM Classe *************\n";
		cout<<"***********   (mascara Notacao CIDR)  ************\n";
		cout<<"\nDigite o IPv4 separado por espacos: Ex: 192 168 0 1\n";
		cin>> x;
		cin>> y;
		cin>> z;
		cin>> t;
		cout<<"\nDigite a MASCARA na notacao CIDR: \n";
		cin>> cidr;
		
		if(!validarIP(x, y, z, t)){
			system("cls");
			cout<<"\nDigite um IP valido!!!\n";
		}
		if(cidr<1 || cidr>31){
			system("cls");
			cout<<"\nDigite uma MASCARA em CIDR valida!!!\n";
		}
		
	}while(!validarIP(x, y, z, t) || (cidr<1 || cidr>31));
	
	//GERANDO A MASCARA em BINARIO PARA PASSAR PARA NOTACAO DECIMAL
	//
	int *mascaraBinario = new int [32];
	for(int i = 0; i<32; i++){
		if(i<cidr){
			mascaraBinario[i] = 1;
		}else{
			mascaraBinario[i] = 0;
		}
	}
	/////PASSANDO MASCARA PARA DECIMAL
	int xM = converterParaDecimal(mascaraBinario, 0);
	int yM = converterParaDecimal(mascaraBinario, 8);
	int zM = converterParaDecimal(mascaraBinario, 16);
	int tM = converterParaDecimal(mascaraBinario, 24);
	
	//CALCULANDO A MASCARA INVERTIDA;
	
	int *xB = convertendoParaBinario(x);
	int *yB = convertendoParaBinario(y);
	int *zB = convertendoParaBinario(z);
	int *tB = convertendoParaBinario(t);
	
	
	int mascaraInvertida[32], ipBinario[32];
	
	for(int i = 0, j = 0; i < 32; i++, j++){
		if(i == 8 || i == 16 || i == 24){
			j = 0;
		}
		
		//UNINDO OS 4 VETORES DO IP BINARIO EM UM UNICO VETOR DE 32 BITS
		if(i < 8){
				ipBinario[i] = xB[j];
			}
			else{
				if(i <16) {
					ipBinario[i] = yB[j];
				}
				else{
					if(i < 24){
						ipBinario[i] = zB[j];
					}else{
						ipBinario[i] = tB[j];
					}
				}
			}
			
		//GERANDO MASCARA INVERTIDA
		if(mascaraBinario[i]==0) mascaraInvertida[i]=1;
		else mascaraInvertida[i]=0;
	}
	
	//FAZER OPERAÇÃO OR ENTRE O IP E A MASCARA NEGADA(INVERTIDA) PARA OBTER O BROADCAST
	int ipBroadcast[32];
	for(int i = 0; i<32; i++){
		ipBroadcast[i] = (mascaraInvertida[i] | ipBinario[i]);
	}
	
	
	int broadcastX = 0, broadcastY = 0, broadcastZ = 0, broadcastT = 0;
	broadcastX = converterParaDecimal(ipBroadcast, 0);
	broadcastY = converterParaDecimal(ipBroadcast, 8);
	broadcastZ = converterParaDecimal(ipBroadcast, 16);
	broadcastT = converterParaDecimal(ipBroadcast, 24); 
	
	//NUMERO DE HOST'S DESCONTANDO REDE E BROADCAST
	int n = pow(2, 32 - cidr) - 2 ;
	
	//PARA ENCONTRAR O ENDERECO DE REDE UTILIZAREI A OPERACAO AND ENTRE O ENDERECO E A MASCARA DECIMAL
	int enderecoRede[] = {x & xM, y & yM, z & zM, t & tM};
	
	//PARA ENCONTRAR O PRIMEIRO ENDERECO DO BLOCO UTILIZAVEL, SOMA-SE 1 NO ULTIMO OCTETO DO ENDERECO DE REDE
	int primeiroEnderecoUtilizavel[] = {x&xM, y&yM, z&zM, (t&tM)+1};
	
	
	
	
	//IMPRIMINDO OS RESULTADOS
	cout<<"\nIP Digitado: "<<x<<"."<<y<<"."<<z<<"."<<t;
	cout<<"\nMascara na notacao DECIMAL: \n"<<xM<<"."<<yM<<"."<<zM<<"."<<tM;
	cout<<"\nNumero de Host's por rede (descontando IP's de Rede e de Broadcast): "<<n;
	cout<<"\nEndereco de Rede: "<<enderecoRede[0]<<"."<<enderecoRede[1]<<"."<<enderecoRede[2]<<"."<<enderecoRede[3];
	cout<<"\nEndereco de Broadcast: "<<broadcastX<<"."<<broadcastY<<"."<<broadcastZ<<"."<<broadcastT;
	cout<<"\nPrimeiro Endereco de Host Utilizavel no Bloco: "<<primeiroEnderecoUtilizavel[0]<<"."<<primeiroEnderecoUtilizavel[1]<<"."<<primeiroEnderecoUtilizavel[2]<<"."<<primeiroEnderecoUtilizavel[3];
	//PARA ENCONTRAR O PRIMEIRO ENDERECO DO BLOCO UTILIZAVEL, SUBTRAI 1 NO ULTIMO OCTETO DO ENDERECO DE BROADCAST;
	cout<<"\nUltimo Endereco de Host Utilizavel no Bloco: "<<broadcastX<<"."<<broadcastY<<"."<<broadcastZ<<"."<<broadcastT-1;
	
	cout<<"\n\nDigite uma das opcoes abaixo: \n0. Voltar ao MENU PRINCIPAL \n1. Calcular outro IP SEM CLASSE COM MASCARA NA NOTACAO CIDR \n2. Fechar\n";
		int op = 0;
		cin>>op;
		
		switch(op){
			case 0:
				system("cls");
				menuPrincipal();
				break;
			case 1:
				enderecamentoSemClasseMascaraNotacaoCIDR();
				break;
			default:
				system("exit");
		}

}

int  *convertendoParaBinario(int number){
	int x = number;
	int *b = new int[7];
	for(int i = 7; i >= 0 ; i--){

        if(x >= 1){
            b[i] = (x%2);
            x /= 2;
        }
        else{
            b[i] = 0;
        }
    }
	
	return b;
}

int  converterParaDecimal(int *ipBroadcast, int inicio){
	
	//CONVERTER BINARIO DE 8 BITS PARA DECIMAL
	int j = inicio+7; 
	int inteiro =0;
	
	for(int i = 0; i < 8; i++){
		
		if(ipBroadcast[j] == 1 ){
			
			inteiro += pow(2, i);
		}
		
		j--;
	}
	
	return inteiro;
}
