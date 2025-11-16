# Sistema Contábil

![Docker](https://img.shields.io/badge/Docker-Enabled-2496ED?style=flat-square&logo=docker)
![Language](https://img.shields.io/badge/Language-C-A8B9CC?style=flat-square&logo=c)
![License](https://img.shields.io/badge/License-MIT-green?style=flat-square)
![Status](https://img.shields.io/badge/Status-Active-brightgreen?style=flat-square)

Um sistema contábil robusto desenvolvido em linguagem C e containerizado com Docker para facilitar a implantação e o gerenciamento de transações financeiras.

## Visão Geral

Este projeto implementa um sistema contábil completo que permite registrar, processar e gerar relatórios de transações. A aplicação foi desenvolvida em C e empacotada em um container Docker para garantir portabilidade e consistência entre diferentes ambientes de execução.

## Estrutura do Projeto

```
sistemacontabil/
├── main.c           # Ponto de entrada da aplicação
├── transacao.c      # Implementação de transações
├── transacao.h      # Interface de transações
├── relatorios.c     # Geração de relatórios
├── relatorios.h     # Interface de relatórios
├── utils.c          # Funções utilitárias
├── utils.h          # Interface de utilitários
├── Dockerfile       # Configuração do container
└── data/            # Diretório de dados (criado automaticamente)
    └── planilhas/   # Arquivos de relatórios em Excel
```

## Pré-requisitos

Antes de começar, certifique-se de ter instalado em sua máquina:

- Docker versão 20.10 ou superior
- Terminal/Console com suporte a comandos Linux
- Permissões para executar comandos com Docker

## Configuração do Dockerfile

O Dockerfile utiliza a imagem base `ubuntu:latest` e instala as ferramentas necessárias para compilação:

```dockerfile
FROM ubuntu:latest
RUN apt-get update && apt-get install -y build-essential nano
CMD ["/bin/bash"]
```

### Componentes do Dockerfile

- **FROM ubuntu:latest**: Define a imagem base Ubuntu mais recente como ponto de partida
- **RUN apt-get update**: Atualiza a lista de pacotes disponíveis
- **RUN apt-get install -y**: Instala ferramentas de compilação (GCC, Make, etc.) e editor Nano
- **CMD ["/bin/bash"]**: Define o bash como shell padrão do container

## Instruções de Uso

### 1. Construir a Imagem Docker

Na pasta onde o Dockerfile está localizado, execute:

```bash
docker build -t ubuntucontabil .
```

Este comando:
- Lê as instruções do Dockerfile
- Cria uma imagem nomeada `ubuntucontabil`
- O ponto final (`.`) indica que o Dockerfile está no diretório atual

**Tempo estimado de construção**: 3-5 minutos na primeira execução

### 2. Criar e Executar o Container

Para criar e iniciar o container interativo:

```bash
docker run -it --name sistemacontabil ubuntucontabil
```

Opções utilizadas:
- `-i`: Mantém a entrada padrão aberta mesmo sem conexão
- `-t`: Aloca um pseudo-terminal
- `--name sistemacontabil`: Nomeia o container para fácil identificação
- `ubuntucontabil`: Nome da imagem a ser utilizada

### 3. Configurar Estrutura de Diretórios

Dentro do container, crie a estrutura de pastas do projeto:

```bash
mkdir sistemacontabil
cd sistemacontabil
```

### 4. Criar os Arquivos do Projeto

Crie todos os arquivos necessários utilizando o comando `touch`:

```bash
touch main.c relatorios.c relatorios.h transacao.c transacao.h utils.c utils.h
```

### 5. Editar os Arquivos

Para adicionar código a cada arquivo, utilize o editor Nano:

```bash
nano main.c
```

Após abrir o editor:
- Pressione `i` para entrar no modo de inserção
- Cole ou digite seu código
- Pressione `Ctrl + X` para sair
- Digite `Y` para confirmar salvar
- Pressione `Enter` para confirmar o nome do arquivo

Repita este processo para todos os arquivos `.c` e `.h`.

### 6. Compilar o Projeto

Para compilar todos os arquivos-fonte em um único executável:

```bash
gcc main.c relatorios.c transacao.c utils.c -o sistema.exe
```

Componentes da compilação:
- `gcc`: Compilador GNU C
- `main.c relatorios.c transacao.c utils.c`: Arquivos-fonte a compilar
- `-o sistema.exe`: Define o nome do executável gerado

**Saída esperada**: Arquivo `sistema.exe` criado na pasta atual

### 7. Executar a Aplicação

Para iniciar o sistema contábil:

```bash
./sistema.exe
```

A aplicação iniciará e estará pronta para processar transações e gerar relatórios.

### 8. Arquivos de Saída

Ao executar o sistema, será criada automaticamente uma pasta `data` com a seguinte estrutura:

```
data/
└── planilhas/
    ├── relatorio_transacoes.xlsx
    ├── relatorio_saldo.xlsx
    └── [outros arquivos de relatório]
```

Os arquivos gerados estão em formato Excel e podem ser transferidos para sua máquina local para análise detalhada.

### 9. Encerrar a Aplicação

Para sair do sistema contábil:

```bash
exit
```

Pressione `Enter` para confirmar. O programa será finalizado.

## Fluxo de Trabalho Completo

Um exemplo de fluxo de trabalho típico:

```bash
# Construir a imagem
docker build -t ubuntucontabil .

# Executar o container
docker run -it --name sistemacontabil ubuntucontabil

# Dentro do container
mkdir sistemacontabil && cd sistemacontabil
touch main.c relatorios.c relatorios.h transacao.c transacao.h utils.c utils.h

# Editar arquivos (repita para cada arquivo)
nano main.c

# Compilar
gcc main.c relatorios.c transacao.c utils.c -o sistema.exe

# Executar
./sistema.exe

# Sair
exit
```

## Gerenciamento de Containers

### Listar containers em execução

```bash
docker ps
```

### Listar todos os containers (incluindo inativos)

```bash
docker ps -a
```

### Parar um container

```bash
docker stop sistemacontabil
```

### Reiniciar um container existente

```bash
docker start -i sistemacontabil
```

### Remover um container

```bash
docker rm sistemacontabil
```

### Remover uma imagem

```bash
docker rmi ubuntucontabil
```

## Transferir Dados entre Container e Host

### Copiar arquivo do container para o host

```bash
docker cp sistemacontabil:/root/sistemacontabil/data ./dados_locais
```

### Copiar arquivo do host para o container

```bash
docker cp ./arquivo_local sistemacontabil:/root/sistemacontabil/
```

## Solução de Problemas

### Erro: "docker: command not found"

Certifique-se de que o Docker está instalado e adicionado ao PATH do sistema.

### Erro: "Permission denied while trying to connect to Docker daemon"

Execute os comandos com privilégios de administrador ou adicione seu usuário ao grupo Docker:

```bash
sudo usermod -aG docker $USER
```

### Container não inicia

Verifique se já existe um container com o mesmo nome:

```bash
docker rm sistemacontabil
```

### Erro de compilação no container

Certifique-se de que todos os arquivos-fonte estão na mesma pasta e que a sintaxe C está correta.

## Recursos Técnicos

- **Linguagem**: C (ISO/IEC 9899:2011)
- **Compilador**: GCC (GNU Compiler Collection)
- **Container**: Docker
- **Ambiente Base**: Ubuntu Linux
- **Formato de Saída**: Excel (.xlsx)

## Boas Práticas

1. Sempre execute o container com a opção `-it` para garantir interatividade
2. Nomeie seus containers para facilitar o gerenciamento
3. Faça backup regularmente dos arquivos na pasta `data`
4. Utilize volumes Docker se necessitar persistência de dados entre execuções
5. Mantenha a imagem Docker atualizada reconstruindo periodicamente

## Notas Importantes

- Os dados armazenados no diretório `data` serão preservados enquanto o container existir
- Para persistir dados entre execuções de containers diferentes, considere usar volumes Docker
- A pasta `data` é criada automaticamente na primeira execução do sistema
- Os relatórios em Excel são gerados automaticamente conforme o sistema processa transações

## Suporte e Contribuições

Para reportar problemas, sugestões de melhorias ou contribuições, entre em contato com a equipe de desenvolvimento.

## Versão

Versão 1.0.0 - Lançamento Inicial

---

**Desenvolvido com foco em robustez, portabilidade e facilidade de uso.**