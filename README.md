[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/G8V_0Zaq)

# Tarefa: IoT Security Lab - EmbarcaTech 2025

Autor: **Danilo Naves do Nascimento e Gabriel**

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Brasília, 27 de Maio de 2025

---

# Introdução

Colocar aqui a introdução da atividade

## 1. Configuração/inicialização do Wi-fi

Para configurar o wifi, já existe uma função fornecida para isso. Então foi apenas necessário trocar as informações de conexão de rede.

```c
connect_to_wifi("Nome do Wifi", "Senha");
```

![Configuração finalizada](./img/conf-wifi.png)

| Conexão feita com wi-fi

## 2.  Configuração do Broker Local - Mosquitto

Para inicializar e configurar o mosquitto no Fedora 42 foi adicionado as seguintes linhas no arquivo ```/etc/mosquitto/mosquitto.conf```

```shell
listener 1883 0.0.0.0 // Porta padrão e aceitar endereços Ip de diferentes máquinas
```

```shell
allow_anonymous falso // Modo com autenticação
password_file /etc/mosquitto/passwd // Configuração com usuários para autenticação
```

Após isso, inicializar o servidor mosquitto com o seguinte comando:

```
sudo mosquitto -c /etc/mosquitto/mosquitto.conf -v // "-c" para indicar caminho do arquivo de configuração. "-v" para apresentar todos os logs de mensagem.
```

![Inicialização mosquitto](img/conf-mosquitto.png)

Após a configuração do broker, é necessário configurar o endereço ip, nome e senha do broker na bitdoglab.

O código fornecido já possui um função preparada para somente passar os parâmetros corretos.

![Login no Broker](/img/broker-bitdoglab.png)

| O ip `192.168.15.14` é o ip do broker.

| Os outros campos são, respectivamente, `Nome do cliente`, `Nome de usuário` e `Senha de usuário`.

Por fim, a pico W já está pronta para enviar mensagens aos tópicos.

## Envio de mensagens a tópicos

Para enviar mensagem a um tópico, foi utilizado a função `mqtt_comm_publish`

![Função de envio de mensagem sem criptografia](/img/msg-nocrypt.png)

Ao enviar a mensagem, a seguinte mensagem é printada no terminal serial da bitdoglab.

![Mensagem MQTT enviada](/img/serial-msg-send.png)

No wireshark, é possível ver o corpo da mensagem

![Informações a claras](/img/wireshark-nocrypt.png)

## Teste de autenticação e Criptografia

Caso o cliente use algum usuário ou senha não cadastrada no `/etc/mosquitto/passwd`, é retornado o erro `not authorised`.

![Usuário não conectado](/img/not-authorised.png)

Caso o usuário seja autenticado. A conexão com o broker será feita com sucesso.

![Novo usuário conectado](/img/client-connect.png)

Um problema notável é a falta de privacidade sobre as informações acerca dos tópicos e dos corpos das mensagens. Sem uma criptografia, o pacote MQTT pode sofrer atacantes conhecido como Man-the-Middle, onde o atacante pode ler os corpos do pacote, alterar e fazer tentativas de replays.



---

## 📜 Licença
GNU GPL-3.0.
