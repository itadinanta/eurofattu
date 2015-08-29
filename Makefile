# $Id: Makefile,v 1.8 2002/01/17 23:56:03 nicola Exp $
DESTDIR=/home/fattu
APACHE_USER=wwwrun
APACHE_GROUP=www
DBUSER=eurofattu
DIRS=lib web conf text debug bin template tmp out font
FONTCONFIG=font/t1lib.config

messages: text/messages.db font/t1lib.config

text/messages.db: text/messages.txt
	cd text; ./txt2gdbm.pl messages.txt messages.db 2> text.log

install: messages installdb installfiles

reinstall: uninstalldb uninstallfiles installdb messages installfiles fixperm

installfiles: createdir
	cp lib/*.inc $(DESTDIR)/lib
	cp -r lib/base $(DESTDIR)/lib
	cp lib/*.conf $(DESTDIR)/conf
	cp font/*.config font/FontDataBase font/*.pfb font/*.afm font/*.pfm $(DESTDIR)/font
	cp template/efstyle.tex template/logo.eps $(DESTDIR)/template
	cp template/test.tex $(DESTDIR)/out
	cp bin/*.sh $(DESTDIR)/bin
	cp text/README text/*.htm text/*.db $(DESTDIR)/text
	cp -r web/* $(DESTDIR)/web

createdir: 
	for i in $(DIRS) ; do mkdir -p $(DESTDIR)/$$i; done

font/t1lib.config:
	echo ENCODING= > $(FONTCONFIG)
	echo AFM=$(DESTDIR)/font >> $(FONTCONFIG)
	echo TYPE1=$(DESTDIR)/font >> $(FONTCONFIG)
	echo FONTDATABASE=$(DESTDIR)/font/FontDataBase >> $(FONTCONFIG)

fixperm:
	@useradd $(DBUSER) -g $(APACHE_GROUP)
	chown -R $(APACHE_USER).$(APACHE_GROUP) $(DESTDIR)
	chmod -R 775 $(DESTDIR)
	find $(DESTDIR) -type f -exec chmod 664 \{\} \;
	chmod 775 $(DESTDIR)/bin/*.sh

installdb:
	createuser -d -a -U postgres $(DBUSER)
	createdb $(DBUSER) -U $(DBUSER) 2> installdb.log 	
	psql $(DBUSER) -U $(DBUSER) -f sql/create_tables.sql 2>> installdb.log
	psql $(DBUSER) -U $(DBUSER) -f sql/populate_tables.sql 2>> installdb.log
	createlang -U $(DBUSER) $(DBUSER) plpgsql 2>> installdb.log
	psql $(DBUSER) -U $(DBUSER) -f sql/create_procedures.sql 2>> installdb.log

uninstallfiles:
	for i in $(DIRS) ; do rm -rf $(DESTDIR)/$$i; done

uninstalldb:
	dropdb $(DBUSER) -U $(DBUSER) 2> cleandb.log
	dropuser $(DBUSER) -U postgres

clean:
	find . \( -name "*.log" -or -name "*~" -or -name "*.db" \) -exec rm \{\} \;

cleanbak:
	find . -name "*~" -exec rm \{\} \;
