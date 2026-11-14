# PSE em Ação — Sistema de Planejamento e Acompanhamento de Ações de Saúde na Escola

Atividade de Estudo Prático (AEP) — 2º semestre de 2026
Curso: Tecnólogo em Análise e Desenvolvimento de Sistemas — UniCesumar (Maringá – PR)

## Integrantes

| Nome | GitHub |
|---|---|
| Eric Barros Arco-Verde | [@Eric-ArcoVerde](https://github.com/Eric-ArcoVerde) |
| Henrique Estrela Correia | [@Henrique-Estrela-Correia115](https://github.com/Henrique-Estrela-Correia115) |
| Valdemar Tieppo Neto | [@valder5780](https://github.com/valder5780) |

## Sobre o projeto

Aplicação de terminal, desenvolvida em linguagem C, para apoiar uma equipe intersetorial (escola + Atenção Primária à Saúde) no planejamento, registro e acompanhamento de **ações coletivas** do Programa Saúde na Escola (PSE), instituído pelo Decreto nº 6.286/2007.

O sistema substitui o controle feito em anotações, formulários e planilhas separadas, permitindo localizar ações programadas, verificar as concluídas, identificar cancelamentos e consolidar a quantidade de participantes atendidos por escola.

**Questão norteadora:** como uma aplicação desenvolvida em linguagem C pode auxiliar uma equipe escolar e de saúde a planejar, registrar e acompanhar ações coletivas do PSE, apresentando informações claras e preservando a privacidade dos estudantes?

## Funcionalidades

O programa é operado por um menu principal com seis opções:

| Opção | Funcionalidade | O que faz |
|---|---|---|
| 1 | **Cadastrar ação** | Lê código, escola, tema, data prevista, público-alvo, responsável, participantes previstos e situação inicial. Antes de salvar, exibe o resumo e pede confirmação; se o usuário responder "nao", permite corrigir qualquer campo ou cancelar o cadastro. |
| 2 | **Listar ações** | Exibe todas as ações cadastradas com todos os campos. |
| 3 | **Pesquisar ação** | Submenu para buscar por código (exato) ou por escola/tema (termo parcial, sem diferenciar maiúsculas de minúsculas). |
| 4 | **Atualizar situação** | Localiza a ação pelo código (ou lista as ações antes) e altera para planejada, realizada ou cancelada. Quando realizada, registra a quantidade efetiva de participantes. |
| 5 | **Gerar resumo** | Total de ações por situação, participantes previstos, participantes efetivos e percentual de participação (efetivos ÷ previstos das ações realizadas). |
| 0 | **Sair** | Encerra o programa. |

### Validações e tratamento de erros

- Letras onde se espera número, números fora do intervalo e quantidades negativas são rejeitados e a entrada é pedida novamente.
- Campos de texto não podem ficar vazios.
- Código duplicado é recusado no cadastro.
- Data é validada no formato `DD/MM/AAAA`, com mês, dia do mês e ano bissexto conferidos.
- Código inexistente, pesquisa sem resultado e lista/resumo vazios geram mensagem e retorno ao menu.
- Limite de 100 ações: o sistema avisa ao atingir o limite e impede novos cadastros.
- O programa nunca é encerrado por erro de entrada; sempre repete a pergunta ou volta ao menu.

## Organização do código

Arquivo único `src/sistema-pse.c`, dividido em:

- **Estrutura de dados** — `struct Acao` e o vetor global `acoes[100]` com contador `totalAcoes`.
- **Funções de apoio** — leitura validada (`lerTexto`, `lerInteiro`, `lerData`, `lerSituacao`, `lerCodigoNovo`), busca (`buscarPorCodigo`, `contemTexto`), exibição (`imprimirAcao`, `situacaoTexto`) e validação (`dataValida`).
- **Funcionalidades** — `cadastrarAcao`, `listarAcoes`, `pesquisarAcao`, `atualizarSituacao`, `gerarResumo`.
- **`main`** — menu em `do/while` que chama as funcionalidades até o usuário escolher sair.

## Limites éticos e de escopo

- Utiliza **somente dados fictícios e coletivos** sobre as ações.
- **Não** armazena nome, diagnóstico, prontuário, condição clínica ou qualquer dado sensível individual de estudantes.
- **Não** realiza diagnóstico, triagem, prescrição ou recomendação de tratamento.
- Armazenamento em memória durante a execução (sem banco de dados, interface gráfica ou aplicação web).

## Tecnologias

- Linguagem C (padrão C99 ou superior)
- Compilador GCC (Linux) ou Dev-C++/MinGW (Windows)
- Estruturas utilizadas: `struct`, vetores, funções, estruturas condicionais e laços de repetição

## Como compilar e executar

Linux:

```bash
gcc -Wall -Wextra -o sistema-pse src/sistema-pse.c
./sistema-pse
```

Windows (MinGW ou Dev-C++):

```bash
gcc -Wall -Wextra -o sistema-pse.exe src\sistema-pse.c
sistema-pse.exe
```

Há também um executável já compilado para Windows em `bin/sistema-pse.exe`.

## Estrutura do repositório

```
.
├── README.md
├── bin/
│   └── sistema-pse.exe                     # executável compilado para Windows
├── docs/
│   ├── etapa1/
│   │   ├── AEP_2_revisado.pdf              # documento escrito da etapa 1
│   │   ├── Fluxograma AEP 2 Geral.drawio   # fluxograma geral do sistema
│   │   └── Fluxograma AEP 2 - pesquisa.drawio   # fluxograma da pesquisa
│   └── etapa2/
│       ├── manual-sistema-pse.pdf          # manual do usuário
│       └── diagrama-casos-de-uso-pse.drawio.xml   # diagrama de casos de uso
└── src/
    └── sistema-pse.c                       # código-fonte em C
```

## Processo de desenvolvimento

Processo evolutivo, iterativo e incremental, inspirado em práticas do Scrum e organizado em sprints semanais. Cada sprint produz um incremento compilável e testável ou um artefato de documentação, revisado no início da sprint seguinte.

| Sprint | Fase | Responsáveis |
|---|---|---|
| 1 | Levantamento | Valdemar e Henrique |
| 2 | Modelagem (fluxogramas, repositório, casos de uso) | Eric / Todos |
| 3 | Implementação — Incremento 1 (menu, cadastrar, listar, validações) | Todos |
| 4 | Implementação — Incremento 2 (pesquisar, atualizar situação) | Eric |
| 5 | Implementação — Incremento 3 (resumo, limite, refatoração) | Valdemar |
| 6 | Testes | Todos |
| 7 | Documentação (manual, capturas de tela) | Henrique |
| 8 | Apresentação (vídeo de até 7 min, entrega final) | Todos |

O planejamento detalhado está em `docs/etapa1/`.

## Documentação

- [Documento da etapa 1](docs/etapa1/AEP_2_revisado.pdf)
- Fluxogramas: [geral](docs/etapa1/Fluxograma%20AEP%202%20Geral.drawio) e [pesquisa](docs/etapa1/Fluxograma%20AEP%202%20-%20pesquisa.drawio) (abrir em [draw.io](https://app.diagrams.net))
- [Manual do usuário](docs/etapa2/manual-sistema-pse.pdf)
- [Diagrama de casos de uso](docs/etapa2/diagrama-casos-de-uso-pse.drawio.xml) (abrir em draw.io)

## Entregas

- [x] **Etapa 1** — documento escrito (contextualização, requisitos, fluxogramas e planejamento das sprints)
- [ ] **Etapa 2** — implementação em C, casos de uso, testes, manual do usuário e vídeo de apresentação
  - [x] Implementação em C
  - [x] Diagrama de casos de uso
  - [x] Manual do usuário
  - [ ] Vídeo de apresentação

## Referências

- BRASIL. Decreto nº 6.286, de 5 de dezembro de 2007. Institui o Programa Saúde na Escola – PSE. Diário Oficial da União, Brasília, DF, 6 dez. 2007.
- BRASIL. Ministério da Saúde. *O que é o Programa Saúde na Escola (PSE)?* Brasília, DF, 2025a.
- BRASIL. Ministério da Saúde. *Quais são as ações do PSE?* Brasília, DF, 2025b.
- SOUSA, M. C.; ESPERIDIÃO, M. A.; MEDINA, M. G. A intersetorialidade no Programa Saúde na Escola: avaliação do processo político-gerencial e das práticas de trabalho. *Ciência & Saúde Coletiva*, v. 22, n. 6, p. 1781-1790, 2017.
