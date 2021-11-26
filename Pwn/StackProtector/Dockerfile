FROM ubuntu
RUN apt update -y && apt install -y tcpd xinetd make gcc gcc-multilib
RUN useradd stack_protector
COPY ./app/stack-protector-config /etc/xinetd.d/stack_protector
COPY ./app/src/main.c /main.c
COPY ./app/Makefile /Makefile
COPY ./app/flag.txt /flag.txt
RUN chmod 666 /flag.txt
RUN make docker
EXPOSE 18181
CMD xinetd -dontfork
