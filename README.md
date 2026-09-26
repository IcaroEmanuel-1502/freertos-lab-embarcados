# Laboratório de Sistemas Embarcados: FreeRTOS

Este repositório contém as implementações práticas desenvolvidas para o estudo do RTOS **FreeRTOS**, com foco no escalonamento de tarefas e comunicação inter-processos (IPC). 

Os ficheiros aqui presentes limitam-se aos códigos-fonte principais (`main`) de cada atividade, implementados em linguagem C para microcontroladores.

## 🎯 Objetivo das Atividades

O principal objetivo deste conjunto de práticas é explorar e consolidar os conceitos de concorrência e sincronização em sistemas embarcados. As atividades progridem desde a criação básica de tarefas até à construção de um "Mini Sistema Industrial", abordando:

*   **Escalonamento e Prioridades:** Análise do comportamento de tarefas com diferentes níveis de prioridade e a mecânica de preempção.
*   **Sincronização com Semáforos:** Utilização de semáforos binários para coordenar a execução entre tarefas (ex: sinalizar a leitura de um sensor para iniciar o processamento).
*   **Proteção de Recursos Partilhados (Mutex):** Garantia de acesso exclusivo a recursos comuns, como a interface de comunicação serial (UART), prevenindo a corrupção de dados.
*   **Gestão de Tempos Limite (Timeouts):** Implementação de mecanismos de *timeout* (ex: `osWaitForever` vs `1000ms`) para evitar bloqueios indefinidos (*deadlocks*) e gerir o fluxo alternativo quando um recurso está ocupado.
