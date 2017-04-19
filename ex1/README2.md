# Relatório 1
- Henrique Noronha Facioli 157986
- Thiago Silva de Farias 148077

### a) Envie 10 pacotes que verificam o tempo de ida e volta a 5 endereços web de sua escolha (10 pacotes para cada endereço). Inclua no relatório os comandos utilizados e as saídas obtidas, além de uma análise sobre as informações observadas.

Podemos usar o comando `ping -c 10 $URL` para medir o tempo em que um pacote ICMP demora para ir a voltar. Com o parâmetro `-c` podemos dizer quantos pacotes ele deve enviar

#### www.google.com.br
 Podemos ver que o tempo foi mantido por volta de 9ms e que nenhum pacote foi nem rejeitado nem perdido.
```
PING www.google.com.br (172.217.29.163) 56(84) bytes of data.
64 bytes from gru10s02-in-f3.1e100.net (172.217.29.163): icmp_seq=1 ttl=56 time=7.66 ms
64 bytes from gru10s02-in-f3.1e100.net (172.217.29.163): icmp_seq=2 ttl=56 time=9.16 ms
64 bytes from gru10s02-in-f3.1e100.net (172.217.29.163): icmp_seq=3 ttl=56 time=8.62 ms
64 bytes from gru10s02-in-f3.1e100.net (172.217.29.163): icmp_seq=4 ttl=56 time=9.82 ms
64 bytes from gru10s02-in-f3.1e100.net (172.217.29.163): icmp_seq=5 ttl=56 time=8.68 ms
64 bytes from gru10s02-in-f3.1e100.net (172.217.29.163): icmp_seq=6 ttl=56 time=8.41 ms
64 bytes from gru10s02-in-f3.1e100.net (172.217.29.163): icmp_seq=7 ttl=56 time=8.81 ms
64 bytes from gru10s02-in-f3.1e100.net (172.217.29.163): icmp_seq=8 ttl=56 time=8.72 ms
64 bytes from gru10s02-in-f3.1e100.net (172.217.29.163): icmp_seq=9 ttl=56 time=8.53 ms
64 bytes from gru10s02-in-f3.1e100.net (172.217.29.163): icmp_seq=10 ttl=56 time=8.63 ms

--- www.google.com.br ping statistics ---
10 packets transmitted, 10 received, 0% packet loss, time 9014ms
rtt min/avg/max/mdev = 7.666/8.708/9.824/0.530 ms
```

#### www.meutimao.com.br
```
PING www.meutimao.com.br (104.20.7.243) 56(84) bytes of data.
64 bytes from 104.20.7.243 (104.20.7.243): icmp_seq=1 ttl=59 time=5.14 ms
64 bytes from 104.20.7.243 (104.20.7.243): icmp_seq=2 ttl=59 time=7.63 ms
64 bytes from 104.20.7.243 (104.20.7.243): icmp_seq=3 ttl=59 time=8.02 ms
64 bytes from 104.20.7.243 (104.20.7.243): icmp_seq=4 ttl=59 time=5.04 ms
64 bytes from 104.20.7.243 (104.20.7.243): icmp_seq=5 ttl=59 time=5.35 ms
64 bytes from 104.20.7.243 (104.20.7.243): icmp_seq=6 ttl=59 time=123 ms
64 bytes from 104.20.7.243 (104.20.7.243): icmp_seq=7 ttl=59 time=4.85 ms
64 bytes from 104.20.7.243 (104.20.7.243): icmp_seq=8 ttl=59 time=4.78 ms
64 bytes from 104.20.7.243 (104.20.7.243): icmp_seq=9 ttl=59 time=4.88 ms
64 bytes from 104.20.7.243 (104.20.7.243): icmp_seq=10 ttl=59 time=4.71 ms

--- www.meutimao.com.br ping statistics ---
10 packets transmitted, 10 received, 0% packet loss, time 9012ms
rtt min/avg/max/mdev = 4.716/17.347/123.041/35.249 ms
```

