all:	pdf

pdf: 
	pdflatex wsnpresentation.tex
	pdflatex wsnpresentation.tex
	evince wsnpresentation.pdf &
bib:	
	pdflatex wsnpresentation.tex
	bibtex wsnpresentation
	pdflatex wsnpresentation.tex
					
clean:
	rm -f wsnpresentation.aux wsnpresentation.log wsnpresentation.blg wsnpresentation.bbl wsnpresentation.out wsnpresentation.dvi wsnpresentation.snm wsnpresentation.toc wsnpresentation.nav

