FROM golang:latest 
RUN mkdir /app 
ADD ./app/main.go /app/ 
WORKDIR /app 
RUN go build ./main.go
EXPOSE 502/tcp
CMD ["/app/main"]