#### www.lolesports.com
```
PING a1496.f1.akamai.net (200.157.208.241) 56(84) bytes of data.
64 bytes from 200-157-208-241.ded.intelignet.com.br (200.157.208.241): icmp_seq=1 ttl=59 time=22.8 ms
64 bytes from 200-157-208-241.ded.intelignet.com.br (200.157.208.241): icmp_seq=2 ttl=59 time=24.5 ms
64 bytes from 200-157-208-241.ded.intelignet.com.br (200.157.208.241): icmp_seq=3 ttl=59 time=25.1 ms
64 bytes from 200-157-208-241.ded.intelignet.com.br (200.157.208.241): icmp_seq=4 ttl=59 time=26.0 ms
64 bytes from 200-157-208-241.ded.intelignet.com.br (200.157.208.241): icmp_seq=5 ttl=59 time=25.8 ms
64 bytes from 200-157-208-241.ded.intelignet.com.br (200.157.208.241): icmp_seq=6 ttl=59 time=25.4 ms
64 bytes from 200-157-208-241.ded.intelignet.com.br (200.157.208.241): icmp_seq=7 ttl=59 time=26.3 ms
64 bytes from 200-157-208-241.ded.intelignet.com.br (200.157.208.241): icmp_seq=8 ttl=59 time=25.8 ms
64 bytes from 200-157-208-241.ded.intelignet.com.br (200.157.208.241): icmp_seq=9 ttl=59 time=25.3 ms
64 bytes from 200-157-208-241.ded.intelignet.com.br (200.157.208.241): icmp_seq=10 ttl=59 time=26.4 ms

--- a1496.f1.akamai.net ping statistics ---
10 packets transmitted, 10 received, 0% packet loss, time 9013ms
rtt min/avg/max/mdev = 22.820/25.385/26.405/1.004 ms
```

#### www.lolhehehe.com.br
```
PING lolhehehe.com.br (192.185.216.154) 56(84) bytes of data.
64 bytes from srv56-ip05.prodns.com.br (192.185.216.154): icmp_seq=1 ttl=46 time=142 ms
64 bytes from srv56-ip05.prodns.com.br (192.185.216.154): icmp_seq=2 ttl=46 time=145 ms
64 bytes from srv56-ip05.prodns.com.br (192.185.216.154): icmp_seq=3 ttl=46 time=145 ms
64 bytes from srv56-ip05.prodns.com.br (192.185.216.154): icmp_seq=4 ttl=46 time=145 ms
64 bytes from srv56-ip05.prodns.com.br (192.185.216.154): icmp_seq=5 ttl=46 time=145 ms
64 bytes from srv56-ip05.prodns.com.br (192.185.216.154): icmp_seq=6 ttl=46 time=142 ms
64 bytes from srv56-ip05.prodns.com.br (192.185.216.154): icmp_seq=7 ttl=46 time=144 ms
64 bytes from srv56-ip05.prodns.com.br (192.185.216.154): icmp_seq=8 ttl=46 time=145 ms
64 bytes from srv56-ip05.prodns.com.br (192.185.216.154): icmp_seq=9 ttl=46 time=145 ms
64 bytes from srv56-ip05.prodns.com.br (192.185.216.154): icmp_seq=10 ttl=46 time=145 ms

--- lolhehehe.com.br ping statistics ---
10 packets transmitted, 10 received, 0% packet loss, time 9009ms
rtt min/avg/max/mdev = 142.418/144.672/145.645/1.143 ms
```

#### www.caco.ic.unicamp.br
```
PING lambari.caco.ic.unicamp.br (143.106.73.184) 56(84) bytes of data.
64 bytes from lambari.caco.ic.unicamp.br (143.106.73.184): icmp_seq=1 ttl=55 time=9.44 ms
64 bytes from lambari.caco.ic.unicamp.br (143.106.73.184): icmp_seq=2 ttl=55 time=11.7 ms
64 bytes from lambari.caco.ic.unicamp.br (143.106.73.184): icmp_seq=3 ttl=55 time=11.5 ms
64 bytes from lambari.caco.ic.unicamp.br (143.106.73.184): icmp_seq=4 ttl=55 time=11.3 ms
64 bytes from lambari.caco.ic.unicamp.br (143.106.73.184): icmp_seq=5 ttl=55 time=11.5 ms
64 bytes from lambari.caco.ic.unicamp.br (143.106.73.184): icmp_seq=6 ttl=55 time=16.4 ms
64 bytes from lambari.caco.ic.unicamp.br (143.106.73.184): icmp_seq=7 ttl=55 time=11.1 ms
64 bytes from lambari.caco.ic.unicamp.br (143.106.73.184): icmp_seq=8 ttl=55 time=11.1 ms
64 bytes from lambari.caco.ic.unicamp.br (143.106.73.184): icmp_seq=9 ttl=55 time=11.2 ms
64 bytes from lambari.caco.ic.unicamp.br (143.106.73.184): icmp_seq=10 ttl=55 time=9.86 ms

--- lambari.caco.ic.unicamp.br ping statistics ---
10 packets transmitted, 10 received, 0% packet loss, time 9011ms
rtt min/avg/max/mdev = 9.443/11.541/16.478/1.791 ms
```

