FROM ubuntu
RUN apt update -y
RUN apt install -y tcpd xinetd
RUN useradd elf
COPY elf-server-config /etc/xinetd.d/elf-server
COPY bin/elf-server /elf-server
COPY bin/elf /elf
COPY flag/flag.png /flag.png
RUN chmod 666 flag.png
RUN chmod 666 elf
CMD xinetd -dontfork
