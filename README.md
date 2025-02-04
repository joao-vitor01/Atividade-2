# Atividade 2: Temporizador de Um Disparo (One Shot)

Este projeto implementa um sistema de acionamento de LEDs utilizando um **botão** e a função `add_alarm_in_ms()` da **Pico SDK**. O botão inicia uma sequência de desligamento dos LEDs com **intervalos de 3 segundos**.

## **Requisitos do Projeto**
- Pressionar o **botão (GPIO5)** ativa os **3 LEDs** (Azul, Vermelho e Verde).
- Após **3 segundos**, o **LED Azul apaga**.
- Após mais **3 segundos**, o **LED Vermelho apaga**.
- Após mais **3 segundos**, o **LED Verde apaga** (todos desligados).
- O botão **só pode ser pressionado novamente após o desligamento total** dos LEDs.
- Implementação de **debounce por software**.

## **Componentes Utilizados**
- Raspberry Pi Pico W
- **LED Azul, Vermelho e Verde** (GPIOs 11, 12 e 13)
- **Botão (GPIO5)**
- Resistores de 330Ω
- **BitDogLab** (opcional)

##  **Como Executar**
1. Instale a **Pico SDK** e o **CMake**.
2. Compile o código e carregue no Raspberry Pi Pico W.
3. Pressione o **botão** e observe a sequência de desligamento dos LEDs.

