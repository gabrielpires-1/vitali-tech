# VitaliTech
Repositório utilizado para a disciplina de Projetos 2 - 2º período de Ciência da Computação na CESAR School.

# VitaliTech
Vitali-Tech é uma aplicação que visa auxiliar no monitoramento de notas e avaliações de residentes e preceptores, além de fornecer feedbacks com base em tags. A aplicação também inclui um gestor responsável por registrar novos usuários, fazer modificações e excluí-los.

# Como funciona
Inicialmente, o gestor deve cadastrar os usuários, fornecendo nome, email, senha, CPF e selecionando o tipo de função que desempenham (Preceptor/Residente). Após o cadastro, os preceptores e residentes poderão acessar o site fazendo login com seu email e senha. Ao entrar no site, eles serão apresentados a duas opções: aba de avaliação e aba de feedback.

Na aba de avaliação, o preceptor poderá atribuir notas para cada critério, selecionar tags (comentários pré-definidos) para o residente e, ao final, gerar uma nota final. Além disso, o preceptor terá a opção de adicionar um comentário opcional sobre o residente. Na aba de avaliação, o residente poderá visualizar sua nota por critério, as tags atribuídas pelo preceptor, a nota final e o comentário gerado pelo preceptor.

Na aba de feedback, tanto o preceptor quanto o residente terão a possibilidade de enviar tags pré-definidas e comentários opcionais. Além disso, eles poderão visualizar os feedbacks recebidos, que serão anônimos.

# Como utilizar nosso protótipo:
Primeiramente, é necessário ter um compilador C instalado em sua máquina. Em seguida, instale o Git Bash. No terminal do Git Bash, navegue até o diretório correto do seu projeto. Para clonar o repositório, utilize o comando <br>'git clone https://github.com/gabrielpires-1/vitali-tech.git'<br> Com isso, o repositório será baixado para a sua IDE.<br>

Para compilar e executar o código, abra o terminal e execute os seguintes comandos:<br>
gcc -o executavel main.c lib.c<br>
.\executavel<br>
Você pode substituir o nome "executavel" por qualquer nome de sua preferência.
