FROM alpine:3.16
RUN apk add --no-cache gcc musl-dev

COPY ./src/main.c .

# command for build application
RUN gcc -o main main.c -lpthread

#CMD ["/main"]
ENTRYPOINT ["/bin/sh", "-c", "./main"]