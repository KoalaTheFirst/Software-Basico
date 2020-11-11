Nome: Matheus Valente Brandão Moura
Matricula: 16/0138426

O trabalho resolve MACROS.

Instruções de compilação: O programa foi feito em C e compilado todas as vezes no Ubuntu utilizando o GCC. Para que ele tenha o nome "montador" e sejá executado com o comando ./montador, como requisitado no trabalho, é necessário apenas compila-lo utilizando o comando "gcc -o montador montador.c", o nome dos arquivos gerados estão exatamente com o escrito no roteiro, então tanto PRE como OBJ são escritos em letras maiúsculas, o que deve ser observado para roda o progrma na hora de inserir o nome do arquivo. Todos os testes foram feitos com o arquivo na mesma pasta do programa, logo, não posso dar certeza que funcionaria de outra forma, no entanto suponho que funcionaria, embora ache que para este trabalho não faz diferença.

Comentários gerais para facilitar a analise do código:
O código contem duas funções principais, preprocessa() e monta(), cada uma delas é utilizada em uma etapa diferente. Quando utilizado o argumento "-p" na linha de comando para a execução do programa a função chama é preprocessa(). Esta função recebera como argumento os ponteiros dos arquivos que deve acessar para ler o .asm e escrever o .PRE. A função em si faz muito pouco, ela apenas contém alguns condicionais que acionam outras funções dependendo do que for lido no arquivo .asm, as condicionais são testadas com base no retorno da função checa(). Esta por sua vez, recebe como argumento o que foi lido do arquivo e retorna um código diferente dependendo do que recebeu de argumento, ela retorna um valor diferente para cada um dos mnemonicos do assembly inventado, caso a leitura seja um rótulo ela retorna 98, caso seja algo não identificado, possivelmente um rótulo que está sendo utilizado como operador ela retorna 21, e para os comentários retorna 99.
A partir do valor lido em checa(), o programa decide o que é o que foi lido e chamará uma função diferente, caso seja uma instrução chamará instruct(), um rótulo chamará rotulo(), um IF chamará if_condition(). Todas estas funções são bem simples, a mais complexa seria a função rotulo(), pois ela deve testar se o que ela leu é um rótulo que deve ser tratado no preprocessamento, como no caso EQU, ou não. 
Caso sim, ela adiciona o rótulo a uma lista que será consultada posteriormente para fazer as substituições no código durante a execução desta primeira etapa.
A função também checa ser o rótulo é referente a uma MACRO, assim como se fosse um EQU, a MACRO é salva em uma lista encadeada simples para consulta posterior pelo código.
Ao fim da função há dois laços que servem apenas para liberar a memoria alocada nas listas durante a execução do programa.
A função monta() funciona de maneira bem similar à função preprocessa(), a maior diferença é o fato dela fazer as duas passagens no código preprocessado, a primeira lendo o código e assim como a anterior, alocando memoria em uma lista para salvar os rótulos, e a segunda substituindo no código o valor dos opcodes da função. Aqui cabe um breve comentário que ao fazer a função checa() eu me equivoquei e subtrai 1 de todos os opcodes que ela retorna, por isso ao escrever os opcodes no arquivo .OBJ sempre é escrito (mnemonico+1) pois foi mais rápido corrigir assim do que modificando todo o código.
Para a função monta, como não tinha de me preocupar com IF ou MACRO ela ficou mais simples, a quantidade de testes é feita apenas para verificar se o que foi lido é um rótulo, uma instrução ou um número substituido por EQU ou o valor de uma CONST. 

Eu não consgui utilizar o simulador disponível no aprender, por algum motivo ele entra em um loop infinito no meu pc, então todos os testes do programa foram feitos com códigos que eu mesmo inventei usando o assembly inventado.

Breve comentário das funções mais simples:
checa_operandos(): checa o número de operandos que o programa deve ler após uma instrução, poderia ser utilizado para checar erros nos argumentos, mas não implementei isto pois optei por fazer o programa para macros.
checa_tamanho(): retorna o tamanho de cada instrução. É utilizado para o valor do contador na hora de substituir o valor dos rótulos na montagem.
cria_no(): cria um nó na lista de rótulos.
cria_no_macro(): cria um nó na lista de instruções de macros.
percorre_lista(): percorre a lista de rotulos e retorna um ponteiro para o rotulo que está sendo buscado.
percore_lista_macro(): percorre a lista de macros e retorna o ponteiro para a primeira instrução da macro buscada.
instruct(): le e imprime no arquivo os operando lidos com base no opcode passado para a função.
if_condition(): checa se o valor do rotulo após o IF é 1 ou 0, se for 0 apaga a próxima instrução, caso não, não faz nada e ela será lida normalmente.