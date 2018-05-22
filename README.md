# Introdução
No 1º trabalho, foi proposto pelo professor Christian Azambuja Pagot a criação de três funções PutPixel, DrawLine e DrawTriangle, elas nos auxiliavam em rasterizavar as linhas na tela de acordo com primitivas que passávamos para o programa.
Nessa 2º tarefa, o objetivo era pegar os vértices no espaço do objeto, e por meio das transformações que vamos ver mais a frente, levar eles para o espaço da tela. Para exemplificação do funcionamento do Pipeline, nos foi pedido que carregássemos a Suzanne, um modelo padrão do blender, que o arquivo obj nos foi dado pelo professor para que, através de algum loader, carregamos seus vértices e usassemos o nosso pipeline, o imprimisse na tela, com auxílio do que foi desenvolvido no primeiro trabalho.
Vamos exemplificar o funcionamento teórico e prático do pipeline no tópico a seguir

# Bases Teóricas/Praticas
Faremos aqui transformações geométricas para que possamos matematicamente passar nossa modelagem no espaço do universo até o espaço da tela, usando:

 - Matrizes
Elas são muito mais eficientes computacionalmente falando quando trabalhamos com vetores e fazemos nossas multiplicações para as transformações de espaço ao longo do pipeline.
 - Coordenadas Homogêneas
São fundamentais em nosso Pipeline durante a transformação no espaço da câmera, e no espaço de corte ao espaço canônico, por isso faremos todo o pipeline já considerando a coordenada homogênea.

## Visão Geral do Pipeline

Inicialmente passamos todos os objetos em seus respectivos espaços, para um contendo todos eles, que chamamos de espaço do universo, através da Matriz Model:

<img src="https://github.com/douglasliralima/PIpelineGrafico/blob/master/Imagens/Imagem%20do%20objeto-universo.jpg">

Através de uma outra matriz que chamamos de View, definimos o espaço do universo em um espaço da câmera, que será a representação de nossos olhos na cena:

<img src="https://github.com/douglasliralima/PIpelineGrafico/blob/master/Imagens/Imagem%20da%20c%C3%A2mera%20nos%20personagens.jpg">

Aplicamos então uma matriz de projeção nesse espaço, para podermos definir se o objeto será visto em 3D(Projeção Perspectiva) ou em 2D(Projeção Paralela), simplesmente alterando a coordenada homogênea do espaço, esse espaço é conhecido como espaço de recorte:

<img src="https://github.com/douglasliralima/PIpelineGrafico/blob/master/Imagens/Imagem%20da%20diferen%C3%A7a%20de%20proje%C3%A7%C3%A3o.jpg">

Dividimos todas as coordenadas pela coordenada homogênea, dando seu valor para uma variável w e a dividindo todas as coordenadas por ela e reconfigurando seu valor para 1, mas deixando as coordenadas x, y e z distorcidas para dar o efeito de projeção perspectiva, caso seja projeção ortogonal não haverá distorção, logo podemos normalizar os nossos valores para que finalmente pode ser passado para o espaço da tela.
De uma visão ampla, nosso pipeline vai assumir a seguinte sequência:

<img src="https://github.com/douglasliralima/PIpelineGrafico/blob/master/Imagens/Imagem%20do%20pipeline%20completo.jpg">

## Load da Suzanne.obj 
O modelo que nós usamos foi a Suzanne, que é um arquivo .obj padrão do Blender. Para trabalharmos com esse tipo de arquivo, foi necessário a utilização de uma biblioteca fornecida previamente pelo professor, conhecida como Obj-Loader.

<img src="https://github.com/douglasliralima/PIpelineGrafico/blob/master/Imagens/Suzanne.png">