### b) Verifique se o host www.lrc.ic.unicamp.br é alcançável utilizando a ferramenta ping. Depois, acesse a URL no seu browser. Explique.
Ao pingar o servidor com `ping -c 1 www.lrc.ic.unicamp.br`, temos
```
PING lrc-gw.ic.unicamp.br (143.106.7.163) 56(84) bytes of data.

--- lrc-gw.ic.unicamp.br ping statistics ---
5 packets transmitted, 0 received, 100% packet loss, time 4060ms
```
no entanto conseguimos acessar o site atravez de um navegador.Isso acontece por que muitos servidores derrubam os pacotes ICMP como um meio de protecao do ataque DDoS e ao entrarmos no site utilizamos o protocolo HTTP sobre TCP.

### c) Mostre passo a passo e explique: Descubra o endereço IP da sua máquina utilizando alguma ferramenta vista em sala. Identifique qual interface de rede está sendo utilizada para transmitir dados entre o seu computador e a Internet. Identifique a interface de "loopback" e utilize uma das ferramentas para alterar o nÃºmero de pacotes enviados e recebidos.

Para descobrir as interfaces de rede do computador rodamos  `ifconfig`
Como está conectado via wifi, foi utilizado `ifconfig wlp2s0` para mostrar informações dessa interface
```
wlp2s0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 177.220.85.135  netmask 255.255.254.0  broadcast 177.220.85.255
        inet6 fe80::22b6:e32a:5bdc:fafd  prefixlen 64  scopeid 0x20<link>
        ether 44:1c:a8:e2:c5:c3  txqueuelen 1000  (Ethernet)
        RX packets 38447  bytes 41327549 (39.4 MiB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 24253  bytes 3898565 (3.7 MiB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
```
### d) Identifique a rota padrão na sua máquina.
Para descobrir as rotas no computador utilizamos o comando `route`. Ele retorna o seguinte conteúdo:
```
Kernel IP routing table
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
default         177.220.84.1    0.0.0.0         UG    600    0        0 wlp2s0
172.17.0.0      0.0.0.0         255.255.0.0     U     0      0        0 docker0
172.19.0.0      0.0.0.0         255.255.0.0     U     0      0        0 br-3b522c1dbb94
172.20.0.0      0.0.0.0         255.255.0.0     U     0      0        0 br-6eaf0dc39823
172.21.0.0      0.0.0.0         255.255.0.0     U     0      0        0 br-e0cf9dd24962
177.220.84.0    0.0.0.0         255.255.254.0   U     600    0        0 wlp2s0
```

### e) Qual é o servidor DNS configurado na sua estação? Obtenha os endereços IP de www.ic.unicamp.br, www.unicamp.br, www.usp.br, www.unesp.br, www.cs.man.ac.uk, www.u-tokyo.ac.jp.
`traceroute $URL`
#### www.ic.unicamp.br
```
traceroute to www.ic.unicamp.br (143.106.7.54), 30 hops max, 60 byte packets
 1  wifi-177-220-85-253.wifi.ic.unicamp.br (177.220.85.253)  2.847 ms  2.809 ms  2.791 ms
 2  atibaia.ic.unicamp.br (143.106.7.54)  2.746 ms  2.713 ms  2.691 ms
```

