path-bin=./bin
path-json=./funcionarios/Funcionarios-50K.json

run:
	@${path-bin}/desafio5 ${path-json}

build: includes/json.hpp
	mkdir -p ${path-bin}
	g++ -o ${path-bin}/desafio5 ./src/main.cpp ./src/company.cpp

includes/json.hpp:
	curl -o ./includes/json.hpp https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp

url-funcionarios-json= \
	http://www.bcampos.com/Funcionarios-10K.json.7z \
	http://www.bcampos.com/Funcionarios-50K.json.7z \
	http://www.bcampos.com/Funcionarios-100K.json.7z \
	http://www.bcampos.com/Funcionarios-250K.json.7z \
	http://www.bcampos.com/Funcionarios-500K.json.7z \
	http://www.bcampos.com/Funcionarios-1M.json.7z \
	# http://www.bcampos.com/Funcionarios-2M.json.7z \
	# http://www.bcampos.com/Funcionarios-3M.json.7z \
	# http://www.bcampos.com/Funcionarios-5M.json.7z \
	# http://www.bcampos.com/Funcionarios-12M.json.7z \
	# http://www.bcampos.com/Funcionarios-15M.json.7z \
	# http://www.bcampos.com/Funcionarios-20M.json.7z \
	# http://www.bcampos.com/Funcionarios-25M.json.7z \
	# http://www.bcampos.com/Funcionarios-30M.json.7z

path-funcionarios-json=./funcionarios

download-funcionarios-json:
	mkdir -p ${path-funcionarios-json}
	wget ${url-funcionarios-json} -P ${path-funcionarios-json}
	7z -y x -o${path-funcionarios-json} "${path-funcionarios-json}/*.7z"
	rm -rf ${path-funcionarios-json}/*.7z
