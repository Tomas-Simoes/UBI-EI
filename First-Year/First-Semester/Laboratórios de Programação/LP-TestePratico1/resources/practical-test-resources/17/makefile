# Este target mostra a resposta a partir do ficheiro segredo.txt
mostrar: segredo.txt
	@cat segredo.txt

# Este target gera o ficheiro segredo.txt a partir dos ficheiros segredo.enc e key.hex
gerar: segredo.enc key.hex
	@openssl enc -aes-128-ctr -in segredo.enc -out segredo.txt -K `cat key.hex` -iv 0

# Este target gera o ficheiro key.hex a partir do ficheiro key.txt
key.hex : key.txt
	@openssl md5 -r -out key.hex key.txt ; truncate -s 32 key.hex
