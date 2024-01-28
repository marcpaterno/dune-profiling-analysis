.PHONY: clean pdf

QMD_FILES = $(wildcard *.qmd)
PDF_FILES = $(patsubst %.qmd,%.pdf, $(QMD_FILES))

.SUFFIXES: .pdf .qmd .html

all: pdf

pdf: paterno-23-01-2024.pdf

.qmd.pdf:
	quarto render $< --to beamer

.qmd.html:
	quarto render $< --to html

clean:
	rm -f *.bak* indent.log *.fls *.pdf.tmp *.fdb_latexmk *.tex $(PDF_FILES)
	#rm -rf january-2024_cache/* january-2024_files/*
	#rm -rf atan_cache/* atan2_files/*


# Addtional dependencies go here.
january-2024.pdf: vtune_data.csv benchmark_2024_01_06.txt
paterno-23-01-2024.pdf: vtune_data.csv benchmark_2024_01_06.txt

