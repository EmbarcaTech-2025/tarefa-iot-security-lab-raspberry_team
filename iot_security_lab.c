// Bibliotecas necessárias
#include <string.h>                 // Para funções de string como strlen()
#include "pico/stdlib.h"            // Biblioteca padrão do Pico (GPIO, tempo, etc.)
#include "pico/cyw43_arch.h"        // Driver WiFi para Pico W
#include "include/wifi_conn.h"      // Funções personalizadas de conexão WiFi
#include "include/mqtt_comm.h"      // Funções personalizadas para MQTT
#include "include/xor_cipher.h"     // Funções de cifra XOR

#include <time.h>

int main() {
    // Inicializa todas as interfaces de I/O padrão (USB serial, etc.)
    stdio_init_all();
    
    // Conecta à rede WiFi
    // Parâmetros: Nome da rede (SSID) e senha
    connect_to_wifi("AP-ACCESS BLH", "Fin@ApointBlH");

    // Configura o cliente MQTT
    // Parâmetros: ID do cliente, IP do broker, usuário, senha
    mqtt_setup("bitdog10", "192.168.15.14", "aluno", "senha123");

    // Mensagem original a ser enviada
    char mensagem[1000];
    // Buffer para mensagem criptografada (16 bytes)
    uint8_t criptografada[16];
    // Criptografa a mensagem usando XOR com chave 42

    // Loop principal do programa
    bool inscrito = false;  // Flag para garantir que só assine uma vez

    while (true) {
        if (!inscrito) {
            mqtt_comm_subscribe("escola/sala1/temperatura");
            inscrito = true;
        }

        // Mensagem com time
        sprintf(mensagem, "{\"Messagem\":\"Mensagem secreta!\",\"ts\":%lu}", time(NULL));

        xor_encrypt((uint8_t *)mensagem, criptografada, strlen(mensagem), 42);

        printf("Data: %lu", time(NULL));

        // Publica a mensagem original (não criptografada)
        //mqtt_comm_publish("escola/sala1/temperatura", mensagem, strlen(mensagem));

        // Alternativa: Publica a mensagem criptografada
        mqtt_comm_publish("escola/sala1/temperatura", criptografada, strlen(mensagem));

        // Aguarda 5 segundos antes da próxima publicação
        sleep_ms(5000);
    }
    return 0;
}

/* 
 * Comandos de terminal para testar o MQTT:
 * 
 * Inicia o broker MQTT com logs detalhados:
 * mosquitto -c mosquitto.conf -v
 * 
 * Assina o tópico de temperatura (recebe mensagens):
 * mosquitto_sub -h localhost -p 1883 -t "escola/sala1/temperatura" -u "aluno" -P "senha123"
 * 
 * Publica mensagem de teste no tópico de temperatura:
 * mosquitto_pub -h localhost -p 1883 -t "escola/sala1/temperatura" -u "aluno" -P "senha123" -m "26.6"
 */