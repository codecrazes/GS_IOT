# 🌡️ Projeto IoT – Monitoramento Ambiental com ESP32, DHT22 e ThingSpeak

## 📌 Descrição do Projeto

Este projeto tem como objetivo criar uma solução de monitoramento ambiental utilizando a placa **ESP32**, o sensor **DHT22** para captar temperatura e umidade, e LEDs para indicar situações de alerta. Os dados são enviados para a plataforma **ThingSpeak**, onde podem ser visualizados em tempo real através de um dashboard.

---

## ⚙️ Componentes Utilizados

- ESP32 DevKit V1
- Sensor DHT22
- LED Vermelho (alerta)
- LED Verde (ambiente estável)
- Plataforma ThingSpeak
- Conexão Wi-Fi

---

## 🚀 Fluxo de Funcionamento

1. O ESP32 inicializa e conecta-se à rede Wi-Fi.
2. O sensor DHT22 coleta dados de **temperatura** e **umidade**.
3. O ESP32 lê os dados e ativa:
   - **LED vermelho** caso os valores estejam fora da faixa segura (temp < 12°C ou > 35°C / umidade < 40% ou > 70%)
   - **LED verde** se os dados estiverem dentro dos limites aceitáveis.
4. Os dados (temperatura, umidade e velocidade do vento simulada) são enviados via HTTP para a plataforma **ThingSpeak**.
5. Na **dashboard do ThingSpeak**, os dados são visualizados graficamente em tempo real.

---

## 📘 Instruções Didáticas (Configuração, Execução e Testes)

### 🛠️ Configuração

1. **Hardware**:
   - Conecte o DHT22 à porta D15.
   - Conecte LEDs:
     - LED vermelho no pino D13.
     - LED verde no pino D12.
   - Alimente o ESP32 com 3.3V e GND.

2. **ThingSpeak**:
   - Acesse: [https://thingspeak.com](https://thingspeak.com)
   - Crie um canal com 3 campos: Temperatura, Umidade e Velocidade do Vento.
   - Copie a sua **Write API Key**.

3. **IDE / Simulador**:
   - Use o [Wokwi](https://wokwi.com/) ou Arduino IDE com a biblioteca `DHT`.
   - Configure a conexão Wi-Fi no código.
   - Insira a API_KEY copiada do ThingSpeak.

---

### ▶️ Execução

1. Faça o upload do código para o ESP32 (ou rode no simulador).
2. Aguarde a conexão Wi-Fi.
3. Veja os dados sendo enviados ao ThingSpeak a cada 15 segundos.
4. Observe os LEDs:
   - Verde: dados normais.
   - Vermelho: alerta de temperatura/umidade fora do padrão.

---

### 🧪 Testes da Aplicação

- **Temperatura**: modifique manualmente (no simulador) ou aproxime calor/frio real para testar os limites de ativação dos LEDs.
- **Umidade**: simule valores baixos/altos para acionar o LED vermelho.
- **Velocidade do vento**: é gerada aleatoriamente para testes.

Valide os dados diretamente na **dashboard do ThingSpeak**.

---

## 📊 Dashboard no ThingSpeak

A dashboard foi configurada com 3 gráficos:

- **Temperatura (Field1)**
- **Umidade (Field2)**
- **Velocidade do Vento (Field3)**

Atualização a cada 15 segundos, com visualização contínua dos dados.

---

## 🧭 Passo a Passo Resumido

1. Monte o circuito com ESP32 + DHT22 + LEDs.
2. Configure canal no ThingSpeak.
3. Suba o código com Wi-Fi e API_KEY corretos.
4. Verifique os gráficos e LEDs em ação.

## 🔁 Fluxo Detalhado da Comunicação

Este projeto envolve um fluxo contínuo e automático de dados entre três componentes principais:

### 1. Sensor e Dispositivo (ESP32 + DHT22)

- O ESP32 conectado ao sensor DHT22 faz leituras periódicas de **temperatura** e **umidade**.
- Também é gerada uma simulação da **velocidade do vento** para enriquecer os dados.
- Com base nesses valores, o ESP32 aciona dois LEDs para indicar:
  - **LED Verde:** ambiente estável, dentro das faixas de temperatura e umidade consideradas seguras.
  - **LED Vermelho:** alerta para condições extremas (temperatura ou umidade fora da faixa segura).
- Esse dispositivo atua como um **gateway local**, realizando o pré-processamento dos dados.

### 2. Comunicação via Wi-Fi

- O ESP32 se conecta a uma rede Wi-Fi (neste projeto, rede “Wokwi-GUEST” para simulação).
- A cada 15 segundos, o ESP32 monta uma requisição HTTP do tipo GET contendo os dados coletados.
- Essa requisição é enviada para o serviço ThingSpeak usando uma URL com a chave API e os valores dos sensores.

### 3. Plataforma ThingSpeak (Nuvem)

- ThingSpeak recebe os dados via API REST.
- Os valores são armazenados em campos específicos (field1, field2, field3).
- O ThingSpeak disponibiliza um dashboard online que mostra os dados em tempo real, com gráficos que facilitam a visualização da evolução das condições ambientais.
- Essa plataforma funciona como um servidor na nuvem, armazenando dados históricos e permitindo monitoramento remoto.

---

### Resumo do Fluxo

| Etapa              | Atividade                                           |
|--------------------|----------------------------------------------------|
| 1. Leitura         | ESP32 lê temperatura e umidade com DHT22            |
| 2. Avaliação       | Decisão sobre condição estável ou extrema (LEDs)    |
| 3. Envio           | ESP32 envia dados para ThingSpeak via HTTP GET      |
| 4. Armazenamento   | ThingSpeak recebe e armazena os dados                |
| 5. Visualização    | Dados exibidos no dashboard para monitoramento remoto |

---

Essa arquitetura permite o monitoramento local (LEDs) e remoto (ThingSpeak) de forma integrada e contínua, facilitando a criação de soluções IoT eficientes, escaláveis e fáceis de replicar.

## 📽️ Vídeo de Apresentação

Assista ao vídeo demonstrando nossa solução completa para apoio comunitário durante enchentes e frio extremo:

> 🔗 [Acesse diretamente o vídeo aqui](https://youtu.be/I-IyMrXRyKc)

