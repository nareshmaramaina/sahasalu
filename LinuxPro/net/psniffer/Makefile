#Target : Dependencies 
#<TAB>	commands to acheive target

all: main.o ip.o arp.o rarp.o ./ip/tcp.o ./ip/udp.o ./ip/icmp.o \
          ./ip/igmp.o
	@gcc -w main.o ip.o arp.o rarp.o ./ip/tcp.o ./ip/udp.o ./ip/icmp.o \
        ./ip/igmp.o -o sniffer
	@echo "target created successfully"

main.o : main.c
	@gcc -w -c main.c -o main.o
	@echo "main.o created succesfully"

ip.o : ip.c
	@gcc -w -c ip.c -o ip.o
	@echo "ip.o created successfully"

arp.o : arp.c
	@gcc -w -c arp.c -o arp.o
	@echo "arp.o created successfully"

rarp.o : rarp.c
	@gcc -w -c rarp.c -o rarp.o
	@echo "rarp.o created successfully"

tcp.o : tcp.c
	@gcc -w -c ./ip/tcp.c -o ./ip/tcp.o
	@echo "tcp.o created successfully"

udp.o : udp.c
	@gcc -w -c ./ip/udp.c -o ./ip/udp.o
	@echo "udp.o created successfully"

icmp.o : icmp.c
	@gcc -w -c ./ip/icmp.c -o ./ip/icmp.o
	@echo "icmp.o created successfully"

igmp.o : igmp.c
	@gcc -w -c ./ip/igmp.c -o ./ip/igmp.o
	@echo "igmp.o created successfully"

clean : 	
	@rm *.o
	@rm ./ip/*.o 	
