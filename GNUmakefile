all: january-2023.pdf atan2.pdf

january-2023.pdf: january-2023.qmd vtune_data.csv
	quarto render $< --to beamer
atan2.pdf: atan2.qmd atan2.tsv
	quarto render $< --to beamer

clean:
	rm -f january-2023.pdf january-2023.tex
	rm -rf january-2023_cache/* january-2023_files/*
	rm -f atan2.pdf atan2.tex
	rm -rf atan_cache/* atan2_files/*
