# Documentação #

O **OpenLPC** conta com uma documentação escrita usando o [www.doxygen.org Doxygen]. O OpenLPC não conta com o arquivo **Doxyfile** pois a localização relativa dos diretórios pode mudar.

A geração do arquivo **Doxyfile** não é muito complexa e a instalação do Doxygen no GNU/Linux conta com uma GUI gráfica (doxywizard) para criar o arquivo e gerar a documentação.

Os códigos documentados encontram-se no diretório **include**, onde estão todos os _headers_. Os códigos contidos em **ports** não contém documentação Doxygen mas contém comentários instrutivos para os programadores.

Para gerar a documentação o arquivo **Doxyfile** deve ser gerado com as seguintes configurações mínimas:
  * _Optimize for C or PHP output_
  * _DOXYFILE\_ENCODING_ = UTF-8
  * OUTPUT LANGUAGE = Brazillian

A documentação está toda em Português do Brasil.