## Espaço do Objeto -(Matrix Model)- Espaço da Tela
Esse é o espaço que basicamente vai pegar os vértices no espaço do objeto e o transferir para um outro espaço contendo todos os objetos da cena, chamamos esse local como o espaço do objeto, nesse espaço teremos, assim como pedido pelo professor, todos os vértices no sistema de coordenadas da mão direita.
Para isso nos vamos usar uma matriz que chamamos de matriz de modelagem, também conhecida como modeling matrix ou model, nela nós vamos aplicar 4 transformações afim, essas são úteis por manter o paralelismo e poder ser exposta por matrizes,essas transformação são as de rotação, translação escala e shear, de maneira distinta para cada um dos objetos.
Como vamos aplicamos a coordenada homogênea já na model, vamos exemplificar algumas das coisas já com ela.

### Coordenadas homogêneas
Antes de observarmos as nossas transformações é valido ver um pouco sobre o principio das coordenadas homogêneas em nosso pipeline.
Os benefícios desse sistema de coordenada se torna visível também em outras partes do pipeline, como pode ser observado para fazermos as nossas projeções, mas aqui ele é especialmente útil quando tratamos de translações.
Em resumo, podemos ir ao espaço das coordenadas homogêneas e voltar para o espaço euclidiano aplicando as seguinte transformações:

<img src="https://github.com/douglasliralima/PIpelineGrafico/blob/master/Imagens/Formulas%20das%20transforma%C3%A7%C3%B5es%20em%20homog%C3%AAnea.jpg">

### Escala
Esse é o tipo mais fácil de transformação, partindo do principio que cada vértice do objeto será composto por uma matriz 1x1, nos simplesmente multiplicamos, multiplicamos todos os vetores:

<img src="https://github.com/douglasliralima/PIpelineGrafico/blob/master/Imagens/Imagem%20da%20escala.jpg">

<img src="https://github.com/douglasliralima/PIpelineGrafico/blob/master/Imagens/Matriz%20de%20escala.jpg">	

### Shear
Basicamente nós teremos no shear uma das retas uma coordenada presa, sendo que a outra irá se deslocando, vamos pegar o shear em x para exemplificar, veja que a medida que se sobe em y, os valores em x vão aumentando:

<img src="https://github.com/douglasliralima/PIpelineGrafico/blob/master/Imagens/Imagem%20do%20shear%20em%20x.jpg">

Basicamente a matriz em shear que poderíamos ter em 3D, já incluindo a coordenada homogênea seriam variações dessas, dependendo de para onde o shear for ocorrer:

<img src="https://github.com/douglasliralima/PIpelineGrafico/blob/master/Imagens/Matriz%20shear%20em%20z.jpg">

### Rotação
Utilizaremos aqui o conceito de coordenadas polares que são relativamente simples para se obter das coordenadas cartesianas:

<img src="https://github.com/douglasliralima/PIpelineGrafico/blob/master/Imagens/Imagem%20Polares.jpg">

Com isso em mente, usamos uma simples identidade trigonométrica, conseguimos chegar na matriz respectiva a rotação:

<img src="https://github.com/douglasliralima/PIpelineGrafico/blob/master/Imagens/Matriz%20de%20rota%C3%A7%C3%A3o.jpg">

Ao aplicarmos esse conceito em um sistema 3D e usando o sistema de coordenadas polares, vamos ter que rodar um dos eixos por vez em nosso sistema de vertices:

<img src="https://github.com/douglasliralima/PIpelineGrafico/blob/master/Imagens/Imagem%20de%20uma%20transla%C3%A7%C3%A3o.jpg">

### Translação
Em relação a translação temos um dos motivos da implementação de coordenadas homogêneas em nosso pipeline, pois mesmo que no espaço das coordenadas cartesianas nós não consigamos expor uma translação por meio de uma matriz, isso é possível nas coordenadas homogêneas.

<img src="https://github.com/douglasliralima/PIpelineGrafico/blob/master/Imagens/Matrizes%20para%20transla%C3%A7%C3%A3o.jpg">

Veja, nos pegamos a coordenada homogênea mais fácil que poderíamos (w = 1), e através disso podemos facilmente realizar uma soma em x ou y que translade respectivamente seus pontos.