#### www.unicamp.br
```
traceroute to www.unicamp.br (143.106.10.174), 30 hops max, 60 byte packets
 1  wifi-177-220-85-253.wifi.ic.unicamp.br (177.220.85.253)  2.005 ms  2.000 ms  2.801 ms
 2  area3-gw.unicamp.br (143.106.1.129)  2.610 ms  2.932 ms  3.771 ms
 3  ptp-ncc-nbs.unicamp.br (143.106.199.9)  8.689 ms  8.813 ms  9.001 ms
 4  dmz-gw.unicamp.br (143.106.2.52)  3.724 ms  3.961 ms  3.953 ms
 5  cerejeira.unicamp.br (143.106.10.174)  3.215 ms  3.363 ms  3.503 ms
```

#### www.usp.br
```
traceroute to www.usp.br (200.144.248.41), 30 hops max, 60 byte packets
 1  wifi-177-220-85-253.wifi.ic.unicamp.br (177.220.85.253)  1.841 ms  1.814 ms  2.390 ms
 2  area3-gw.unicamp.br (143.106.1.129)  1.989 ms  2.503 ms  3.261 ms
 3  * ptp-nct-nbs.unicamp.br (143.106.199.13)  2.646 ms  3.242 ms
 4  as28571.saopaulo.sp.ix.br (187.16.216.20)  4.669 ms  4.370 ms  5.384 ms
 5  border2.uspnet.usp.br (143.107.151.42)  5.782 ms  6.273 ms  6.827 ms
 6  143.107.249.38 (143.107.249.38)  6.439 ms  5.452 ms  5.324 ms
 7  * * *
 8  * * *
 9  * * *
10  * * *
11  * * *
12  * * *
13  * * *
14  * * *
15  * * *
16  * * *
17  * * *
18  * * *
19  * * *
20  * * *
21  * * *
22  * * *
23  * * *
24  * * *
25  * * *
26  * * *
27  * * *
28  * * *
29  * * *
30  * * *
```

#### www.unesp.br
```
traceroute to www.unesp.br (200.145.6.90), 30 hops max, 60 byte packets
 1  wifi-177-220-85-253.wifi.ic.unicamp.br (177.220.85.253)  1.847 ms  1.817 ms  2.766 ms
 2  area3-gw.unicamp.br (143.106.1.129)  2.610 ms  3.154 ms  3.275 ms
 3  ptp-ncc-nbs.unicamp.br (143.106.199.9)  11.633 ms  11.771 ms  11.943 ms
 4  * * *
 5  rt-asr.net.unesp.br (200.145.0.253)  6.548 ms  6.539 ms  6.721 ms
 6  * * *
 7  * * *
 8  * * *
 9  * * *
10  * * *
11  * * *
12  * * *
13  * * *
14  * * *
15  * * *
16  * * *
17  * * *
18  * * *
19  * * *
20  * * *
21  * * *
22  * * *
23  * * *
24  * * *
25  * * *
```
#### www.cs.man.ac.uk
```
traceroute to www.cs.man.ac.uk (130.88.199.17), 30 hops max, 60 byte packets
 1  wifi-177-220-85-253.wifi.ic.unicamp.br (177.220.85.253)  2.123 ms  3.485 ms  3.611 ms
 2  area3-gw.unicamp.br (143.106.1.129)  4.546 ms  4.533 ms  4.521 ms
 3  ptp-ncc-nbs.unicamp.br (143.106.199.9)  17.172 ms *  17.323 ms
 4  * * *
 5  sp-sp2.bkb.rnp.br (200.143.253.37)  8.910 ms  8.892 ms  8.870 ms
 6  et-3-3-0.469.rtsw.wash.net.internet2.edu (64.57.28.61)  187.874 ms  185.281 ms  182.464 ms
 7  internet2-gw.mx1.lon.uk.geant.net (62.40.124.44)  258.253 ms  259.137 ms  258.366 ms
 8  janet-gw.mx1.lon.uk.geant.net (62.40.124.198)  257.546 ms  257.651 ms  257.976 ms
 9  ae29.londpg-sbr2.ja.net (146.97.33.2)  259.172 ms  257.707 ms  257.881 ms
10  ae31.erdiss-sbr2.ja.net (146.97.33.22)  261.970 ms  263.119 ms  262.839 ms
11  ae29.manckh-sbr1.ja.net (146.97.33.42)  265.878 ms  306.152 ms  307.063 ms
12  nnw.manckh-sbr1.ja.net (146.97.41.62)  308.099 ms  307.388 ms  308.452 ms
13  gw-man-kb2.netnw.net.uk (194.66.27.18)  308.422 ms  308.389 ms  308.384 ms
14  gw-uom-kb.its.manchester.ac.uk (194.66.26.102)  308.367 ms  308.348 ms  308.341 ms
15  130.88.249.185 (130.88.249.185)  308.290 ms  308.252 ms  308.265 ms
16  gw-jh.cnw.its.manchester.ac.uk (130.88.249.178)  308.236 ms  308.212 ms  308.137 ms
17  130.88.250.35 (130.88.250.35)  308.558 ms  309.904 ms  265.173 ms
18  gw-kilburn.its.manchester.ac.uk (192.84.75.10)  304.506 ms  304.380 ms  304.412 ms
19  waldorf.cs.man.ac.uk (130.88.199.17)  303.670 ms !X  303.822 ms !X  304.208 ms !X
```

