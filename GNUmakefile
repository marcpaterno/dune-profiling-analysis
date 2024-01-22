all: january-2024.pdf atan2.pdf

january-2024.pdf: january-2024.qmd vtune_data.csv
	quarto render $< --to beamer
atan2.pdf: atan2.qmd atan2.tsv
	quarto render $< --to beamer

clean:
	rm -f january-2024.pdf january-2024.tex
	rm -rf january-2024_cache/* january-2024_files/*
	rm -f atan2.pdf atan2.tex
	rm -rf atan_cache/* atan2_files/*
