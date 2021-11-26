FROM ubuntu
RUN apt update -y && apt install -y tcpd xinetd make gcc
RUN useradd near
COPY ./app/near-config /etc/xinetd.d/near
COPY ./app/src/main.c /main.c
COPY ./app/Makefile /Makefile
COPY ./app/flag.txt /flag.txt
RUN chmod 666 /flag.txt
RUN make docker
EXPOSE 20201
CMD xinetd -dontfork
