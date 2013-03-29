/**
 * startup_stm32f4xx.c
 * Código de startup para microcontroladores STM32F4xx
 * Baseado no arquivo "startup_stm32f4xx.s" distribuído pela ST
 * Autor: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
 */

/* start address for the initialization values of the .data section. 
defined in linker script */
extern unsigned long  _etext;
/* start address for the .data section. defined in linker script */  
extern unsigned long  _data;
/* end address for the .data section. defined in linker script */
extern unsigned long  _edata;
/* start address for the .bss section. defined in linker script */
extern unsigned long  _bss;
/* end address for the .bss section. defined in linker script */
extern unsigned long  _ebss;

extern void SystemInit (void);
extern void SysTick_Handler (void);
extern int main (void);

void Reset_Handler (void) {

    unsigned long *srcPtr, *dstPtr, *bss;
    
    srcPtr = &_etext;
    for (dstPtr = &_data; dstPtr < &_edata, *dstPtr++ = *srcPtr++)
        ;

    // Zera o bss (inicializa as variáveis sem inicialização
    for (bss = &_bss; bss < &_ebss; *bss++ = 0)
        ;

    // Inicia o hardware do sistema
    SystemInit();

    // Branch para o main()
    main();

    // Se retornar do main... o que não deve ocorrer
    while (1)
        ;
}

void NMI_Handler (void) {
    while (1)
        ;
}

void HardFault_Handler (void) {
    while (1)
        ;
}

void IntDefault_Handler (void) {
    while (1)
        ;
}

// Espaço reservado para a stack do microcontrolador
static unsigned long pulStack[128];

// Vetor de interruções
__atribute__ ((section(".isr_vector")))
void (*const g_pfnVector[])(void) = {

    (void (*)(void))((unsigned long)pulStack + sizeof(pulStack)),
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    IntDefaultHandler,				// MemManage_Handler
	IntDefaultHandler,				// BusFault_Handler
    IntDefaultHandler,				// UsageFault_Handler
    0,
    0,
    0,
    0,
    IntDefaultHandler,				// SVC_Handler
    IntDefaultHandler,				// DebugMon_Handler
    0,
    IntDefaultHandler,				// PendSV_Handler
    SysTick_Handler,				// SysTick    
    
    // TODO: Colocar as outras aqui
};

