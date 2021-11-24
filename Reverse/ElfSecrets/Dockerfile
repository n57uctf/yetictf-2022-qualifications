FROM ubuntu
RUN apt update -y
RUN apt install -y tcpd xinetd
RUN useradd elf
COPY app/elf-server-config /etc/xinetd.d/elf-server
COPY app/bin/elf-server /elf-server
COPY app/bin/elf /elf
COPY app/flag/flag.png /flag.png
RUN chmod 666 flag.png
RUN chmod 666 elf
EXPOSE 8888
CMD xinetd -dontfork