## Espaço da Tela -(Matrix View)- Espaço da Câmera
Tendo agora nosso objeto modelado e colocado no espaço do universo, vamos deixar todos em eles em relação ao espaço da câmera, para realizar esse feito, primeiro precisamos definir os vetores respectivamente dessa câmera.
Para fazermos isso, vamos precisar de dois conceitos, o primeiro é que, para definir a câmera, precisamos de dois pontos, um localizando a posição da câmera e outro em outro ponto no espaço do universo para definir onde ela está olhando inicialmente, com esses dois pontos, podemos formar um vetor chamado vetor de direção:

<img src="https://github.com/douglasliralima/PIpelineGrafico/blob/master/Imagens/Direction.jpg">

Tendo isso em mãos, podemos determinar o vetor z da base da câmera, normalizando ele e pegando respectivamente sua inversa:

<img src="https://github.com/douglasliralima/PIpelineGrafico/blob/master/Imagens/Zc.jpg">

O segundo conceito é o que chamamos do vetor de up, ele é basicamente algo que diz onde está a "cabeça" do Camereman:

<img src="https://github.com/douglasliralima/PIpelineGrafico/blob/master/Imagens/Up.jpg">

Agora podemos conseguir com um produto vetorial a coordenada Xc e através dela a coordenada Yc:

<img src="https://github.com/douglasliralima/PIpelineGrafico/blob/master/Imagens/Xc%20Yc.jpg">

Para construirmos respectivamente a **View Matrix** que pegará os vetores na base do universo e a transformamos na matriz que faz essa mudança para uma base fora da origem que é representada pela base da câmera:

<img src="https://github.com/douglasliralima/PIpelineGrafico/blob/master/Imagens/View%20Matrix.jpg">

## Espaço da Câmera -(Projection)- Espaço de corte

Quanto mais próximo um objeto está de nós, maior ele parece, quanto mais longe, menor, a **matriz de projeção** basicamente vai preparar a nossa coordenada homogênea para aplicar esse efeito distorcendo o nosso objeto.
Podemos ver na imagem abaixo que fabricamos um plano, que chamamos de ViewPlane para pegar os valores que usaremos para alterar os pontos do objeto e dar essa ilusão de projeção.

<img src="https://github.com/douglasliralima/PIpelineGrafico/blob/master/Imagens/ViewPlane.jpg">

Veja que quando mais nos aproximarmos do Viw plane, mais perto estaremos do ponto C e respectivamente teremos um p' maior.

O que fazemos então para criar a matriz de projeção é multiplicar os vetores por duas matrizes, uma para levar trazer o centro focal até a origem através da translação e uma matriz P para fazer a modificação da projeção usando a coordenada homogênea.

<img src="https://github.com/douglasliralima/PIpelineGrafico/blob/master/Imagens/Matriz%20para%20proje%C3%A7%C3%A3o.jpg">

## Espaço de corte -(Divisão por w)- Espaço Canônico
No espaço canônico nos retornamos o valor da coordenada homogênea para 1, usando um w com o seu mesmo valor e dividindo todas as coordenadas por ela:

<img src="https://github.com/douglasliralima/PIpelineGrafico/blob/master/Imagens/w.jpg">

## Universo Canônico -(ViewPort)- Universo da tela
Estamos praticamente no final do nosso pipeline, aqui só precisamos respeitar o sistema que as coisas são colocadas na tela e inverter o nosso a direção de nossa coordenada y e transladamos nossos vértices levando em consideração a largura(weight) e altura (height) da tela, em resumo a **MViewPort** vai vir da seguinte operação:

<img src="https://github.com/douglasliralima/PIpelineGrafico/blob/master/Imagens/MViewPort.jpg">

### Vídeo da Rotação

[![IMAGE ALT TEXT HERE](https://github.com/douglasliralima/PIpelineGrafico/blob/master/Imagens/Suzanne_Rotation1.png)](https://www.youtube.com/watch?v=kLTx-9PLFSw&feature=youtu.be)