#### www.u-tokyo.ac.jp
```
traceroute to www.u-tokyo.ac.jp (210.152.135.178), 30 hops max, 60 byte packets
 1  wifi-177-220-85-253.wifi.ic.unicamp.br (177.220.85.253)  2.703 ms  2.815 ms  3.096 ms
 2  area3-gw.unicamp.br (143.106.1.129)  2.949 ms  3.685 ms  3.719 ms
 3  ptp-nct-nbs.unicamp.br (143.106.199.13)  3.165 ms *  3.601 ms
 4  * * *
 5  sp-sp2.bkb.rnp.br (200.143.253.37)  12.736 ms  13.834 ms  13.803 ms
 6  mia2-sp-par-pac.bkb.rnp.br (200.143.252.34)  159.046 ms  156.298 ms  156.643 ms
 7  xe-0-0-26-2.a01.miamfl02.us.bb.gin.ntt.net (129.250.202.93)  165.761 ms  165.953 ms  166.099 ms
 8  ae-5.r05.miamfl02.us.bb.gin.ntt.net (129.250.3.166)  323.536 ms  324.939 ms  323.667 ms
 9  ae-4.r21.miamfl02.us.bb.gin.ntt.net (129.250.3.172)  157.466 ms  157.326 ms  157.801 ms
10  ae-4.r22.dllstx09.us.bb.gin.ntt.net (129.250.2.219)  185.391 ms  184.658 ms  184.835 ms
11  ae-5.r22.lsanca07.us.bb.gin.ntt.net (129.250.7.69)  211.182 ms  214.993 ms  217.958 ms
12  ae-15.r25.osakjp02.jp.bb.gin.ntt.net (129.250.2.177)  326.055 ms  330.283 ms  324.275 ms
13  ae-24.r01.osakjp02.jp.bb.gin.ntt.net (129.250.5.49)  318.493 ms  319.774 ms  329.923 ms
14  xe-0-4-0-7.r01.osakjp02.jp.ce.gin.ntt.net (61.200.80.218)  327.023 ms  326.016 ms  325.188 ms
15  * * *
16  * * *
17  * * *
18  * * *
19  * * *
20  * * *
21  * * *
22  * * *
23  * * *
24  * * *
25  * * *
26  * * *
27  * * *
28  * * *
29  * * *
30  * * *
```

### f) Quais e quantos são os roteadores identificáveis nos caminhos para os endereços do item (e)? Identifique enlaces de longa distÃ¢ncia para o endereço fora do Brasil e explique como fez para identificá-los.

### g) Identifique 5 conexões TCP do seu computador, bem como as portas de origem e destino. Acesse o site www.unicamp.br e repita o comando que utilizou para identificar as conexões. Apresente as informações que encontrou sobre a conexão com www.unicamp.br.

