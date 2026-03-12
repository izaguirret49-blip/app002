FROM gcc:13

WORKDIR /app

COPY . .

RUN g++ -std=c++17 -O2 -pthread main.cpp server.cpp -o app

EXPOSE 10000

CMD ["sh", "-c", "./app"]
