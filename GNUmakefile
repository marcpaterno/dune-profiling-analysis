all: january-2023.pdf

january-2023.pdf: january-2023.qmd
	quarto render $< --to beamer

clean:
	rm -f january-2023.pdf january-2023.tex
