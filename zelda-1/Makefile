# Yeah, I don't know nothing about Makefiles, this is all the better I
# could do.
all:	txt html

html:	z1spec.html
z1spec.html:	z1spec.sgml
	sgml2html $<

txt:	z1spec.txt
z1spec.txt:	z1spec.sgml
	sgml2txt -f $<

zip:	z1spec.zip
z1spec.zip:	z1spec.txt z1spec.html README Makefile
	mkdir html
	mv *.html html/
	zip -9r z1spec README Makefile z1spec.sgml z1spec.txt html
	mv html/* .
	rmdir html

clean:
	rm -f z1spec.txt z1spec*.html z1spec.zip
