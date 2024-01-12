all: january-2023.pdf

january-2023.pdf: january-2023.qmd vtune_data.csv
	quarto render $< --to beamer

clean:
	rm -f january-2023.pdf january-2023.tex
	rm -rf january-2023_cache/* january-2023_files/*
