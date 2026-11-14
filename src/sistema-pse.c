#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_ACOES 100

/* situacao da acao */
#define PLANEJADA 0
#define REALIZADA 1
#define CANCELADA 2

struct Acao
{
	int codigo;
	char escola[100];
	char tema[100];
	char data[11];
	char publicoAlvo[100];
	char responsavel[100];
	int previstos;
	int efetivos;
	int situacao;
};

struct Acao acoes[MAX_ACOES];
int totalAcoes = 0;

/* ================= FUNCOES DE APOIO ================= */

void limparBuffer() /* limpa o buffer do teclado */
{
	int c = 0;
	while ((c = getchar()) != EOF && c != '\n') {}
}

void lerTexto(char destino[], int tamanho) /* le uma linha e repete se vier vazia */
{
	while (true)
	{
		if (fgets(destino, tamanho, stdin) == NULL)
		{
			destino[0] = '\0';
			return;
		}

		size_t fim = strcspn(destino, "\n");

		if (destino[fim] == '\n')
		{
			destino[fim] = '\0';
		}
		else
		{
			limparBuffer(); /* digitou mais que o limite, descarta o resto */
		}

		if (strlen(destino) > 0)
		{
			return;
		}

		printf("Campo obrigatorio, digite novamente: ");
	}
}

int lerInteiro(int minimo, int maximo) /* le um numero e repete ate estar no intervalo */
{
	int valor;

	while (true)
	{
		if (scanf("%d", &valor) != 1) /* digitou algo que nao e numero */
		{
			limparBuffer();
			printf("Valor invalido, digite um numero: ");
			continue;
		}

		limparBuffer();

		if (valor < minimo || valor > maximo)
		{
			printf("Valor invalido, digite um numero entre %d e %d: ", minimo, maximo);
			continue;
		}

		return valor;
	}
}

void paraMinusculas(char destino[], const char origem[]) /* copia o texto em minusculas */
{
	int i = 0;

	while (origem[i] != '\0')
	{
		if (origem[i] >= 'A' && origem[i] <= 'Z')
		{
			destino[i] = origem[i] + ('a' - 'A');
		}
		else
		{
			destino[i] = origem[i];
		}
		i++;
	}

	destino[i] = '\0';
}

bool contemTexto(const char texto[], const char termo[]) /* verifica se termo aparece dentro de texto, sem diferenciar maiusculas */
{
	char textoMin[100];
	char termoMin[100];

	paraMinusculas(textoMin, texto);
	paraMinusculas(termoMin, termo);

	return strstr(textoMin, termoMin) != NULL;
}

const char *situacaoTexto(int situacao)
{
	if (situacao == PLANEJADA) return "Planejada";
	if (situacao == REALIZADA) return "Realizada";
	return "Cancelada";
}

int buscarPorCodigo(int codigo) /* devolve o indice no vetor ou -1 se nao existir */
{
	int i;

	for (i = 0; i < totalAcoes; i++)
	{
		if (acoes[i].codigo == codigo)
		{
			return i;
		}
	}

	return -1;
}

void imprimirAcao(struct Acao a)
{
	printf("\n==== Acao %d ====\n", a.codigo);
	printf("Escola: %s\n", a.escola);
	printf("Tema: %s\n", a.tema);
	printf("Data prevista: %s\n", a.data);
	printf("Publico alvo: %s\n", a.publicoAlvo);
	printf("Responsavel: %s\n", a.responsavel);
	printf("Participantes previstos: %d\n", a.previstos);
	printf("Participantes efetivos: %d\n", a.efetivos);
	printf("Situacao: %s\n", situacaoTexto(a.situacao));
}

bool dataValida(const char data[]) /* confere o formato DD/MM/AAAA e se a data existe */
{
	int i, dia, mes, ano, diasNoMes;

	if (strlen(data) != 10)
	{
		return false;
	}

	for (i = 0; i < 10; i++)
	{
		if (i == 2 || i == 5)
		{
			if (data[i] != '/') return false;
		}
		else
		{
			if (data[i] < '0' || data[i] > '9') return false;
		}
	}

	/* converte os caracteres em numeros: '7' - '0' = 7 */
	dia = (data[0] - '0') * 10 + (data[1] - '0');
	mes = (data[3] - '0') * 10 + (data[4] - '0');
	ano = (data[6] - '0') * 1000 + (data[7] - '0') * 100 + (data[8] - '0') * 10 + (data[9] - '0');

	if (mes < 1 || mes > 12 || ano < 1900)
	{
		return false;
	}

	if (mes == 2)
	{
		if ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0)
			diasNoMes = 29; /* ano bissexto */
		else
			diasNoMes = 28;
	}
	else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
	{
		diasNoMes = 30;
	}
	else
	{
		diasNoMes = 31;
	}

	return dia >= 1 && dia <= diasNoMes;
}