```
tcp        0      0 wifi-177-220-85-1:42196 lga25s56-in-f4.1e:https ESTABLISHED
tcp        0      0 wifi-177-220-85-1:44820 209.85.224.186:https    ESTABLISHED
tcp        0      0 wifi-177-220-85-1:35020 gru09s19-in-f14.1:https ESTABLISHED
tcp        0      0 wifi-177-220-85-1:42760 lga25s60-in-f1.1e:https TIME_WAIT
tcp        0      0 wifi-177-220-85-1:35796 gru06s26-in-f10.1:https ESTABLISHED
tcp        0      0 wifi-177-220-85-1:59810 lga25s60-in-f3.1e:https ESTABLISHED
tcp        0      0 wifi-177-220-85-1:42752 lga25s60-in-f1.1e:https TIME_WAIT
tcp        0      0 wifi-177-220-85-1:35040 gru09s19-in-f14.1:https TIME_WAIT
tcp        0      0 wifi-177-220-85-1:42758 lga25s60-in-f1.1e:https TIME_WAIT
tcp        0      0 wifi-177-220-85-1:35016 gru09s19-in-f14.1:https ESTABLISHED
tcp        0      0 wifi-177-:EtherNet-IP-2 209.85.224.186:https    ESTABLISHED
tcp        0      0 wifi-177-220-85-1:42756 lga25s60-in-f1.1e:https TIME_WAIT
tcp        0      0 wifi-177-220-85-1:35066 gru09s19-in-f14.1:https ESTABLISHED
tcp        0      0 wifi-177-220:traceroute 173.194.27.201:https    ESTABLISHED
tcp        0      0 wifi-177-220-85-1:35026 gru09s19-in-f14.1:https ESTABLISHED
tcp        0      0 wifi-177-220-85-1:35036 gru09s19-in-f14.1:https ESTABLISHED
tcp        0      0 wifi-177-220-85-1:35024 gru09s19-in-f14.1:https ESTABLISHED
tcp        0      0 wifi-177-220-85-1:38878 gru09s19-in-f6.1e:https ESTABLISHED
tcp        0      0 wifi-177-220-85-1:42762 lga25s60-in-f1.1e:https ESTABLISHED
tcp        0      0 wifi-177-220-85-1:35238 lga25s60-in-f1:www-http ESTABLISHED
tcp        0      0 wifi-177-220-85-1:39992 server-52-85-1:www-http ESTABLISHED
tcp        0      0 wifi-177-220-85-1:33436 173.194.27.201:https    ESTABLISHED
tcp        0      0 wifi-177-220-85-1:38168 ec2-107-21-1-61.c:https ESTABLISHED
tcp        0      0 wifi-177-220-85-1:53880 ec2-54-210-192-22:https ESTABLISHED
tcp        0      0 wifi-177-220-85-1:35252 lga25s60-in-f1:www-http ESTABLISHED
tcp        0      0 wifi-177-220-85-1:42754 lga25s60-in-f1.1e:https TIME_WAIT
tcp        0      0 wifi-177-220-85-1:35254 lga25s60-in-f1:www-http TIME_WAIT
tcp        0      0 wifi-177-220-85-1:49198 173.194.27.215:https    ESTABLISHED
tcp        0      0 wifi-177-220-85-1:49196 173.194.27.215:https    ESTABLISHED
```

### h)  Utilize telnet para receber o arquivo html da página http://www.ic.unicamp.br/~reltech/ e apresente no relatório os passos utilizados, explicando-os. Tente, de forma similar, realizar uma conexão telnet com localhost. O que ocorre? Por que?


