# Simulação de um cruzamento de carros com detecção de colisões no servidor
Projeto 2 de MC833
 - Henrique Noronha Facioli
 - Thiago Silva de Farias

## O que é
 Neste projeto, foi implementado um programa em C que utiliza sockets e recebe e envia pacotes de automóveis trafegando em duas vias que se cruzam. O objetivo é detectar potenciais colisões entre automóveis neste cruzamento, considerando as seguintes suposições sobre o cenário:
 - As vias têm mão dupla.
 - Os automóveis enviam pacotes, em intervalos de tempo fixados na simulação, com timestamp, posição, velocidade, direção, tamanho do automóvel (comprimento).
 - Existem três tipos diferentes de automóveis, todos com largura 1 e comprimentos discretos: "Car" (de comprimento 1), "Truck" (de comprimento 2) e "DoubleTruck" (de comprimento 3).
 - Todos os automóveis têm o relógio sincronizado.
 - Os automóveis executam aplicações de 3 tipos: segurança, entretenimento e conforto.
 - Os pacotes das aplicações de entretenimento e conforto têm apenas uma mensagem como conteúdo, enquanto os de segurança tem informações relevantes para os cálculos de possíveis colisões.
 - Somente o servidor detecta potenciais colisões baseados nos pacotes enviados pelos carros da simulação e pode emitir os alertas: - Continue, Acelere, Desacelere ou  Chame Ambulância.
 - Colisões traseiras não ocorrem, ou seja, um automóvel pode magicamente ultrapassar o outro, mesmo que exista um automóvel na direção contrária da via).
 - As mudanças de velocidade são instantâneas.
 - O cruzamento terá tamanho 2x2.
 - As ruas têm uma velocidade máxima (que é um dos parâmetros da simulação).
 - É utilizada uma matriz para a detecção das possíveis colisões, onde o cruzamento 2x2 está em seu centro. O tamanho da matriz (que também é um dos parâmetros da simulação), representa o raio do qual o servidor consegue receber mensagens dos automóveis.

## Como executar
### Parâmetros
Os parâmetros da simulação foram escolhidos baseados no potencial impacto da sua variação no número de colisões, ou no número de comandos do tipo Acelere ou Desacelere que deverão ser enviados pelo servidor. Eles estão listados a seguir:
 - **SIZE_MAP**: raio de comunicação com o servidor (utilizado também como tamanho da matriz). Valor padrão: 18.
 - **MAX_SPEED**: velocidade máxima dos carros na via. Valor padrão: 3.
 - **N_CONNECTIONS**: número de carros que podem estabelecer conexão com o servidor ao mesmo tempo. Valor padrão: 20.
 - **PACKAGE_INTERVAL**: intervalo de tempo no qual os carros enviam mensagens ao servidor. Valor padrão: 25ms.
 - **SPEED_INTERVAL**: tempo em que um carro com velocidade 1 leva para andar um bloco da matriz. Valor padrão: 10ms.
 - **SIMULATE(X)**: escolha da simulação de número X, que implica no número de carros na via, suas direções e suas velocidades iniciais. Valor padrão: 1.
 - **TCP**: escolha do tipo de protocolo utilizado (TCP ou UDP). Valor padrão: 1 (TCP).
 - **NCURSES_SIMULATE**: não é realmente um parâmetro, mas serve para definir o uso ou não da animação gráfica ao realizar a simulação. Valor padrão: 1 (ON).

### Executando
 1. Em primeiro lugar, deve-se definir os parâmetros desejados. Caso queira prosseguir com os parâmetros definidos como padrão, pule para o passo 2. Caso contrário, abra o arquivo definitions.h. Nele é possível variar todos os parâmetros utilizados no programa, além de podermos utilizar ou não uma animação para visualização da simulação. Configure os valores como desejado.
 2. No terminal, vá ao diretório que contém os arquivos relevantes ao programa.
 3. Primeiramente, dê o comando "make", para compilar o programa, e então "make run", para dar início a simulação.
