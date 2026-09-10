# PSE em Ação — Sistema de Planejamento e Acompanhamento de Ações de Saúde na Escola

Atividade de Estudo Prático (AEP) — 2º semestre de 2026
Curso: Tecnólogo em Análise e Desenvolvimento de Sistemas — UniCesumar (Maringá – PR)

## Integrantes

| Nome | GitHub |
|---|---|
| Eric Barros Arco-Verde | [@Eric-ArcoVerde](https://github.com/Eric-ArcoVerde) |
| Henrique Estrela Correia | *(a adicionar)* |
| Valdemar Tieppo Neto | [@valder5780](https://github.com/valder5780) |

## Sobre o projeto

Aplicação de terminal, desenvolvida em linguagem C, para apoiar uma equipe intersetorial (escola + Atenção Primária à Saúde) no planejamento, registro e acompanhamento de **ações coletivas** do Programa Saúde na Escola (PSE), instituído pelo Decreto nº 6.286/2007.

O sistema substitui o controle feito em anotações, formulários e planilhas separadas, permitindo localizar ações programadas, verificar as concluídas, identificar cancelamentos e consolidar a quantidade de participantes atendidos por escola.

**Questão norteadora:** como uma aplicação desenvolvida em linguagem C pode auxiliar uma equipe escolar e de saúde a planejar, registrar e acompanhar ações coletivas do PSE, apresentando informações claras e preservando a privacidade dos estudantes?

## Funcionalidades

1. **Cadastrar ação** — código, escola, tema, data prevista, público-alvo, responsável, quantidade prevista de participantes e situação inicial.
2. **Listar ações** — exibe todas as ações cadastradas de forma organizada.
3. **Pesquisar ações** — por código, escola ou tema.
4. **Atualizar situação** — planejada, realizada ou cancelada; quando realizada, registra a quantidade efetiva de participantes.
5. **Gerar resumo** — total de ações por situação, total de participantes e percentual de participação em relação ao previsto.
6. **Validar entradas** — impede códigos repetidos, quantidades negativas, campos obrigatórios vazios e opções inexistentes no menu.

## Limites éticos e de escopo

- Utiliza **somente dados fictícios e coletivos** sobre as ações.
- **Não** armazena nome, diagnóstico, prontuário, condição clínica ou qualquer dado sensível individual de estudantes.
- **Não** realiza diagnóstico, triagem, prescrição ou recomendação de tratamento.
- Armazenamento em memória durante a execução (sem banco de dados, interface gráfica ou aplicação web).

<!--
## Tecnologias

- Linguagem C (padrão C99 ou superior)
- Compilador GCC
- Estruturas utilizadas: `struct`, vetores, funções, estruturas condicionais e laços de repetição

## Como compilar e executar

```bash
gcc -Wall -o pse_em_acao src/main.c
./pse_em_acao
```

No Windows (MinGW):

```bash
gcc -Wall -o pse_em_acao.exe src\main.c
pse_em_acao.exe
```

> As instruções serão atualizadas na 2ª etapa, conforme a estrutura final dos arquivos-fonte.
-->
## Estrutura do repositório

```
.
├── README.md
├── docs/                 # documentação das etapas
│   ├── etapa1/           # documento escrito, fluxogramas, pseudocódigos, sprints
│   └── etapa2/           # casos de uso, testes, manual do usuário, considerações finais
└── src/                  # código-fonte em C
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

## Entregas

- [x] **Etapa 1** — documento escrito (contextualização, requisitos, fluxogramas e planejamento das sprints)
- [ ] **Etapa 2** — implementação em C, casos de uso, testes, manual do usuário e vídeo de apresentação

## Referências

- BRASIL. Decreto nº 6.286, de 5 de dezembro de 2007. Institui o Programa Saúde na Escola – PSE. Diário Oficial da União, Brasília, DF, 6 dez. 2007.
- BRASIL. Ministério da Saúde. *O que é o Programa Saúde na Escola (PSE)?* Brasília, DF, 2025a.
- BRASIL. Ministério da Saúde. *Quais são as ações do PSE?* Brasília, DF, 2025b.
- SOUSA, M. C.; ESPERIDIÃO, M. A.; MEDINA, M. G. A intersetorialidade no Programa Saúde na Escola: avaliação do processo político-gerencial e das práticas de trabalho. *Ciência & Saúde Coletiva*, v. 22, n. 6, p. 1781-1790, 2017.