void lerData(char destino[]) /* le a data e repete ate ser valida */
{
	while (true)
	{
		printf("Data prevista (DD/MM/AAAA): ");
		lerTexto(destino, 11);

		if (dataValida(destino))
		{
			return;
		}

		printf("Data invalida, use o formato DD/MM/AAAA com uma data existente.\n");
	}
}

int lerSituacao()
{
	printf("1 - Planejada\n2 - Realizada\n3 - Cancelada\n: ");
	return lerInteiro(1, 3) - 1; /* converte 1/2/3 para 0/1/2 */
}

int lerCodigoNovo() /* le um codigo e repete enquanto estiver duplicado */
{
	int codigo;

	while (true)
	{
		printf("Codigo da acao: ");
		codigo = lerInteiro(1, 999999);

		if (buscarPorCodigo(codigo) == -1)
		{
			return codigo;
		}

		printf("Ja existe uma acao com o codigo %d, digite outro.\n", codigo);
	}
}

/* ================= FUNCIONALIDADES ================= */

void cadastrarAcao()
{
	struct Acao nova;
	char resposta[10];
	int campo;

	if (totalAcoes >= MAX_ACOES)
	{
		printf("\nLimite de %d acoes atingido, nao e possivel cadastrar.\n", MAX_ACOES);
		return;
	}

	printf("\n===== CADASTRO DE ACAO =====\n");

	nova.codigo = lerCodigoNovo();

	printf("Escola: ");
	lerTexto(nova.escola, 100);

	printf("Tema: ");
	lerTexto(nova.tema, 100);

	lerData(nova.data);

	printf("Publico alvo: ");
	lerTexto(nova.publicoAlvo, 100);

	printf("Responsavel: ");
	lerTexto(nova.responsavel, 100);

	printf("Participantes previstos: ");
	nova.previstos = lerInteiro(0, 999999);

	printf("Situacao inicial:\n");
	nova.situacao = lerSituacao();
	if(nova.situacao == 1){
	    nova.efetivos = nova.previstos;		
	} else{
		nova.efetivos = 0;
	}


	/* confirmacao, com opcao de corrigir campos */
	while (true)
	{
		imprimirAcao(nova);
		printf("\nConfirmar cadastro? (sim/nao): ");
		lerTexto(resposta, 10);
		paraMinusculas(resposta, resposta);

		if (strcmp(resposta, "sim") == 0)
		{
			acoes[totalAcoes] = nova;
			totalAcoes++;
			printf("\nCadastro salvo com sucesso.\n");

			if (totalAcoes == MAX_ACOES)
			{
				printf("Atencao: limite de %d acoes atingido.\n", MAX_ACOES);
			}
			return;
		}

		if (strcmp(resposta, "nao") == 0)
		{
			printf("\nQual campo deseja alterar?\n");
			printf("1 - Codigo\n2 - Escola\n3 - Tema\n4 - Data\n5 - Publico alvo\n");
			printf("6 - Responsavel\n7 - Participantes previstos\n8 - Situacao\n0 - Cancelar cadastro\n: ");
			campo = lerInteiro(0, 8);

			if (campo == 0)
			{
				printf("\nCadastro cancelado.\n");
				return;
			}
			if (campo == 1) nova.codigo = lerCodigoNovo();
			if (campo == 2) { printf("Escola: "); lerTexto(nova.escola, 100); }
			if (campo == 3) { printf("Tema: "); lerTexto(nova.tema, 100); }
			if (campo == 4) lerData(nova.data);
			if (campo == 5) { printf("Publico alvo: "); lerTexto(nova.publicoAlvo, 100); }
			if (campo == 6) { printf("Responsavel: "); lerTexto(nova.responsavel, 100); }
			if (campo == 7) { printf("Participantes previstos: "); nova.previstos = lerInteiro(0, 999999); }
			if (campo == 8) { printf("Situacao:\n"); nova.situacao = lerSituacao(); nova.efetivos = 0; if(nova.situacao == 1){nova.efetivos = nova.previstos;}}
			continue;
		}

		printf("Resposta invalida, digite sim ou nao.\n");
	}
}

void listarAcoes()
{
	int i;

	if (totalAcoes == 0)
	{
		printf("\nNenhuma acao cadastrada.\n");
		return;
	}

	printf("\n===== LISTA DE ACOES (%d) =====\n", totalAcoes);

	for (i = 0; i < totalAcoes; i++)
	{
		imprimirAcao(acoes[i]);
	}
}

