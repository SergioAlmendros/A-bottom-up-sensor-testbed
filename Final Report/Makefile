all:  clean bib pdf

pdf:
	pdflatex A-bottom-up-sensor-testbed.tex
	evince A-bottom-up-sensor-testbed.pdf &

bib:
	pdflatex A-bottom-up-sensor-testbed.tex
	bibtex A-bottom-up-sensor-testbed
	pdflatex A-bottom-up-sensor-testbed.tex

clean:
	rm A-bottom-up-sensor-testbed.aux
