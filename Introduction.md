# Introdução #

OpenLPC (Open Library Portable (for many micro)Controllers) é uma _HAL_ (_Hardware Abstraction Layer_) escrita na linguagem C que pretende uniformizar a escrita de _firmware_ e drivers para dispositivos.

Atualmente este projeto tem sido escrito como hobbie e o propósito inicial é utilizá-lo em duas dissertações de mestrado.

A _HAL_ ainda está em desenvolvimento. Qualquer bug pode (e deve) ser reportado para correção imediata.

## _Features_ ##

A _HAL_ possui as seguintes características e funcionalidades:
  * Totalmente escrita em C (com, possivelmente, algumas funções em assembly
  * Divisão de pastas para cada _port_ (um _port_ é uma versão da _HAL_ para um microcontrolador específico)
  * Documentação no padrão Doxygen
  * Pode ser compilado usando o compilador _open-source_ **GCC**

(Mais coisa a ser acrescentada...)