void pesquisarAcao()
{
	int opcao, i, codigo, encontradas = 0;
	char termo[100];

	if (totalAcoes == 0)
	{
		printf("\nNenhuma acao cadastrada.\n");
		return;
	}

	printf("\n===== PESQUISAR ACAO =====\n");
	printf("1 - Por codigo\n2 - Por escola\n3 - Por tema\n0 - Voltar\n: ");
	opcao = lerInteiro(0, 3);

	if (opcao == 0)
	{
		return;
	}

	if (opcao == 1)
	{
		printf("Codigo: ");
		codigo = lerInteiro(1, 999999);
		i = buscarPorCodigo(codigo);

		if (i == -1)
		{
			printf("\nNenhuma acao com o codigo %d.\n", codigo);
		}
		else
		{
			imprimirAcao(acoes[i]);
		}
		return;
	}

	printf("Digite o termo (pode ser parte do nome): ");
	lerTexto(termo, 100);

	for (i = 0; i < totalAcoes; i++)
	{
		if ((opcao == 2 && contemTexto(acoes[i].escola, termo)) ||
		    (opcao == 3 && contemTexto(acoes[i].tema, termo)))
		{
			imprimirAcao(acoes[i]);
			encontradas++;
		}
	}

	if (encontradas == 0)
	{
		printf("\nNenhuma acao encontrada com \"%s\".\n", termo);
	}
	else
	{
		printf("\n%d acao(oes) encontrada(s).\n", encontradas);
	}
}

void atualizarSituacao()
{
	int codigo, i;

	if (totalAcoes == 0)
	{
		printf("\nNenhuma acao cadastrada.\n");
		return;
	}

	printf("\n===== ATUALIZAR SITUACAO =====\n");

	while (true)
	{
		printf("Codigo da acao (0 para listar as acoes): ");
		codigo = lerInteiro(0, 999999);

		if (codigo == 0)
		{
			listarAcoes();
			continue;
		}

		i = buscarPorCodigo(codigo);

		if (i == -1)
		{
			printf("\nNenhuma acao com o codigo %d.\n", codigo);
			return;
		}

		break;
	}

	imprimirAcao(acoes[i]);

	printf("\nNova situacao:\n");
	acoes[i].situacao = lerSituacao();

	if (acoes[i].situacao == REALIZADA)
	{
		printf("Participantes efetivos: ");
		acoes[i].efetivos = lerInteiro(0, 999999);
	}
	else
	{
		acoes[i].efetivos = 0; /* so acao realizada tem participantes */
	}

	printf("\nSituacao atualizada para %s.\n", situacaoTexto(acoes[i].situacao));
}

void gerarResumo()
{
	int i;
	int planejadas = 0, realizadas = 0, canceladas = 0;
	int previstosTotal = 0, previstosRealizadas = 0, efetivosTotal = 0;
	float percentual;

	if (totalAcoes == 0)
	{
		printf("\nNenhuma acao cadastrada.\n");
		return;
	}

	for (i = 0; i < totalAcoes; i++)
	{
		previstosTotal += acoes[i].previstos;

		if (acoes[i].situacao == PLANEJADA) planejadas++;
		if (acoes[i].situacao == CANCELADA) canceladas++;
		if (acoes[i].situacao == REALIZADA)
		{
			realizadas++;
			previstosRealizadas += acoes[i].previstos;
			efetivosTotal += acoes[i].efetivos;
		}
	}

	printf("\n===== RESUMO GERAL =====\n");
	printf("Total de acoes: %d\n", totalAcoes);
	printf("Planejadas: %d\n", planejadas);
	printf("Realizadas: %d\n", realizadas);
	printf("Canceladas: %d\n", canceladas);
	printf("Participantes previstos (todas as acoes): %d\n", previstosTotal);
	printf("Participantes efetivos (acoes realizadas): %d\n", efetivosTotal);

	if (previstosRealizadas == 0)
	{
		printf("Percentual de participacao: nao ha acoes realizadas com previsao.\n");
	}
	else
	{
		percentual = (float) efetivosTotal / previstosRealizadas * 100;
		printf("Percentual de participacao (realizadas): %.1f%%\n", percentual);
	}
}

/* ================= MENU PRINCIPAL ================= */

int main()
{
	int opcao;

	do
	{
	    system("cls");
	    
		printf("\n===== SISTEMA DE ACOMPANHAMENTO DO PSE =====\n");
		printf("1 - Cadastrar acao\n");
		printf("2 - Listar acoes\n");
		printf("3 - Pesquisar acao\n");
		printf("4 - Atualizar situacao\n");
		printf("5 - Gerar resumo\n");
		printf("0 - Sair\n: ");

		opcao = lerInteiro(0, 5);

		if (opcao == 1) cadastrarAcao();
		if (opcao == 2) listarAcoes();
		if (opcao == 3) pesquisarAcao();
		if (opcao == 4) atualizarSituacao();
		if (opcao == 5) gerarResumo();

		system("pause");

	} while (opcao != 0);

	printf("\nPrograma encerrado.\n");
	return 0;
}