#### www.ic.unicamp.br/~reltech
Para acessar o site http://www.ic.unicamp.br/~reltech atravez do telnet primeiramente precisamos conectar atravez da porta 80 no site utilizando o seuinte comando
```
telnet www.ic.unicamp.br 80
```
ao conectarmos no site podemos utilizar o protocolo HTTP e enviar uma requisição GET para a página desejada, o seja:
```
GET /~reltech/
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 3.2 Final//EN">
<html>
<head>
  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
  <title>Relatórios Técnicos - Technical Reports — Instituto de
Computação - UNICAMP</title>
</head>
<body style="background-color: rgb(255, 255, 234);">
<div
 style="border: 0pt none ; background-color: rgb(0, 0, 140); padding-bottom: 70px;">
<img src="imagens/logo.jpg" align="left"> <img
 src="imagens/logo_unicamp.png" height="65" align="right" width="56"> </div>
<div style="color: rgb(0, 0, 140); margin-left: 80px;" alink="#ee0000"
 link="#0000ee" vlink="#551a8b">
<h3 style="font-family: Lucida Grande,sans-serif; font-size: 100%;">Relatórios
Técnicos
- Technical Reports</h3>
<h3 style="font-family: Lucida Grande,sans-serif; font-size: 80%;">
Acesso aos Relatórios Técnicos - Access to Technical Reports</h3>
<div style="width: 20cm; text-align: justify;">
<table
 style="width: 350pt; margin-left: 36pt; border-collapse: collapse;"
 cellpadding="0" cellspacing="0" width="350">
  <tbody>
     <tr>
      <td><a href=""></a></td>
      <td><a href=""></a></td>
      <td><a href="2017/abstracts.html">2017</a></td>
       <td><a href="2016/abstracts.html">2016</a></td>
    </tr>
     <tr>
      <td><a href="2015/abstracts.html">2015</a></td>
      <td><a href="2014/abstracts.html">2014</a></td>
      <td><a href="2013/abstracts.html">2013</a></td>
      <td><a href="2012/abstracts.html">2012</a></td>
    </tr>
    <tr>
      <td><a href="2011/abstracts.html">2011</a></td>
      <td><a href="2010/abstracts.html">2010</a></td>
      <td><a href="2009/abstracts.html">2009</a></td>
      <td><a href="2008/abstracts.html">2008</a></td>
    </tr>
    <tr>
      <td><a href="2007/abstracts.html">2007</a></td>
      <td><a href="2006/abstracts.html">2006</a></td>
      <td><a href="2005/abstracts.html">2005</a></td>
      <td><a href="2004/abstracts.html">2004</a></td>
    </tr>
    <tr>
      <td><a href="2003/abstracts.html">2003</a></td>
      <td><a href="2002/abstracts.html">2002</a></td>
      <td><a href="2001/abstracts.html">2001</a></td>
      <td><a href="2000/abstracts.html">2000</a></td>
    </tr>
    <tr>
      <td><a href="1999/abstracts.html">1999</a></td>
      <td><a href="1998/abstracts.html">1998</a></td>
      <td><a href="1997/abstracts.html">1997</a></td>
      <td><a href="1996/abstracts.html">1996</a></td>
    </tr>
    <tr>
      <td><a href="1995/abstracts.html">1995</a></td>
      <td><a href="1994/abstracts.html">1994</a></td>
      <td><a href="1993/abstracts.html">1993</a></td>
      <td><a href="1992/abstracts.html">1992</a></td>
    </tr>
  </tbody>
</table>
</div>

<h3 style="font-family: Lucida Grande,sans-serif; font-size: 80%;">
Relatórios de PFG - Undergrad Final Project Reports</h3>
<div style="width: 20cm; text-align: justify;">
<table
 style="width: 350pt; margin-left: 36pt; border-collapse: collapse;"
 cellpadding="0" cellspacing="0" width="350">
  <tbody>
     <tr>
      <td><a href=""></a></td>
      <td><a href=""></a></td>
      <td><a href=""></a></td>
      <td><a href="PFG/2016/abstracts.html">2016</a></td>
    </tr>
  </tbody>
</table>
</div>



<h3 style="font-family: Lucida Grande,sans-serif; font-size: 100%;">Contato
-
Contact
us</h3>
<a href="mailto:reltech@ic.unicamp.br">editores - editors</a>
<h3 style="font-family: Lucida Grande,sans-serif; font-size: 100%;">Autores</h3>
<a href="instrucoes.html">instruções</a> </div>
<hr>
<div style="background-color: rgb(255, 255, 238);"> <img
 src="imagens/logo_unicamp_50anos.png" height="66" hspace="0"
 align="left" width="122">
<table border="0" cellpadding="5" cellspacing="5" width="100%">
  <tbody>
    <tr>
      <td align="right">
      <div style="text-align: center;"> Instituto de Computação ::
Universidade Estadual de Campinas <br>
Av. Albert Einstein, 1251 - Cidade Universitária Zeferino Vaz •
13083-852 Campinas, SP - Brasil • Fone: [19] 3521-5838 </div>
      </td>
    </tr>
  </tbody>
</table>
</div>
<div><br>
</div>
</body>
</html>
Connection closed by foreign host.
```

#### localhost
ao tentar realizar uma conexão com localhost obtemos o seguinte
```
Trying ::1...
Connection failed: Conexão recusada
Trying 127.0.0.1...
telnet: Unable to connect to remote host: Conexão recusada
```

isso ocorre por que a máquina não está servindo um servidor http para que seja possível ela se conectar.
