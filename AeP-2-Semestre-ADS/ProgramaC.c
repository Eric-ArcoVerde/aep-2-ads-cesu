//#include <array>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#define CADASTRO_MAX 100


struct cadastro
{
	char escola[100]; 
	char tema[100]; 
	char data[11]; 
	char publicoAlvo[100];
	char responsavel[100]; 
	int participantes; 
	char sitAtv[10];
	char codigo[100]; //colocar validacao de duplicidade
	bool vazio;

} cadastros[CADASTRO_MAX];

struct stringRet
{
	char string[50];
};

void Clear_Buffer() //limpa o buffer do teclado
{
	int c = 0;
	while((c = getchar()) != EOF && c != '\n'){}
	return;
}

void read(char destino[], int tamanho) //novo scanf feito para ler de uma forma mais dinamica
{

	if(fgets(destino, tamanho, stdin) == NULL)
	{
		destino[0] = '\0';
		return;
	}

	size_t fim = strcspn(destino, "\n");

	if(destino[fim] == '\n')
	{
		destino[fim] = '\0';
	}
	else 
	{
		Clear_Buffer();
	}

}

void Cadastrar_Acao()
{
	//variaveis para guardar os valores antes de salvarem eles
	char escolaRg[100]; 
	char temaRg[100]; 
	char dataRg[11]; 
	char publicoAlvoRg[100];
	char responsavelRg[100]; 
	int participantesRg; 
	char sitAtvRg[10];
	char codigoRg[100];
	
	int indexLivre;
	char resposta[4];

	//checagem de qual o proximo index livre
	for(int i = 0; i < CADASTRO_MAX; i++)
	{
		if(cadastros[i].vazio == true)
		{
			indexLivre = i;
			break;	
		}
	}
		//revisar
	 	
	printf("digite o nome da escola\n:");
	read(escolaRg, 100); 
	 	
	 	

	printf("digite o tema \n:");
	read(temaRg, 100);
		
	 	

	printf("digite a data de previsao para acontecer a acao, no formato DD/MM/AAAA\n:");
	read(dataRg, 11);
		


	printf("digite o publico alvo\n:");
	read(publicoAlvoRg, 100);
	 	


	printf("digite o nome do responsavel pela acao\n:");
	read(responsavelRg, 100);
	 	


	printf("digite o numero de participantes\n:");
	scanf(" %d", &participantesRg);
		
	Clear_Buffer();


	printf("Qual a situacao da atividade? (realizada/planejada/cancelada)\n:");
	while(true)
	{
		
		read(sitAtvRg, 10);
		
		if(strcmp(sitAtvRg, "realizada") == 0 || strcmp(sitAtvRg, "Realizada") == 0)
		{
			strcpy(sitAtvRg, "Realizada");
			break;
		}
		else if(strcmp(sitAtvRg, "planejada") == 0 || strcmp(sitAtvRg, "Planejada") == 0) 
		{
			strcpy(sitAtvRg, "Planejada");
			break;
		}
		else if(strcmp(sitAtvRg, "cancelada") == 0 || strcmp(sitAtvRg, "Cancelada") == 0)
		{
			strcpy(sitAtvRg, "Cancelada");
			break;
		}
		else {
			printf("valor invalido, digite um dos valores validos: realizada/planejada/cancelada\n");
		}
	}

	printf("coloque o codigo da ação\n:");
	read(codigoRg, 100);
	 	

	printf("escola: %s \ntema: %s\ndata prevista: %s\npublico alvo: %s\nresponsavel pela acao: %s\nnumero de participantes: %d\nsituacao: %s\ncodigos: %s\n", escolaRg, temaRg, dataRg, publicoAlvoRg, responsavelRg, participantesRg, sitAtvRg, codigoRg);

	printf("\n \n confirmar dados do cadastro (sim/nao)\n");
	read(resposta, 4);

	if(strcmp(resposta, "sim") == 0 || strcmp(resposta, "Sim") == 0) //salva as respostas no cadastro
	{
		strcpy(cadastros[indexLivre].escola, escolaRg); //marcar as respostas
		strcpy(cadastros[indexLivre].tema, temaRg);
		strcpy(cadastros[indexLivre].data, dataRg);
		strcpy(cadastros[indexLivre].publicoAlvo, publicoAlvoRg);
		strcpy(cadastros[indexLivre].responsavel, responsavelRg);
		cadastros[indexLivre].participantes = participantesRg;
		strcpy(cadastros[indexLivre].sitAtv, sitAtvRg);
		strcpy(cadastros[indexLivre].codigo, codigoRg);
		cadastros[indexLivre].vazio = false;

		printf("Cadastro salvo com sucesso\n");
		printf("O index da acao foi definido como %d\n", indexLivre);
	}

	else if(strcmp(resposta, "nao") == 0 || strcmp(resposta, "Nao"))
	{
			//perguntar oue mudar e implementar edicao dos dados.
	}

}

