# Relatório 2
- Henrique Noronha Facioli - 157986
- Thiago Silva de Farias - 148077

Para ler do arquivo, utilizaremos o parâmetro -r que do manual:
```
-r file
       Read packets from file (which was created with the -w option or by other tools  that  write  pcap  or
       pcap-ng files).  Standard input is used if file is ``-''.
```
## 1. Qual é o endereço IP dos nós maple e willow?
Fizemos a extração uma vez utilizando o comando `tcpdump -r tcpdump.cap  > tcpdump.txt` para utilizar os nomes e outra vez `tcpdump -r tcpdump.cap -n > tcpdumpip.txt` que substitui os nomes por endereços IPS. Dessa maneira, podemos comparar ambos os arquivos e verificar qual o ip de cada um.
- willow: `willow.csail.mit.edu` com IP `128.30.4.222`
- maple: `maple.csail.mit.edu.commplex-link` com IP `128.30.4.223`

## 2.  Qual é o endereço MAC dos nós  maple e willow?
Foi feito o mesmo procedimento do anterior mas para obter o MAC adress utilizamos
- willow: `willow.csail.mit.edu` com MAC `00:16:ea:8e:28:44`
- maple: `maple.csail.mit.edu.commplex-link` com MAC `00:16:ea:8d:e5:8a`

## 3. Qual é a porta TCP usada pelos nós maple e willow?
Com o comando -nn ele imprime o número das portas usadas na conexão e assim temos
- willow: `willow.csail.mit.edu` com porta `39675`
- maple: `maple.csail.mit.edu.commplex-link` com porta `5001`

## 4. Quantos kilobytes foram transferidos durante essa sessão TCP? Qual foi a duração da sessão? Baseado nas respostas anteriores, qual é a vazão (em Kilobytes/segundo) do fluxo TCP entre willow e maple?
Para sabermos quantos dados foram tranferidos podemos observar o valor inicial da sequencia (1) e o final. Como a sequencia é incrementada do tamanho de cada pacote, a diferença entre os dois é o número total de dados.
```
01:34:41.474166 IP willow.csail.mit.edu.39675 > maple.csail.mit.edu.commplex-link: Flags [P.], seq 1:25, ack 1, win 115, options [nop,nop,TS val 282136474 ecr 282202089], length 24
01:34:44.311921 IP willow.csail.mit.edu.39675 > maple.csail.mit.edu.commplex-link: Flags [FP.], seq 1572017:1572889, ack 1, win 115, options [nop,nop,TS val 282139311 ecr 282204927], length 872
```
portanto, 1572.89 Kilobytes foram trocados.
A duração da sessão pode ser pega utilizando o primeiro tempo e o ultimo e fazendo sua diferença: 2.865979s.
A vazão pode ser calculada como a razão entre o número de kilobytes e o tempo total da sessão 548.86 kilobytes por segundo..


## 5. Qual é o round-trip time (RTT), em segundos, entre willow e maple baseado no pacote 1473:2921 e seu acknowledgment? Veja o arquivo outfile.txt e encontre o RTT do pacote 13057:14505. Por que esses dois valores são diferentes?

Para verificar o tempo do RTT do pacote 1443:2921 precisamos pegar o horário em que foi enviado o pacote e a hora emq eu foi recebido o ack do seu valor
```
01:34:41.474225 IP (tos 0x0, ttl 64, id 61638, offset 0, flags [DF], proto TCP (6), length 1500)
    128.30.4.222.39675 > 128.30.4.223.commplex-link: Flags [.], seq 1473:2921, ack 1, win 115, options [nop,nop,TS val 282136474 ecr 282202089], length 1448
    01:34:41.482047 IP (tos 0x0, ttl 64, id 63442, offset 0, flags [DF], proto TCP (6), length 52)
    128.30.4.223.commplex-link > 128.30.4.222.39675: Flags [.], cksum 0x802e (correct), ack 2921, win 159, options [nop,nop,TS val 282202095 ecr 282136474], length 0
```
dessa maneira temos o tempo de 0.007822 segundos.

O tempo para o pacote 13057:14505 é medido da mesma maneira
```
01:34:41.474992 IP (tos 0x0, ttl 64, id 61646, offset 0, flags [DF], proto TCP (6), length 1500)
    128.30.4.222.39675 > 128.30.4.223.commplex-link: Flags [.], seq 13057:14505, ack 1, win 115, options [nop,nop,TS val 282136474 ecr 282202090], length 1448
01:34:41.499373 IP (tos 0x0, ttl 64, id 63450, offset 0, flags [DF], proto TCP (6), length 52)
    128.30.4.223.commplex-link > 128.30.4.222.39675: Flags [.], cksum 0x522f (correct), ack 14505, win 331, options [nop,nop,TS val 282202114 ecr 282136474], length 0
```
com tempo total de 0.024381 segundos

## 6. Identifique os procedimentos three-way handshake e connection termination. Coloque as mensagens envolvidas em uma tabela e, para cada um dos procedimentos, inclua a fonte, o destino e informações das mensagens.
