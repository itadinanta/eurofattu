-- $Id: create_procedures.sql,v 1.3 2001/12/31 17:28:17 nicola Exp $

CREATE FUNCTION DOC_NEW(INTEGER) RETURNS INTEGER AS '
DECLARE
	docclass_ ALIAS for $1;
	docpointer_ integer;
	last_nprog_ integer;
BEGIN
	select into last_nprog_ counter 
	from docclass 
	where codice=docclass_
	limit 1;

	docpointer_ := NEXTVAL(''DOCSEQ'');	

	insert into documenti (docpointer, docclass, nprog)
	values (docpointer_, docclass_, last_nprog_);

	update docclass set counter=counter+1 
	where codice=docclass_;

	return docpointer_;
END;
' LANGUAGE 'plpgsql';

CREATE FUNCTION INDIRIZZO_NEW() RETURNS INTEGER AS '
DECLARE
	codice_ integer;

BEGIN
	codice_ := NEXTVAL(''INDIRIZZOSEQ'');
	insert into indirizzo (codice) values (codice_);

	return codice_;
END;
' LANGUAGE 'plpgsql';

CREATE FUNCTION UTENTE_NEW() RETURNS INTEGER AS '
DECLARE
	codice_ integer;

BEGIN
	codice_ := NEXTVAL(''USERSEQ'');
	insert into utenti (userid,username,password) values (codice_,codice_,''*'');

	return codice_;
END;
' LANGUAGE 'plpgsql';