void Listar_Acoes()
{
	for(int i = 0; i < CADASTRO_MAX; i++)
	{
		if(cadastros[i].vazio == false)
		{
			printf("==== Acao de index %d ====\n escola: %s\n tema: %s\n codigo: %s\n\n", i, cadastros[i].escola, cadastros[i].tema, cadastros[i].codigo);
		}
	}
}

void Ver_Acao()
{
	int index;
	printf("Qual o index da ação que voce gostaria de ver?\n");
	printf("digite '-1' para voltar ou coloque um index valido\n");
	//recebe o valor do index e administra erros
	bool ValorValido = false;
	while(ValorValido == false)
	{
		
		printf(":");
		scanf("%d", &index);

		if(index >= 0 && index < CADASTRO_MAX && cadastros[index].vazio == false)
		{
			ValorValido = true;
		}
		else if(cadastros[index].vazio == true)
		{
			printf("o index %d que foi passado leva para um cadastro vazio", index);
			printf("digite '-1' para voltar ou coloque um index valido\n");
		}
		else if(index == -1)
		{
			return;
		}
		else
		{
			printf("Valor invalido\n");
			printf("digite '-1' para voltar ou coloque um index valido\n");
		}
	}
	
	printf("\n === Acao de index %d ===\nescola: %s \ntema: %s\ndata prevista: %s\npublico alvo: %s\nresponsavel pela acao: %s\nnumero de participantes: %d\nsituacao: %s\ncodigos: %s\n",index, cadastros[index].escola, cadastros[index].tema, cadastros[index].data, cadastros[index].publicoAlvo, cadastros[index].responsavel, cadastros[index].participantes, cadastros[index].sitAtv, cadastros[index].codigo);
}

void Inicializar_Variavel()
{
	for(int i = 0; i < CADASTRO_MAX; i++)
	{
		cadastros[i].vazio = true;
	}
}
int main()
{

	int resposta; 
	


	//**inicializa a variavel vazio dos cadastros
	//se depois for colocar um sistema de registro ou banco de dados
	//retirar essa variavel e alterar o Listar ações, Ver Açao e outras funcoes 
	//do tipo que usam a variavel vazio do cadastro
	Inicializar_Variavel();

	while (true) {
	
	

		
		
		printf("Oque voce gostaria de fazer? (digite o numero da acao)\n");
		printf("1- Cadastrar acao\n2- Listar acoes\n3- Ver acao\n");

		//repete para apenas aceitar respostas certas
		bool valorAceito = false;
		while(valorAceito == false)
		{
			scanf("%d", &resposta);
			Clear_Buffer();
			if(resposta >= 1 && resposta <= 3)
			{
				valorAceito = true;
			}
		}
		
		if(resposta == 1)
		{
			Cadastrar_Acao();
		}
		else if(resposta == 2)
		{
			Listar_Acoes();
		}
		else if(resposta == 3)
		{
			Ver_Acao();
		}

	}

	return 0;

}


